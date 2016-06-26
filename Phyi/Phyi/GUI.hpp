#pragma once
#include "Includes.hpp"
#include "Player.hpp"
#include "Widget.hpp"

class GUI
{
public:
	GUI();
	~GUI();

	void add(std::string, std::string, std::shared_ptr<Widget>);

	virtual void  doDraw(sf::RenderTarget& target);
	virtual void  update();
	virtual void  handler(sf::Event*);

	sf::Vector2f relativeTo(std::string, std::string, Direction);

protected:
	std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Widget>>> widgets;

	Player* player;
};

