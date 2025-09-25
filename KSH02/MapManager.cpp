#include "MapManager.h"
#include <stdio.h>

//stage1맵 이니셜라이즈
void MapManager::InitializeMap1()
{

	for (int i = 0; i < MapSize; i++) {
		for (int j = 0; j < MapSize; j++) {
			if (i == MapSize - 1 || j == MapSize - 1 || i == 0 || j == 0) {
				Map[i][j] = static_cast<int>(MTileState::Wall);
			}
			else if (i % 2 == 0 && j % 2 == 0) {
				Map[i][j] = static_cast<int>(MTileState::Wall);
			}
			else if (i % 2 != 0 && j % 2 == 0) {
				Map[i][j] = static_cast<int>(MTileState::SoftRock);
			}
			else {
				Map[i][j] = static_cast<int>(MTileState::Road);
			}
		}
	}
}
//stage2 이니셜라이즈
void MapManager::InitializeMap2()
{
	
	for (int i = 0; i < MapSize; i++) {
		for (int j = 0; j < MapSize; j++) {
			if (i == MapSize - 1 || j == MapSize - 1 || i == 0 || j == 0) {
				Map[i][j] = static_cast<int>(MTileState::Wall);
			}
			else if ((i == 3 || i == 7) && j % 2 == 0) {
				Map[i][j] = static_cast<int>(MTileState::Wall);
			}
			else if ((i == 1 || i == 5 || i == 9) && j % 2 != 0) {
				Map[i][j] = static_cast<int>(MTileState::Wall);
			}
			else if (i % 2 == 0 && j % 2 == 0) {
				Map[i][j] = static_cast<int>(MTileState::SoftRock);
			}
			else {
				Map[i][j] = static_cast<int>(MTileState::Road);
			}
		}
	}
}
void MapManager::PrintMap(Player* player, Enemy* enemy)
{
	//플레이어 이동위치 동기화
	Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Enemy);


	for (int i = 0; i < MapSize; i++) {
		for (int j = 0; j < MapSize; j++) {
			if (Map[i][j] == static_cast<int>(MTileState::Road)) {
				printf("□ ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::Wall)) {
				printf("■ ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::SoftRock)) {
				printf("▣ ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::UnbreakableRock)) {
				printf("● ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::Bomb)) {
				printf("★ ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::HitBombEffect)) {
				printf("◆ ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::NotHitBombEffect)) {
				printf("◇ ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::Player)) {
				printf("P  ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::Enemy)) {
				printf("E  ");
			}
			else {
				printf("Error ");
				//들어오면안됨 유효하지않는값
			}
		}
		printf("\n");
	}
	printf("\n");
}

void MapManager::TileStateChange(int posX,int posY, int TileState)
{
	if (static_cast<int>(MTileState::Bomb) == TileState) {
		Map[posY][posX] = TileState;
	}
	else if(static_cast<int>(MTileState::Wall) == TileState) {
		Map[posY][posX] = TileState;
	}
	else if (static_cast<int>(MTileState::SoftRock) == TileState) {
		Map[posY][posX] = TileState;
	}
	else if (static_cast<int>(MTileState::UnbreakableRock) == TileState) {
		Map[posY][posX] = TileState;
	}
	else if (static_cast<int>(MTileState::Bomb) == TileState) {
		Map[posY][posX] = TileState;
	}
	else if (static_cast<int>(MTileState::HitBombEffect) == TileState) {
		Map[posY][posX] = TileState;
	}
	else if (static_cast<int>(MTileState::NotHitBombEffect) == TileState) {
		Map[posY][posX] = TileState;
	}
	else if (static_cast<int>(MTileState::Player) == TileState) {
		Map[posY][posX] = TileState;
	}
	else if (static_cast<int>(MTileState::Enemy) == TileState) {
		Map[posY][posX] = TileState;
	}
	else {
		//오류
	}

}

bool MapManager::CanMove(int posX, int posY) const
{
	bool CanMove = false;

	if (Map[posY][posX] == static_cast<int>(MTileState::Road)) {
		CanMove = true;
	}
	else {
		CanMove = false;
	}

	return CanMove;
}
//폭탄이 부술수 없는곳 리턴
bool MapManager::CanBreak(int inPosX, int inPosY) const
{
	bool CanBreak = true;
	if (Map[inPosY][inPosX] == static_cast<int>(MTileState::Wall) ||
		(inPosY >= MapSize || inPosX >= MapSize || inPosY < 0 || inPosX < 0)) {
		CanBreak = false;
	}
	return CanBreak;
}


bool MapManager::isPlayerHit(int inPosX, int inPosY ,Player* player) const
{
	bool isHit = false;

	if ((player->ExpectedGetPosX() == inPosX)&& (player->ExpectedGetPosY() == inPosY)) {
		isHit = true;
	}

	return isHit;
}

bool MapManager::isEnemyHit(int inPosX, int inPosY) const
{
	bool isHit = false;
	if (Map[inPosY][inPosX] == static_cast<int>(MTileState::Enemy)) {
		isHit = true;
	}

	return isHit;
}

bool MapManager::isBreakableHit(int inPosX, int inPosY) const
{
	bool isHit = false;

	if (Map[inPosY][inPosX] == static_cast<int>(MTileState::SoftRock)) {
		isHit = true;
	}

	return isHit;
}
