#pragma once
#include "Force.hpp"
#include "Entity.hpp"
#include "Includes.hpp"

template <class E>
class Chunk : public sf::RectangleShape
{
public:

	Chunk();
	Chunk(sf::Vector2f pos);
	~Chunk();

	std::shared_ptr<std::vector<std::shared_ptr<E>>> getOutOfBounds();
	std::shared_ptr<std::vector<std::pair<std::shared_ptr<E>, Direction>>> getOnEdges();

	static Direction toDirection(bool up, bool down, bool left, bool right);

	void clean();
	void update();
	void checkEntities(int);
	void add(std::shared_ptr<E> e);
	void drawEntities(sf::RenderTarget & target);
	void externalCheck(std::shared_ptr<E> ent);

	bool hasNoEntities();

	const int getNumEntities();

	static std::string directionToString(Direction);

	static int getPrehash(sf::Vector2f pos);
	static sf::Vector2f toChunkPos(sf::Vector2f pos);

	std::shared_ptr<std::vector<sf::Vector2f>> fromDirection(Direction);


	std::vector<std::shared_ptr<E>> entities;
};

template <class E>
Chunk<E>::Chunk() {}


template <class E>
Chunk<E>::Chunk(sf::Vector2f pos)
{
	auto chunkPos = toChunkPos(pos);
	setPosition(chunkPos.x * Board<E>::chunkSize, chunkPos.y * Board<E>::chunkSize);
	setSize(sf::Vector2f((float)Board<E>::chunkSize, (float)Board<E>::chunkSize));
	setFillColor(sf::Color::Transparent);
}

template <class E>
Chunk<E>::~Chunk() {}

template <class E>
std::shared_ptr<std::vector<std::shared_ptr<E>>> Chunk<E>::getOutOfBounds() //Return elements that are out of bounds, erasing them from current entity list
{
	auto bounds = this->getGlobalBounds();
	auto notInBounds = [bounds](auto& e) {return !bounds.contains(e->getCenter()); };

	//Copy elements that are out of bounds into a new vector
	std::vector<std::shared_ptr<E>> outOfBounds(entities.size());

	auto it = std::copy_if(entities.begin(), entities.end(), outOfBounds.begin(), notInBounds);
	outOfBounds.resize(std::distance(outOfBounds.begin(), it));  //Resize the vector

																 //Erase old elements that were out of bounds
	entities.erase(std::remove_if(entities.begin(), entities.end(), notInBounds),
		entities.end());

	return std::make_shared<std::vector<std::shared_ptr<E>>>(outOfBounds);
}

template <class E>
std::shared_ptr<std::vector<std::pair<std::shared_ptr<E>, Direction>>> Chunk<E>::getOnEdges()
{
	auto bounds = this->getGlobalBounds();

	//Copy elements that are out of bounds into a new vector
	auto onEdges = std::make_shared<std::vector<std::pair<std::shared_ptr<E>, Direction>>>();
	bool up = false, down = false, left = false, right = false;
	Direction direction = Up;

	for (auto& e : entities)
	{
		sf::Vector2f pos = e->getCenter();
		auto e_bounds = e->getGlobalBounds();

		right = (pos.x + e_bounds.width / 2 > bounds.left + bounds.width);
		left = (pos.x - e_bounds.width / 2 < bounds.left);

		down = (pos.y + e_bounds.height / 2 > bounds.top + bounds.height);
		up = (pos.y - e_bounds.height / 2 < bounds.top);

		if (right || left || down || up) //If the entity is actually out of bounds
		{
			direction = toDirection(up, down, left, right);
			onEdges->push_back(std::make_pair(e, direction));

			if (direction > Right) //If the direction is a corner (UpRight, DownLeft, etc..)
			{
				//Literal Corner Cases
				if (direction == UpLeft)
				{
					onEdges->push_back(std::make_pair(e, Up));
					onEdges->push_back(std::make_pair(e, Left));
				}
				else if (direction == UpRight)
				{
					onEdges->push_back(std::make_pair(e, Up));
					onEdges->push_back(std::make_pair(e, Right));
				}
				else if (direction == DownRight)
				{
					onEdges->push_back(std::make_pair(e, Down));
					onEdges->push_back(std::make_pair(e, Right));
				}
				else if (direction == DownLeft)
				{
					onEdges->push_back(std::make_pair(e, Down));
					onEdges->push_back(std::make_pair(e, Left));
				}
			}
		}
	}

	return onEdges;
}

template <class E>
Direction Chunk<E>::toDirection(bool up, bool down, bool left, bool right)
{
	if (right && up)
	{
		return UpRight;
	}
	else if (left && up)
	{
		return UpLeft;
	}
	else if (right && down)
	{
		return DownRight;
	}
	else if (left && down)
	{
		return DownLeft;
	}
	else if (up)
	{
		return Up;
	}
	else if (down)
	{
		return Down;
	}
	else if (right)
	{
		return Right;
	}
	else if (left)
	{
		return Left;
	}
	else
	{
		return None;
	}
}

