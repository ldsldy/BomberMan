#include "GameManager.h"
#include <iostream>
#include <stdio.h>

void GameManager::Clear()
{
	delete bomb;
	bomb = nullptr;
	delete enemy2;
	enemy2 = nullptr;
	delete enemy;
	enemy = nullptr;
	delete player;
	player = nullptr;
}


void GameManager::StagePlay(int StageNum)
{
	char PlayerSelect=-2;
	if (StageNum == 1) {
		mapManager.InitializeMap1(player,enemy,enemy2);
		mapManager.RemainEnemy = mapManager.Stage1RemainEnemy;
	}
	else if (StageNum == 2) {
		mapManager.InitializeMap2(player, enemy , enemy2);
		mapManager.RemainEnemy = mapManager.Stage2RemainEnemy;
	}
	
	printf("스테이지를 시작합니다 !!\n");
	printf("모든적을 처치하세요\n");

	while (!isStageClear && !isStageFail) {
		mapManager.PrintMap(player, enemy);
		printf("원하는 행동을 메뉴에 맞게 입력해주세요.\n");
		printf("1.위 [W(w)] 2.아래 [S(s)]\n3.왼쪽 [A(a)] 4.오른쪽 [D(d)]\n");
		printf("5.폭탄설치 [B(b)]\n6.스테이지 포기\n");
		std::cin >> PlayerSelect;
		KeyChange(PlayerSelect);
		
		switch (PlayerSelect)
		{
		case 1:
			player->ExpectedPosYMove(-1);
			BombStateCheck();
			PlaceBomb();
			PlayerMoveYPlus();
			break;
		case 2:
			player->ExpectedPosYMove(+1);
			BombStateCheck();
			PlaceBomb();
			PlayerMoveYMinus();
			break;
		case 3:
			player->ExpectedPosXMove(-1);
			BombStateCheck();
			PlaceBomb();
			PlayerMoveXMinus();
			break;
		case 4:
			player->ExpectedPosXMove(+1);
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
			else {
				OnBomb = true; isPresentBomb = true;
				printf("현재 위치에 폭탄이 설치되었습니다.\n");
			}
			break;
		case 6:
			printf("스테이지 포기\n");
			isStageFail = true;
			break;
		default: printf("유효하지 않은 메뉴 번호입니다.\n");
			break;
		}
		EnemyYMove(enemy);
		EnemyYMove(enemy2);

	}


	
}

void GameManager::EnemyYMove(Enemy* enemy)
{
	//false 는 -y방향 true는 +y방향
	if (enemy->MoveDir) {
		if (mapManager.CanMove(enemy->GetPosX(), enemy->GetPosY() - 1)) {
			mapManager.Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Road);
			enemy->PosYMove(-1);
			mapManager.Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Enemy);
		}
		else {
			enemy->MoveDir = false;
		}
	}
	else {
		if (mapManager.CanMove(enemy->GetPosX(), enemy->GetPosY() + 1)) {
			mapManager.Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Road);
			enemy->PosYMove(+1);
			mapManager.Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Enemy);
		}
		else {
			enemy->MoveDir = true;
		}
	}
	
	
	
}

void GameManager::KeyChange(char& PlayerSelect)
{
	if (PlayerSelect == 'W' || PlayerSelect == 'w') {
		PlayerSelect = 1;
	}
	else if (PlayerSelect == 'S' || PlayerSelect == 's') {
		PlayerSelect = 2;
	}
	else if (PlayerSelect == 'A' || PlayerSelect == 'a') {
		PlayerSelect = 3;
	}
	else if (PlayerSelect == 'D' || PlayerSelect == 'd') {
		PlayerSelect = 4;
	}
	else if (PlayerSelect == 'B' || PlayerSelect == 'b') {
		PlayerSelect = 5;
	}
	else {
		PlayerSelect -= '0';
	}

}

void GameManager::PlayerMoveXPlus()
{
	if (mapManager.CanMove(player->GetPosX() + 1, player->GetPosY())) {
		if (mapManager.Map[player->GetPosY()][player->GetPosX()] != static_cast<int>(MTileState::Bomb)) {
			mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Road);
		}
		player->PosXMove();
		//플레이어 이동위치 동기화
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	}
	else {
		printf("이동 불가능합니다 .\n");
	}
}

void GameManager::PlayerMoveXMinus()
{
	if (mapManager.CanMove(player->GetPosX() - 1, player->GetPosY())) {
		if (mapManager.Map[player->GetPosY()][player->GetPosX()] != static_cast<int>(MTileState::Bomb)) {
			mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Road);
		}
		player->PosXMove();
		//플레이어 이동위치 동기화
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	}
	else {
		printf("이동 불가능합니다 .\n");
	}
}

void GameManager::PlayerMoveYMinus()
{
	
	if (mapManager.CanMove(player->GetPosX(), player->GetPosY() + 1)) {
		if (mapManager.Map[player->GetPosY()][player->GetPosX()] != static_cast<int>(MTileState::Bomb)) {
			mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Road);
		}
		player->PosYMove();
		//플레이어 이동위치 동기화
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	}
	else {
		printf("이동 불가능합니다 .\n");
	}
}

void GameManager::PlayerMoveYPlus()
{
	//플레이어 현재위치
	if (mapManager.CanMove(player->GetPosX(), player->GetPosY() - 1)) {
		if (mapManager.Map[player->GetPosY()][player->GetPosX()] != static_cast<int>(MTileState::Bomb)) {
			mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Road);
		}
		player->PosYMove();
		//플레이어 이동위치 동기화
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	}
	else {
		printf("이동 불가능합니다 .\n");
	}
}

