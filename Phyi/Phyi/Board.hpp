#pragma once
#include "Includes.hpp"
#include "Entity.hpp"
#include "TextureMap.hpp"
#include "Chunk.hpp"
#include <type_traits>

struct Keys
{
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
};

template <class E>
class Board
{
	static_assert(std::is_base_of<Entity, E>::value, "E Must inherit from Entity - Intialize Board with a different class parameter");

public:
	static int chunkSize;
	static float moveSpeed;

	Board(int width = 4096, int height = 4096);
	~Board();

	virtual void update();           
	virtual void handler(sf::Event*); 

	void run();

	virtual void addEntity(std::shared_ptr<E> e);

	static TextureMap texture_map;

protected:
	std::vector<std::shared_ptr<E>> getEntitiesWithin(sf::Vector2f pos1, sf::Vector2f pos2);

	std::unordered_map<int, std::shared_ptr<Chunk<E>>> chunks;
	std::vector<int> chunkKeys;
	sf::View view;
	sf::View gui_view;
	sf::RenderWindow window;

	sf::RectangleShape selectionBox;
	bool selecting;
	std::shared_ptr<std::vector<std::shared_ptr<E>>> selected;

private:
	void clean();
	void checkEdges();
	void checkMoved();

	Keys keys;
	float current_zoom;
};

template <class E>
int   Board<E>::chunkSize = 131072;
template <class E>
float Board<E>::moveSpeed = 10.0f;
template <class E>
TextureMap   Board<E>::texture_map;

template <class E>
Board<E>::Board(int width, int height) : current_zoom(1), selecting(false),
				selected(std::make_shared<std::vector<std::shared_ptr<E>>>(std::vector<std::shared_ptr<E>>()))
{
	window.create(sf::VideoMode(600, 600), "Phyi");

	view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((float)width, (float)height));
	gui_view = sf::View(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((float)width, (float)height)));
	window.setView(view);

	selectionBox.setOutlineColor(sf::Color::Red);
	selectionBox.setOutlineThickness(20.0);
	selectionBox.setFillColor(sf::Color::Transparent);
}

template <class E>
Board<E>::~Board() {}

template <class E>
void Board<E>::addEntity(std::shared_ptr<E> e)
{
	e->setOrigin(sf::Vector2f(e->getGlobalBounds().width / 2, e->getGlobalBounds().height / 2));

	auto c = Chunk<E>(e->getCenter());

	int preHash = Chunk<E>::getPrehash(e->getCenter());

	//Add a new chunk if it doesn't already exist
	if (chunks.find(preHash) == chunks.end())
	{
		auto c = Chunk<E>(e->getCenter());
		chunks.insert(std::make_pair(preHash, std::make_shared<Chunk<E>>(c)));
		chunkKeys.push_back(preHash);
	}

	chunks.at(preHash)->add(e);
}

template <class E>
void Board<E>::update()
{
	if (keys.W) view.move(0.0f, -moveSpeed * (current_zoom / 1.7f));
	if (keys.A) view.move(-moveSpeed * (current_zoom / 1.7f), 0.0f);
	if (keys.S) view.move(0.0f, moveSpeed * (current_zoom / 1.7f));
	if (keys.D) view.move(moveSpeed * (current_zoom / 1.7f), 0.0f);
}

template <class E>
void Board<E>::handler(sf::Event *event)
{
	switch (event->type)
	{
	case sf::Event::Closed:
		window.close();
		break;

	case sf::Event::Resized:
		std::cout << event->size.width << event->size.height << std::endl;
		view.setSize((float)event->size.width, (float)event->size.height);
		view.zoom(current_zoom);
		break;

	case sf::Event::MouseWheelScrolled:
		if (event->mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		{
			if (event->mouseWheelScroll.delta < 0)
			{
				view.zoom(1.1f);
				current_zoom *= 1.1f;
			}
			else
			{
				view.zoom(0.9f);
				current_zoom *= 0.9f;
			}
		}
		break;
	case sf::Event::KeyPressed:
		switch (event->key.code)
		{
		case sf::Keyboard::W:
			keys.W = true;
			break;
		case sf::Keyboard::A:
			keys.A = true;
			break;
		case sf::Keyboard::S:
			keys.S = true;
			break;
		case sf::Keyboard::D:
			keys.D = true;
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (event->key.code)
		{
		case sf::Keyboard::W:
			keys.W = false;
			break;
		case sf::Keyboard::A:
			keys.A = false;
			break;
		case sf::Keyboard::S:
			keys.S = false;
			break;
		case sf::Keyboard::D:
			keys.D = false;
			break;
		};
		break;
	}
}

template <class E>
void Board<E>::run()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			this->handler(&event);
		}

		window.setView(view);

		//Begin Drawing and updating
		window.clear();
		this->update();

		for (auto& k : chunkKeys)
		{
			window.draw(*chunks.at(k));
		}

		std::vector<std::future<void>> futures;
		for (auto& k : chunkKeys)
		{
			futures.push_back(std::async(&Chunk<E>::update, chunks.at(k))); //Update each chunk on a seperate thread, if possible
		}

		//Return to a single thread
		for (auto &f : futures)
		{
			f.get();
		}

		futures.clear();

		for (auto& k : chunkKeys)
		{
			chunks.at(k)->drawEntities(window);
		}

		window.display();

		Board::clean(); //Delete empty chunks and move entities to their correct chunks. Must be done on a single thread
	}
}

