#include "Ray.hpp"
#include "Window.hpp"
#include "GameObject.h"
#include "Player.h"
#include "GameManager.h"
#include "TextureLibary.h"

#include <vector>
#include <iostream>

int main()
{
	int screenWidth = 1280;
	int screenHeight = 720;

	raylib::Window window(screenWidth, screenHeight);

	GameManager* gm = new GameManager();

	Player* player = new Player();
	player->BulletCooldown = Timer(0.125f);
	player->Texture = TextureLibrary::GetTexture("Ships/ship_0000.png");
	player->BulletTexture = TextureLibrary::GetTexture("Tiles/tile_0000.png");
	player->Texture.width *= 2;
	player->Texture.height *= 2;
	player->Rotation = -PI / 2;
	gm->SpawnObject(player);

	gm->Init();

	Texture2D EnemyTexture = TextureLibrary::GetTexture("Ships/ship_0012.png");

	for (size_t i = 0; i < 25; i++)
	{
		Enemy* newEnemy = new Enemy();
		newEnemy->Texture = EnemyTexture;
		newEnemy->TargetObj = player;

		newEnemy->Position.x = (float)GetRandomValue(0, GetScreenWidth());
		newEnemy->Position.y = (float)GetRandomValue(0, GetScreenHeight());

		newEnemy->MovementSpeed = (float)GetRandomValue(20, 100) * 0.01f;

		newEnemy->Texture.width *= 2;
		newEnemy->Texture.height *= 2;
		gm->EM->SpawnEnemy(newEnemy);
	}

	SetTargetFPS(60);

	while (!window.ShouldClose())
	{
		ClearBackground(RAYWHITE);
		
		gm->Update();

		BeginDrawing();

		gm->Draw();

		EndDrawing();
	}

	return 0;
}