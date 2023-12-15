#include "TextureLibary.h"

std::unordered_map<const char*, Texture2D> TextureLibrary::Textures;

Texture2D TextureLibrary::GetTexture(const char* fileName)
{
	if (Textures[fileName].id == 0)
	{
		// The texture hasn't been loaded or was invalid
		Textures[fileName] = LoadTexture(fileName);
	}
	return Textures[fileName];
}