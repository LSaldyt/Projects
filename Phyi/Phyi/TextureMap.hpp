#pragma once
#include "Includes.hpp"

class TextureMap
{
public:
	TextureMap();
	~TextureMap();

	const sf::Texture& get (std::string);

	void load        (std::string);
	void stripEnding (std::string &string);

private:
	std::unique_ptr<std::unordered_map<std::string, sf::Texture>> textures;
};

