#pragma once

#include "Ray.hpp"

#include <unordered_map>

class TextureLibrary
{
	static std::unordered_map<const char*, Texture2D> Textures;

public:
	static Texture2D GetTexture(const char* fileName);
};