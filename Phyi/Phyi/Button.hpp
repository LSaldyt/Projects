#pragma once
#include "Widget.hpp"
class Button :
	public Widget
{
public:
	Button();
	Button(const sf::Texture& text, sf::Vector2f = sf::Vector2f(0.0f, 0.0f));
	~Button();
};

