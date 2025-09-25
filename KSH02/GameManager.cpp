#include "GameManager.h"
#include <iostream>
#include <stdio.h>

GameManager::~GameManager()
{
	delete player;
	player = nullptr;
}

void GameManager::Clear()
{
	delete bomb;
	bomb = nullptr;
	delete enemy;
	enemy = nullptr;
	delete player;
	player = nullptr;


}

void GameManager::StagePlay()
{
	int PlayerSelect=-2;
	mapManager.InitializeMap();
	printf("스테이지를 시작합니다 !!\n");
	printf("모든적을 처치하세요\n");

	while (!isStageClear) {
		mapManager.PrintMap(player, enemy);
		//PrintMap();
		printf("원하는 행동을 메뉴에 맞게 입력해주세요.\n");
		printf("1.위  2.아래\n3.왼쪽 4.오른쪽\n");
		printf("5.폭탄설치\n6.스테이지 포기\n");
		std::cin >> PlayerSelect;

		//플레이어 현재위치
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Road);
		
		switch (PlayerSelect)
		{
		case 1: 
			BombStateCheck();
			PlaceBomb();
			PlayerMoveYPlus();
			break;
		case 2:	
			BombStateCheck();
			PlaceBomb();
			PlayerMoveYMinus();
			break;
		case 3: 
			BombStateCheck();
			PlaceBomb();
			PlayerMoveXMinus();
			break;
		case 4: 
			BombStateCheck();
			PlaceBomb();
			PlayerMoveXPlus();
			
			break;
		case 5: 
			//다음 이동직전에 폭탄이 깔리도록 bool OnBomb isPresentBomb true;
			//폭탄이 존재하면 안깔리도록  플레이어 최대폭탄수 1
			if (isPresentBomb || WasPresentBomb) {
				printf("설치가 불가능합니다. 이미 존재\n");
			}
			else { OnBomb = true; isPresentBomb = true;		
			printf("현재 위치에 폭탄이 설치되었습니다.\n");
			}
			break;
		case 6: printf("스테이지 포기\n");
			break;
		default: printf("유효하지 않은 메뉴 번호입니다.\n");
			break;
		}

	}
	mapManager.PrintMap(player, enemy);
	
}

void GameManager::PlayerMoveXPlus()
{
	if (mapManager.CanMove(player->GetPosX() + 1, player->GetPosY())) {
		player->PosXMove(+1);
	}
	else {
		printf("이동 불가능합니다 .\n");
	}
}

void GameManager::PlayerMoveXMinus()
{
	if (mapManager.CanMove(player->GetPosX() - 1, player->GetPosY())) {
		player->PosXMove(-1);
	}
	else {
		printf("이동 불가능합니다 .\n");
	}
}

void GameManager::PlayerMoveYMinus()
{
	if (mapManager.CanMove(player->GetPosX(), player->GetPosY() + 1)) {
		player->PosYMove(+1);
	}
	else {
		printf("이동 불가능합니다 .\n");
	}
}

void GameManager::PlayerMoveYPlus()
{
	if (mapManager.CanMove(player->GetPosX(), player->GetPosY() - 1)) {
		player->PosYMove(-1);
	}
	else {
		printf("이동 불가능합니다 .\n");
	}
}

void GameManager::BombStateCheck()
{

	if (isPresentBomb) {
		bomb->ExplosiveTime--;
		printf("폭발 타이머 : %d\n", bomb->ExplosiveTime);
		if (bomb->isExplosive()) {
			ExplosiveTileChange(bomb->PosX, bomb->PosY);
			bomb->ExplosiveTime = bomb->DefaultExplosiveTime;
		}
	}
	
	if (WasPresentBomb) {
		bomb->ExplosiveRemoveTime--;
		printf("폭발 제거타이머 : %d\n", bomb->ExplosiveRemoveTime);
		if (bomb->ExplosiveRemoveTime == 0) {
			ExplosiveTileRemove(bomb->PosX, bomb->PosY);
			bomb->ExplosiveRemoveTime = bomb->DefaultExplosiveRemoveTime;
		}
	}
}