void GameManager::BombStateCheck()
{

	if (isPresentBomb) {
		bomb->ExplosiveTime--;
		printf("[ 폭발 타이머 : %d ]\n", bomb->ExplosiveTime);
		if (bomb->isExplosive()) {
			ExplosiveTileChange(bomb->PosX, bomb->PosY);
			bomb->ExplosiveTime = bomb->DefaultExplosiveTime;
		}
	}
	
	if (WasPresentBomb) {
		bomb->ExplosiveRemoveTime--;
		printf("[ 폭발 제거타이머 : %d ]\n", bomb->ExplosiveRemoveTime);
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
		isStageClear = false;
		isStageFail = false;
		printf("봄버맨\n");
		printf("[ 1. Stage1 2. Stage2 3.폭탄 범위 업그레이드 ]\n");
		printf("[ -1입력시 종료 ]\n");
		std::cin >> MenuNumber;
		switch (MenuNumber) {
		case 1: StagePlay(MenuNumber);
			break;
		case 2: StagePlay(MenuNumber);
			break;
		case 3: 
			printf("현재 업그레이드 가능횟수는 : %d 입니다\n", player->UpgradeChance);
			printf("업그레이드 횟수를 소모하여 폭탄범위를 업그레이드 하시겠습니까?\n");
			printf("[ 1.Yes ] [ 2.NO ]\n");
			std::cin >> MenuNumber;
			if (MenuNumber == 1) {
				if (player->UpgradeChance <= 0) {
					printf("횟수가 부족합니다.\n");
				}
				else {
					bomb->ExplosiveRange++;
					player->UpgradeChance--;
					printf("범위가 %d 가 되었습니다.\n", bomb->ExplosiveRange);
				}
			}
			break;
		default:
			break;
		}
	}
	

}


void GameManager::ExplosiveTileChange(int inPosX, int inPosY)
{
	if (mapManager.CanBreak(inPosX, inPosY)) {
		isHit(inPosX, inPosY);
		mapManager.Map[inPosY][inPosX] = static_cast<int>(MTileState::HitBombEffect);
	}
	
	for (int i = 1; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.CanBreak(inPosX + i, inPosY)) {
			if (isHit(inPosX + i, inPosY)) {
				break;
			}
			mapManager.Map[inPosY][inPosX + i] = static_cast<int>(MTileState::HitBombEffect);
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.CanBreak(inPosX - i, inPosY)) {
			if (isHit(inPosX - i, inPosY)) {
				break;
			}
			mapManager.Map[inPosY][inPosX - i] = static_cast<int>(MTileState::HitBombEffect);
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.CanBreak(inPosX, inPosY + i)) {
			if (isHit(inPosX, inPosY+i)) {
				break;
			}
			mapManager.Map[inPosY + i][inPosX] = static_cast<int>(MTileState::HitBombEffect);
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.CanBreak(inPosX, inPosY - i)) {
			if (isHit(inPosX, inPosY - i)) {
				break;
			}
			mapManager.Map[inPosY - i][inPosX] = static_cast<int>(MTileState::HitBombEffect);
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
			if (mapManager.CanBreak(inPosX + i, inPosY)) {
				mapManager.Map[inPosY][inPosX + i] = static_cast<int>(MTileState::Road);
			}
			
		}
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (mapManager.CanBreak(inPosX - i, inPosY)) {
				mapManager.Map[inPosY][inPosX - i] = static_cast<int>(MTileState::Road);
			}
			
		}
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (mapManager.CanBreak(inPosX, inPosY + i)) {
				mapManager.Map[inPosY + i][inPosX] = static_cast<int>(MTileState::Road);
			}
			
		}
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (mapManager.CanBreak(inPosX, inPosY - i)) {
				mapManager.Map[inPosY - i][inPosX] = static_cast<int>(MTileState::Road);
			}
			
		}

		mapManager.Map[inPosY][inPosX] = static_cast<int>(MTileState::Road);
	}

	WasPresentBomb = false;
	
}


bool GameManager::isHit(int inPosX, int inPosY)
{
	bool isHit = false;
	if (mapManager.isPlayerHit(inPosX, inPosY,player)) {
		player->TakeDamage(1);
		isHit = true;
		printf("플레이어가 맞았습니다 : %d\n", player->GetHP());
		if (player->isDead == true) {
			player->isDead = false;
			printf("스테이지 클리어 실패!\n");
			isStageFail = true;
		}
	}
	if (mapManager.isEnemyHit(inPosX, inPosY)) {
		enemy->TakeDamage(1);
		isHit = true;
		printf("[ 적이 맞았습니다 : %d ]\n", enemy->GetHP());
		if (enemy->isDead == true) {
			enemy->PosXMove(20);
			enemy->PosYMove(20);
			enemy->isDead = false;
			mapManager.RemainEnemy--;
			if (mapManager.RemainEnemy <= 0) {
				printf("※모든 적을 처치했습니다\n");
				printf("※스테이지 클리어!\n");
				player->UpgradeChance++;
				printf("업그레이드 횟수 : %d\n", player->UpgradeChance);
				mapManager.PrintMap(player, enemy);
				printf("[ 계속하려면 엔터 ]\n");
				getchar();
				getchar();
				isStageClear = true;
			}
		}
	}
	if (mapManager.isBreakableHit(inPosX, inPosY)) {
		if (mapManager.Map[inPosY][inPosX] == static_cast<int>(MTileState::SoftRock)) {
			mapManager.Map[inPosY][inPosX] = static_cast<int>(MTileState::Road);
			isHit = true;
		}
	}
	return isHit;
}

