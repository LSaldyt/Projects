#include "GUI.hpp"

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::add(std::string classifier, std::string identifier, std::shared_ptr<Widget> w)
{
	if (widgets.find(classifier) == widgets.end())
	{
		std::unordered_map<std::string, std::shared_ptr<Widget>> temp_map;
		temp_map.insert(std::make_pair(identifier, w));
		widgets.insert(std::make_pair(classifier, std::move(temp_map)));
	}
	else
	{
		widgets.at(classifier).insert(std::make_pair(identifier, w));
	}
}

void GUI::doDraw(sf::RenderTarget & target)
{
	for (auto& kv : widgets)
	{
		for (auto& kv2 : kv.second)
		{
			kv2.second->doDraw(target);
		}
	}
}

void GUI::update()
{
	for (auto& kv : widgets)
	{
		for (auto& kv2 : kv.second)
		{
			kv2.second->update();
		}
	}
}

void GUI::handler(sf::Event *)
{
}

sf::Vector2f GUI::relativeTo(std::string classifier, std::string identifier, Direction direction)
{
	auto pos = sf::Vector2f(0.0f, 0.0f);

	if (widgets.find(classifier) != widgets.end())
	{
		if (widgets.at(classifier).find(identifier) != widgets.at(classifier).end())
		{
			pos = widgets[classifier][identifier]->getPosition();
			switch (direction)
			{
			case Up:
				pos.y -= widgets[classifier][identifier]->getGlobalBounds().height;
				break;
			case Down:
				pos.y += widgets[classifier][identifier]->getGlobalBounds().height;
				break;
			case Left:
				pos.x -= widgets[classifier][identifier]->getGlobalBounds().width;
				break;
			case Right:
				pos.x += widgets[classifier][identifier]->getGlobalBounds().width;
				break;
			case UpLeft:
				pos.y -= widgets[classifier][identifier]->getGlobalBounds().height;
				pos.x -= widgets[classifier][identifier]->getGlobalBounds().width;
				break;
			case UpRight:
				pos.y -= widgets[classifier][identifier]->getGlobalBounds().height;
				pos.x += widgets[classifier][identifier]->getGlobalBounds().width;
				break;
			case DownLeft:
				pos.y += widgets[classifier][identifier]->getGlobalBounds().height;
				pos.x -= widgets[classifier][identifier]->getGlobalBounds().width;
				break;
			case DownRight:
				pos.y += widgets[classifier][identifier]->getGlobalBounds().height;
				pos.x += widgets[classifier][identifier]->getGlobalBounds().width;
				break;
			default:
				break;
			}
		}
	}

	return pos;
}
