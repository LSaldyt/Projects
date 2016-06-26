#pragma once
#include "GUI.hpp"
#include "Button.hpp"
#include "TextureMap.hpp"
#include "Player.hpp"
#include "ShipTemplate.hpp"

class GameGUI :
	public GUI
{
public:
	GameGUI();
	GameGUI(TextureMap&, Player*);
	~GameGUI();

	virtual void  doDraw(sf::RenderTarget& target);
	virtual void  update();
	virtual void  handler(sf::Event*, sf::RenderTarget&);

	ShipTemplate* current_template;
};

