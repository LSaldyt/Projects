#pragma once
#include "Widget.hpp"

class TextField :
	public Widget
{
public:
	TextField();
	TextField(sf::Font* set_font, std::string text, sf::Texture& texture, sf::Vector2f = sf::Vector2f(0.0f, 0.0f));
	~TextField();

	virtual void doDraw(sf::RenderTarget & target);

private:
	sf::Font* font;
	sf::Text  text;
};

