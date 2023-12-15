#pragma once

#include "Enemy.h"

#include <vector>
#include <queue>

class EnemyManager
{
	std::queue<Enemy*> PendingEnemies;
	std::queue<Enemy*> DestroyedEnemies;

	bool UpdateTerminated;

public:

	std::vector<Enemy*> Enemies;

	void Update();
	void EarlyDraw();
	void Draw();
	void LateDraw();

	bool ShouldUpdate = true;

	void SpawnEnemy(Enemy* enemy);
	void DestroyEnemy(Enemy* enemy);
};