template <class E>
void Chunk<E>::add(std::shared_ptr<E> e)
{
	entities.push_back(e);
}

template <class E>
void Chunk<E>::drawEntities(sf::RenderTarget& target)
{
	for (auto e : entities)
	{
		e->doDraw(target);
	}
}

template <class E>
void Chunk<E>::update()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->update();
		if (entities[i]->isAwaitingAction())
		{
			entities[i]->action(this);
		}
		checkEntities(i); //Check entities to the right of current entity until there are no longer collisions
	}

	//Keep our entities sorted so that we can more easily check collisions
	std::sort(
		entities.begin(), entities.end(),
		[](auto& e1, auto& e2)
	{return e1->getSortBy() < e2->getSortBy(); }
	);
}

//Worst case for checkEntities is O(n + n-1 -> n=0), when all entities are colliding
//Best case is O(n), where each entity is only colliding with its neighbor or nothing at all
template <class E>
void Chunk<E>::checkEntities(int it)
{
	for (int i = it; i < entities.size(); i++) //Start from current entity and check to the right
	{
		if (i + 1 < entities.size()) //If there IS an entity to the right..
		{
			if (entities[i]->checkWith(*entities[i + 1])) //See if we are touching it
			{
				entities[i]->collide(&*entities[i + 1]); //If so, collide with it
			}
			else
			{
				return; //Otherwise, move onto the next entity
			}
		}
	}
}

template<class E>
inline void Chunk<E>::clean()
{
	auto isDead = [](auto& e) {return !e->isAlive(); };
	entities.erase(std::remove_if(entities.begin(), entities.end(), isDead), entities.end());

	for (auto & e : entities)
	{
		e->clean();
	}
}

template <class E>
sf::Vector2f Chunk<E>::toChunkPos(sf::Vector2f pos) //Find out where a grid of chunks a certain point lies.
{
	return sf::Vector2f(floor(pos.x / (float)Board<E>::chunkSize), floor(pos.y / (float)Board<E>::chunkSize));
}

template <class E>
int Chunk<E>::getPrehash(sf::Vector2f pos)
{
	auto chunkPos = toChunkPos(pos);
	return (int)chunkPos.x + ((10 ^ (numDigits((int)chunkPos.x) + 2)) * (int)chunkPos.y); 
}

template <class E>
const int Chunk<E>::getNumEntities()
{
	return (int)entities.size();
}

template <class E>
bool Chunk<E>::hasNoEntities()
{
	return entities.size() == 0;
}

template <class E>
void Chunk<E>::externalCheck(std::shared_ptr<E> ent)
{
	for (auto& e : entities)
	{
		if (ent->checkWith(*e))
		{
			ent->collide(&*e);
		}
	}
}

template <class E>
std::shared_ptr<std::vector<sf::Vector2f>> Chunk<E>::fromDirection(Direction direction)
{

	auto chunk_positions = std::make_shared<std::vector<sf::Vector2f>>();

	chunk_positions->push_back(getPosition());

	sf::Vector2f pos = getPosition();
	switch (direction)
	{
	case Up:
		pos.y -= (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		break;
	case Down:
		pos.y += (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		break;
	case Left:
		pos.x -= (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		break;
	case Right:
		pos.x += (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		break;
	case UpLeft:
		pos.y -= (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		pos.x -= (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		pos.y += (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		break;
	case UpRight:
		pos.y -= (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		pos.x += (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		pos.y += (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		break;
	case DownLeft:
		pos.y += (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		pos.x -= (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		pos.y -= (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		break;
	case DownRight:
		pos.y += (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		pos.x += (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		pos.y -= (float)Board<E>::chunkSize;
		chunk_positions->push_back(pos);
		break;
	case None:
		break;
	default:
		break;
	}

	return chunk_positions;
}

template <class E>
std::string Chunk<E>::directionToString(Direction direction)
{
	std::string toReturn;
	switch (direction)
	{
	case Up:
		toReturn = "Up";
		break;
	case Down:
		toReturn = "Down";
		break;
	case Left:
		toReturn = "Left";
		break;
	case Right:
		toReturn = "Right";
		break;
	case UpLeft:
		toReturn = "UpLeft";
		break;
	case UpRight:
		toReturn = "UpRight";
		break;
	case DownLeft:
		toReturn = "DownLeft";
		break;
	case DownRight:
		toReturn = "DownRight";
		break;
	case None:
		toReturn = "None";
		break;
	default:
		break;
	}

	return toReturn;
}