void GameManager::PlaceBomb()
{
	if (OnBomb) { //폭탄배치함수
		bomb->PosX = player->GetPosX(); //폭탄 XY 확정
		bomb->PosY = player->GetPosY();
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Bomb);
		OnBomb = false; // 타일 배치하고 폭탄 설치상태 트리거 False
	}
}

void GameManager::StageMenu()
{
	int MenuNumber = -2;
	while (MenuNumber!=-1)
	{
		printf("봄버맨\n");
		printf("[1. Stage1 2. Stage2 ]\n");
		printf("[-1입력시 종료]\n");
		std::cin >> MenuNumber;
		switch (MenuNumber) {
		case 1: StagePlay();
			break;
		case 2: StagePlay();
			break;
		default:
			break;
		}
	}
	

}


void GameManager::ExplosiveTileChange(int inPosX, int inPosY)
{
	if (mapManager.UnBreakable(inPosX, inPosY)) {
		isHit(inPosX, inPosY);
		mapManager.Map[inPosY][inPosX] = static_cast<int>(MTileState::HitBombEffect);
	}
	
	for (int i = 0; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.UnBreakable(inPosX + i, inPosY)) {
			isHit(inPosX+i, inPosY);
			mapManager.Map[inPosY][inPosX + i] = static_cast<int>(MTileState::HitBombEffect);
		}
		else {
			break;
		}
	}
	for (int i = 0; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.UnBreakable(inPosX - i, inPosY)) {
			isHit(inPosX - i, inPosY);
			mapManager.Map[inPosY][inPosX - i] = static_cast<int>(MTileState::HitBombEffect);
		}
		else {
			break;
		}
	}
	for (int i = 0; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.UnBreakable(inPosX, inPosY + i)) {
			isHit(inPosX, inPosY+i);
			mapManager.Map[inPosY+i][inPosX] = static_cast<int>(MTileState::HitBombEffect);
		}
		else {
			break;
		}
	}
	for (int i = 0; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.UnBreakable(inPosX, inPosY - i)) {
			isHit(inPosX, inPosY-i);
			mapManager.Map[inPosY-i][inPosX] = static_cast<int>(MTileState::HitBombEffect);
		}
		else {
			break;
		}
	}

	isPresentBomb = false;
	WasPresentBomb = true;
}

void GameManager::ExplosiveTileRemove(int inPosX, int inPosY)
{
	if (bomb->ExplosiveRemoveTime <= 0) {
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (mapManager.UnBreakable(inPosX + i, inPosY)) {
				mapManager.Map[inPosY][inPosX + i] = static_cast<int>(MTileState::Road);
			}
			
		}
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (mapManager.UnBreakable(inPosX - i, inPosY)) {
				mapManager.Map[inPosY][inPosX - i] = static_cast<int>(MTileState::Road);
			}
			
		}
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (mapManager.UnBreakable(inPosX, inPosY + i)) {
				mapManager.Map[inPosY + i][inPosX] = static_cast<int>(MTileState::Road);
			}
			
		}
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (mapManager.UnBreakable(inPosX, inPosY - i)) {
				mapManager.Map[inPosY - i][inPosX] = static_cast<int>(MTileState::Road);
			}
			
		}

		mapManager.Map[inPosY][inPosX] = static_cast<int>(MTileState::Road);
	}

	WasPresentBomb = false;
	
}


bool GameManager::isClear()
{
	bool isClear = false;

	return isClear;
}

void GameManager::isHit(int inPosX, int inPosY)
{
	if (mapManager.isPlayerHit(inPosX, inPosY)) {
		player->TakeDamage(1);
		printf("플레이어가 맞았습니다 : %d\n", player->GetHP());
	}
	if (mapManager.isEnemyHit(inPosX, inPosY)) {
		enemy->TakeDamage(1);
		if (enemy->isDead == true) {
			enemy->PosXMove(20);
			enemy->PosYMove(20);
			enemy->isDead = false;
			mapManager.RemainEnemy--;
			if (mapManager.RemainEnemy <= 0) {
				printf("모든 적을 처치했습니다\n");
				isStageClear = true;
			}
		}
		printf("적이 맞았습니다 : %d\n", enemy->GetHP());
	}
	if (mapManager.isBreakableHit(inPosX, inPosY)) {

	}
}

