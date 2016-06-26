#include "GameBoard.hpp"
#include "Module.hpp"
#include "Physics.hpp"
#include "Projectile.hpp"

ShipFrame GameBoard::buildTestFrame()
{
	ShipFrame test_frame(1, 1, 1, 1000, 1000, 100, 100);

	test_frame.add(std::make_shared<Module>(resource_manager.getModule("test_engine")));
	test_frame.add(std::make_shared<Module>(resource_manager.getModule("test_weapon")));
	test_frame.add(std::make_shared<Module>(resource_manager.getModule("test_defense")));

	return std::move(test_frame);
}

GameBoard::GameBoard()
{
	resource_manager.loadModules("test.csv");

	texture_map.load("shship.png");
	texture_map.load("projectile.png");

	Ship test_ship;

	auto test_frame = buildTestFrame();

	test_ship.setFrame(test_frame);

	test_ship.setPosition(400.0f, 400.0f);
	test_ship.setTexture(texture_map.get("shship"));
	addEntity(std::make_shared<Ship>(test_ship));

	/*
	for (int i = 0; i < 0; i++)
	{
		std::cout << i << std::endl;
		Projectile test_projectile(20, 10000);
		test_projectile.setTexture(textureMap.get("projectile"));
		test_projectile.setPosition(100.0f * i, 0.0f);
		addEntity(std::make_shared<Projectile>(test_projectile));
	}
	*/


	ShipTemplate cruiserTemplate{"shship", test_frame};

	player.add("cruiser", cruiserTemplate);

	gui = GameGUI(texture_map, &player);
	template_sprite.setColor(sf::Color(255, 255, 255, 164));
}

GameBoard::~GameBoard()
{
}

void GameBoard::update()
{
	Board::update();

	if (selecting)
	{
		window.draw(selectionBox);
	}
	else if (gui.current_template != NULL)
	{
		template_sprite.setTexture(texture_map.get(gui.current_template->spriteLocation));
		template_sprite.setOrigin(template_sprite.getGlobalBounds().width / 2.0f, template_sprite.getGlobalBounds().height / 2.0f);
		window.draw(template_sprite);
	}

	window.setView(gui_view);
	drawGUI();
	window.setView(view);
}

void GameBoard::handler(sf::Event *event)
{
	Board::handler(event);

	sf::Vector2f worldPos;

	switch (event->type)
	{
	case sf::Event::MouseButtonPressed:
		worldPos = window.mapPixelToCoords(sf::Vector2i(event->mouseButton.x, event->mouseButton.y));
		if (event->mouseButton.button == sf::Mouse::Right)
		{
			if (gui.current_template == NULL)
			{
				setApproaches(worldPos);
			}
		}
		else if (event->mouseButton.button == sf::Mouse::Left)
		{
			if (gui.current_template != NULL)
			{
				purchaseShip(*gui.current_template);
			}
			else
			{
				deselect();
				startSelect(worldPos);
			}
		}
	break;

	case sf::Event::MouseButtonReleased:
		worldPos = window.mapPixelToCoords(sf::Vector2i(event->mouseButton.x, event->mouseButton.y));
		if (event->mouseButton.button == sf::Mouse::Left)
		{
			select(worldPos);
		}
		
	break;

	case sf::Event::MouseMoved:
		worldPos = window.mapPixelToCoords(sf::Vector2i(event->mouseMove.x, event->mouseMove.y));
		if (selecting == true)
		{
			selectionBox.setSize(sf::Vector2f(worldPos.x - selectionBox.getPosition().x, worldPos.y - selectionBox.getPosition().y));
		}
		else if (gui.current_template != NULL)
		{
			template_sprite.setPosition(worldPos);
		}
	break;
	}


	window.setView(gui_view);
	gui.handler(event, window);
	window.setView(view);
}

void GameBoard::drawGUI()
{
	gui.doDraw(window);
	gui.update();
}

void GameBoard::purchaseShip(ShipTemplate &ship_template)
{
	if (player.funds > gui.current_template->frameType.getCost())
	{
		player.funds -= ship_template.frameType.getCost();

		Ship new_ship;

		new_ship.setFrame(ship_template.frameType);

		new_ship.setPosition(template_sprite.getPosition());
		new_ship.setTexture(texture_map.get(gui.current_template->spriteLocation));
		new_ship.setOwner("player");
		addEntity(std::make_shared<Ship>(new_ship));

		std::cout << player.funds << std::endl;
	}
}

void GameBoard::setApproaches(sf::Vector2f worldPos)
{
	for (auto &s : *selected)
	{
		s->setApproach(worldPos);
	}
}

void GameBoard::deselect()
{
	for (auto &e : *selected)
	{
		e->setColor(sf::Color::White);
	}
	selected->clear();
	selectionBox.setSize(sf::Vector2f(0.0f, 0.0f));
}

void GameBoard::startSelect(sf::Vector2f worldPos)
{
	selecting = true;
	selectionBox.setPosition(worldPos);
}

void GameBoard::select(sf::Vector2f worldPos)
{
	for (auto& e : getEntitiesWithin(selectionBox.getPosition(), worldPos))
	{
		selected->push_back(e);
	}

	selectionBox.setSize(sf::Vector2f(0.0f, 0.0f));
	selecting = false;

	for (auto &e : *selected)
	{
		e->setColor(sf::Color::Cyan);
	}
}


