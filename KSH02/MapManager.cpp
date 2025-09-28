#include "MapManager.h"
#include <stdio.h>

//stage1 이니셜라이즈
void MapManager::InitializeMap1(Player* player, Enemy* enemy, Enemy* enemy2)
{
	RemainEnemy = Stage1RemainEnemy;
	player->setDefault(1,1);
	enemy->setDefault(9,9);
	enemy2->setDefault(5,1);
	enemy->isDead = false;
	enemy2->isDead = false;
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
	Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Enemy);
	Map[enemy2->GetPosY()][enemy2->GetPosX()] = static_cast<int>(MTileState::Enemy);
}
//stage2 이니셜라이즈
void MapManager::InitializeMap2(Player* player, Enemy* enemy, Enemy* enemy2)
{
	RemainEnemy = Stage2RemainEnemy;
	player->setDefault(1,1);
	enemy->setDefault(9,9);
	enemy2->setDefault(1,5);
	enemy->isDead = false;
	enemy2->isDead = false;
	for (int i = 0; i < MapSize; i++) {
		for (int j = 0; j < MapSize; j++) {
			if (i == MapSize - 1 || j == MapSize - 1 || i == 0 || j == 0) {
				Map[i][j] = static_cast<int>(MTileState::Wall);
			}
			else if (i%2==0&&j%2!=0) {
				Map[i][j] = static_cast<int>(MTileState::Wall);
			}
			else if(i % 2 == 0 && j % 2 == 0){
				Map[i][j] = static_cast<int>(MTileState::SoftRock);
			}
			else {
				Map[i][j] = static_cast<int>(MTileState::Road);
			}
			
		}
	}
	Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Enemy);
	Map[enemy2->GetPosY()][enemy2->GetPosX()] = static_cast<int>(MTileState::Enemy);
}
void MapManager::PrintMap(Player* player, Enemy* enemy1, Enemy* enemy2)
{
	printf("==================================================\n");
	printf("                  B O M B E R M A N               \n");
	printf("--------------------------------------------------\n");
	printf(" [P] HP: %-2d | [E] 남은 적: %-2d | [B] 폭탄 수: %d/%d \n",
		player->GetHP(), RemainEnemy, player->currentBombs, player->maxBombs);
	printf("==================================================\n");

	
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
			else if (Map[i][j] == static_cast<int>(MTileState::Bomb)) {
				printf("★ ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::ExplosiveWarning)) {
				printf("!  ");
			}
			else if (Map[i][j] == static_cast<int>(MTileState::HitBombEffect)) {
				printf("◆ ");
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


bool MapManager::CanMove(int posX, int posY) const
{
	bool CanMove = false;

	if (Map[posY][posX] == static_cast<int>(MTileState::Road)
		|| Map[posY][posX] == static_cast<int>(MTileState::ExplosiveWarning)) {
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

	
	if ((player->GetPosX() == inPosX) && (player->GetPosY() == inPosY)) {
		isHit = true;
	}

	return isHit;
}

bool MapManager::isEnemyHit(int inPosX, int inPosY, Enemy* enemy) const
{
	bool isHit = false;
	if (enemy && enemy->GetPosX() == inPosX && enemy->GetPosY() == inPosY) {
		isHit =true;
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
