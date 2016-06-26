#pragma once
#include "Board.hpp"
#include "Ship.hpp"
#include "Projectile.hpp"
#include "ShipTemplate.hpp"
#include "GameGUI.hpp"
#include "ResourceManager.hpp"

class GameBoard :
	public Board<Entity>
{
public:
	ShipFrame buildTestFrame();
	GameBoard();
	~GameBoard();

	virtual void update();            
	virtual void handler(sf::Event*); 
	virtual void drawGUI();

	void purchaseShip(ShipTemplate &ship_template);

private:
	void deselect      ();
	void select        (sf::Vector2f worldPos);
	void startSelect   (sf::Vector2f worldPos);
	void setApproaches (sf::Vector2f worldPos);

	GameGUI    gui;
	Player     player;
	sf::Sprite template_sprite;

	ResourceManager resource_manager;
};
