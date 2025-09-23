#include "GameManager.h"

#include <stdio.h>

void GameManager::InitializeMap()
{

	for (int i = 0; i < MapSize; i++) {
		for (int j = 0; j < MapSize; j++) {
			if (i == MapSize - 1 || j == MapSize - 1 || i==0||j==0) {
				Map[i][j] = static_cast<int>(TileState::Wall);
			}
			else if (i%2==0&&j%2==0) {
				Map[i][j] = static_cast<int>(TileState::Wall);
			}
			else {
				Map[i][j] = static_cast<int>(TileState::Road);
			}
			
		}
	}
	Map[player->GetPlayerStartPosY()][player->GetPlayerStartPosX()] = static_cast<int>(TileState::Player);

	
}

void GameManager::PrintMap()
{
	for (int i = 0; i < MapSize; i++) {
		for (int j = 0; j < MapSize; j++) {
			if (Map[i][j] == static_cast<int>(TileState::Road)) {
				printf("□ ");
			}
			else if (Map[i][j] == static_cast<int>(TileState::Wall)) {
				printf("■ ");
			}
			else if (Map[i][j] == static_cast<int>(TileState::SoftRock)) {
				printf("○ ");
			}
			else if (Map[i][j] == static_cast<int>(TileState::UnbreakableRock)) {
				printf("● ");
			}
			else if (Map[i][j] == static_cast<int>(TileState::Bomb)) {
				printf("★ ");
			}
			else if (Map[i][j] == static_cast<int>(TileState::HitBombEffect)) {
				printf("◆ ");
			}
			else if (Map[i][j] == static_cast<int>(TileState::NotHitBombEffect)) {
				printf("◇ ");
			}
			else if (Map[i][j] == static_cast<int>(TileState::Player)) {
				printf("◇ ");
			}
			else if (Map[i][j] == static_cast<int>(TileState::Enemy)) {
				printf("◇ ");
			}
			else {
				printf("E ");
				//들어오면안됨 유효하지않는값
			}
		}
		printf("\n");
	}
	printf("\n");
}

void GameManager::Clear()
{
	delete player;
	player = nullptr;
}

void GameManager::StagePlay()
{
}

bool GameManager::isClear()
{
	bool isClear = false;

	return isClear;
}

bool GameManager::isHit()
{
	bool isHit = false;

	return isHit;
}
