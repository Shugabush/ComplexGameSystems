#include "EnemyManager.h"
#include "GameManager.h"

#include <thread>

void EnemyManager::Update()
{
	while (true)
	{
		if (UpdateTerminated) return;

		if (ShouldUpdate)
		{
			while (!PendingEnemies.empty())
			{
				Enemy* Enemy = PendingEnemies.front();
				Enemies.push_back(Enemy);
				PendingEnemies.pop();
			}

			while (!DestroyedEnemies.empty())
			{
				Enemy* Enemy = DestroyedEnemies.front();
				Enemies.erase(std::remove(Enemies.begin(), Enemies.end(), Enemy), Enemies.end());
				DestroyedEnemies.pop();
			}

			for (auto Enemy : Enemies)
			{
				Enemy->EarlyUpdate();
			}

			for (auto Enemy : Enemies)
			{
				Enemy->Update();
			}

			for (auto Enemy : Enemies)
			{
				Enemy->LateUpdate();
			}

			ShouldUpdate = false;
		}
	}
}

void EnemyManager::Draw()
{
	for (auto Enemy : Enemies)
	{
		Enemy->EarlyDraw();
	}

	for (auto Enemy : Enemies)
	{
		Enemy->Draw();
	}

	for (auto Enemy : Enemies)
	{
		Enemy->LateDraw();
	}
}

void EnemyManager::SpawnEnemy(Enemy* enemy)
{
	PendingEnemies.push(enemy);
}

void EnemyManager::DestroyEnemy(Enemy* enemy)
{
	DestroyedEnemies.push(enemy);
}