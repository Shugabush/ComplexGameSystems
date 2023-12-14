#include "Ray.hpp"
#include "Window.hpp"
#include "GameObject.h"
#include "Player.h"
#include "GameManager.h"

#include <vector>

int main()
{
	int screenWidth = 1280;
	int screenHeight = 720;

	raylib::Window window(screenWidth, screenHeight);

	GameManager* gm = new GameManager();

	Player* player = new Player();
	player->Texture = LoadTexture("Ships/ship_0000.png");
	player->Texture.width *= 2;
	player->Texture.height *= 2;
	gm->SpawnObject(player);

	SetTargetFPS(60);

	while (!window.ShouldClose())
	{
		ClearBackground(RAYWHITE);

		gm->Update(GetFrameTime());
		
		BeginDrawing();

		gm->Draw();

		EndDrawing();
	}

	return 0;
}