template <class E>
void Board<E>::checkEdges()
{
	std::vector<std::pair<std::shared_ptr<E>, Direction>> onEdges;

	for (auto& k : chunkKeys)
	{
		auto onChunkEdges = chunks.at(k)->getOnEdges();
		for (auto& ed : (*onChunkEdges))
		{
			onEdges.push_back(ed);
		}
	}

	for (auto& ed : onEdges)
	{
		int currentChunkPreHash = Chunk<E>::getPrehash(ed.first->getCenter());
		if (chunks.find(currentChunkPreHash) != chunks.end())
		{
			auto adjacentChunks = chunks.at(currentChunkPreHash)->fromDirection(ed.second);
			for (auto adjacentChunkPos : *adjacentChunks)
			{
				int preHash = Chunk<E>::getPrehash(adjacentChunkPos);

				if (chunks.find(preHash) != chunks.end())
				{
					chunks.at(preHash)->externalCheck(ed.first);
				}
			}
		}
	}
}

template <class E>
void Board<E>::checkMoved()
{
	std::vector<std::shared_ptr<E>> toBeMoved;

	if (chunkKeys.size() > 0) //Can't allocate based on entities per chunk if there are no chunks
	{
		//Assume the first chunk is representative of all chunks, and that less than half of the entities would leave the chunk during a given loop
		toBeMoved.reserve(chunkKeys.size() * chunks.at(chunkKeys.at(0))->getNumEntities() / 2);
		//If this assumption is incorrect, the vector will reallocate (but only a few times, since it has already been reserved)

		//Basically, overallocate memory so we don't have to worry about re-acllocating our vector multiple times mid loop
	}

	for (auto& k : chunkKeys)
	{
		auto chunkOutOfBounds = chunks.at(k)->getOutOfBounds();
		for (auto& e : (*chunkOutOfBounds))
		{
			toBeMoved.push_back(e);
		}
	}

	for (auto& e : toBeMoved)
	{
		addEntity(e);
	}
}

template <class E>
void Board<E>::clean()
{
	checkEdges();
	checkMoved();
	auto it = chunkKeys.begin();
	while (it != chunkKeys.end())
	{
		if (chunks.at(*it)->hasNoEntities())
		{
			chunks.erase(*it);
			it = chunkKeys.erase(it);
		}
		else
		{
			chunks.at(*it)->clean();
			it++;
		}
	}

	auto isDead = [](auto& e) {return !e->isAlive(); };
	selected->erase(std::remove_if(selected->begin(), selected->end(), isDead), selected->end());
}

template <class E>
std::vector<std::shared_ptr<E>> Board<E>::getEntitiesWithin(sf::Vector2f pos1, sf::Vector2f pos2)
{
	sf::Vector2f start_pos;
	sf::Vector2f target_pos;

	if (pos1.x < pos2.x)
	{
		start_pos.x = pos1.x;
		target_pos.x = pos2.x;
	}
	else
	{
		start_pos.x = pos1.x;
		target_pos.x = pos2.x;
	}

	if (pos1.y < pos2.y)
	{
		start_pos.y = pos1.y;
		target_pos.y = pos2.y;
	}
	else
	{
		start_pos.y = pos2.y;
		target_pos.y = pos1.y;
	}

	std::vector<std::shared_ptr<Chunk<E>>> containing;

	while (start_pos.x < target_pos.x)
	{
		while (start_pos.y < target_pos.y)
		{
			int preHash = Chunk<E>::getPrehash(start_pos);
			if (chunks.find(preHash) != chunks.end())
			{
				containing.push_back(chunks.at(preHash));
			}
			start_pos.y += (float)Board::chunkSize;
		}
		start_pos.x += (float)Board::chunkSize;
	}

	auto entities_within = std::vector<std::shared_ptr<E>>();

	for (auto &c : chunks)
	{
		for (auto& e : c.second->entities)
		{
			if (selectionBox.getGlobalBounds().intersects(e->getGlobalBounds()))
			{
				entities_within.push_back(e);
			}
		}
	}

	return std::move(entities_within);
}