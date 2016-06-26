#include "GameGUI.hpp"
#include "ShipButton.hpp"

GameGUI::GameGUI()
{
	current_template = NULL;
}

GameGUI::GameGUI(TextureMap &texture_map, Player* player) : GameGUI()
{
	texture_map.load("button.png");

	std::string last_classifier = "info";
	std::string last_identifier = "balance";

	add("info", "balance", std::make_shared<Button>(Button(texture_map.get("button"))));

	for (auto& kv : *(player->getTemplates()))
	{
		add("ships", kv.first, std::make_shared<ShipButton>(ShipButton(texture_map.get("button"), texture_map.get(kv.second.spriteLocation), relativeTo(last_classifier, last_identifier, Down))));
		last_identifier = kv.first;
		last_classifier = "ships";
	}

	this->player = player;
}

GameGUI::~GameGUI()
{
}

void GameGUI::doDraw(sf::RenderTarget & target)
{
	GUI::doDraw(target);
}

void GameGUI::update()
{
	GUI::update();
}

void GameGUI::handler(sf::Event *event, sf::RenderTarget& target)
{
	if (event->type == sf::Event::MouseButtonPressed)
	{
		for (auto& kv : widgets.at("ships"))
		{
			if (kv.second->clickedOn(target.mapPixelToCoords(sf::Vector2i(event->mouseButton.x, event->mouseButton.y))))
			{
				if (player->getTemplates()->find(kv.first) != player->getTemplates()->end())
				{
					if (current_template != &player->getTemplates()->at(kv.first))
					{
						current_template = &player->getTemplates()->at(kv.first);
					}
					else
					{
						current_template = NULL;
					}
				}
			}
		}
	}
	if (event->type == sf::Event::KeyPressed)
	{
		switch (event->key.code)
		{
		case sf::Keyboard::Escape:
			current_template = NULL;
			break;
		}
	}
}
