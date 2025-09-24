#include "GameManager.h"
#include <iostream>
#include <stdio.h>

GameManager::~GameManager()
{
	delete player;
	player = nullptr;
}

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

	Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(TileState::Player);

	
}

void GameManager::PrintMap()
{
	//플레이어 이동위치 동기화
	Map[player->GetPosY()][player->GetPosX()]= static_cast<int>(TileState::Player);

	for(int i=0;i<MapSize;i++){
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
	
	printf("스테이지를 시작합니다 !!\n");
	printf("모든적을 처치하세요\n");

	while (!isStageClear) {
		PrintMap();
		printf("원하는 행동을 메뉴에 맞게 입력해주세요.\n");
		printf("1.위  2.아래\n3.왼쪽 4.오른쪽\n");
		printf("5.폭탄설치\n6.스테이지 포기\n");
		std::cin >> PlayerSelect;
		
		Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(TileState::Road);

		switch (PlayerSelect)
		{
		case 1: 
			if (isPresentBomb) { //폭탄폭발 //isPresentBomb 폭탄이 존재하는지 bool 
				if (bomb->isExplosive()) { //isExplosive 폭탄이 타이머가 지나 터진상태인지
					ExplosiveTileChange(bomb->PosX, bomb->PosY); //폭발타일 변경
					bomb->ExplosiveTime = bomb->DefaultExplosiveTime; //폭발타이머 원래대로
				}
				else {
					
					printf("폭발 타이머 : %d\n",bomb->ExplosiveTime);
				}
			}
			else {
				bomb->ExplosiveRemoveTime--;
				ExplosiveTileRemove(bomb->PosX, bomb->PosY);
			}
			if (OnBomb) { //폭탄배치함수
				bomb->PosX = player->GetPosX(); //폭탄 XY 확정
				bomb->PosY = player->GetPosY();
				Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(TileState::Bomb);
				OnBomb = false; // 타일 배치하고 폭탄 설치상태 트리거 False
			}
			//움직일수 있으면 움직인다
			if (CanMove(player->GetPosX(), player->GetPosY()-1)) {
				player->PosYMove(-1);
			}
			else {
				printf("이동 불가능합니다 .\n");
			}
			break;
		case 2:	
			if (isPresentBomb) { 
				if (bomb->isExplosive()) {
					ExplosiveTileChange(bomb->PosX, bomb->PosY);
					bomb->ExplosiveTime = bomb->DefaultExplosiveTime;
				}
				else {
					printf("폭발 타이머 : %d\n", bomb->ExplosiveTime);
				}
			}
			else {
				bomb->ExplosiveRemoveTime--;
				ExplosiveTileRemove(bomb->PosX, bomb->PosY);
			}
			if (OnBomb) {
				bomb->PosX = player->GetPosX();
				bomb->PosY = player->GetPosY();
				Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(TileState::Bomb);
				OnBomb = false;
			}
			if (CanMove(player->GetPosX(), player->GetPosY()+1)) {
				player->PosYMove(+1);
			}
			else {
				printf("이동 불가능합니다 .\n");
			}
			break;
		case 3: 
			if(isPresentBomb){ 
				if (bomb->isExplosive()) {
					ExplosiveTileChange(bomb->PosX, bomb->PosY);
					bomb->ExplosiveTime = bomb->DefaultExplosiveTime;
				}
				else {
					printf("폭발 타이머 : %d\n", bomb->ExplosiveTime);
				}
			}
			else {
				bomb->ExplosiveRemoveTime--;
				ExplosiveTileRemove(bomb->PosX, bomb->PosY);
			}
			if (OnBomb) {
				bomb->PosX = player->GetPosX();
				bomb->PosY = player->GetPosY();
				Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(TileState::Bomb);
				OnBomb = false;
			}
			if (CanMove(player->GetPosX()-1, player->GetPosY())) {
				player->PosXMove(-1);
			}
			else {
				printf("이동 불가능합니다 .\n");
			}
			break;
		case 4: 
			if (isPresentBomb) { 
				if (bomb->isExplosive()) {
					ExplosiveTileChange(bomb->PosX, bomb->PosY);
					bomb->ExplosiveTime = bomb->DefaultExplosiveTime;
				}
				else {
					printf("폭발 타이머 : %d\n", bomb->ExplosiveTime);
				}
			}
			else {
				bomb->ExplosiveRemoveTime--;
				ExplosiveTileRemove(bomb->PosX, bomb->PosY);
			}
			if (OnBomb) {
				bomb->PosX = player->GetPosX();
				bomb->PosY = player->GetPosY();
				Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(TileState::Bomb);
				OnBomb = false;
			}
			if (CanMove(player->GetPosX()+1, player->GetPosY())) {
				player->PosXMove(+1);
			}
			else {
				printf("이동 불가능합니다 .\n");
			}
			break;
		case 5: 
			//다음 이동직전에 폭탄이 깔리도록 bool OnBomb isPresentBomb true;
			printf("현재 위치에 폭탄이 설치되었습니다.\n");
			//폭탄이 존재하면 안깔리도록  플레이어 최대폭탄수 1
			if (isPresentBomb) { printf("설치가 불가능합니다. 이미 존재\n"); }
			else { OnBomb = true; isPresentBomb = true; }
			break;
		case 6: printf("스테이지 포기\n");
			break;
		default: printf("유효하지 않은 메뉴 번호입니다.\n");
			break;
		}

	}
	
}


void GameManager::ExplosiveTileChange(int inPosX, int inPosY)
{

	Map[inPosY][inPosX] = static_cast<int>(TileState::HitBombEffect);
	
	for (int i = 0; i <= bomb->ExplosiveRange; i++) {
		if (UnBreakable(inPosX + i, inPosY)) {
			Map[inPosY][inPosX + i] = static_cast<int>(TileState::HitBombEffect);
		}
	}
	for (int i = 0; i <= bomb->ExplosiveRange; i++) {
		if (UnBreakable(inPosX - i, inPosY)) {
			Map[inPosY][inPosX - i] = static_cast<int>(TileState::HitBombEffect);
		}
	}
	for (int i = 0; i <= bomb->ExplosiveRange; i++) {
		if (UnBreakable(inPosX, inPosY + i)) {
			Map[inPosY+i][inPosX] = static_cast<int>(TileState::HitBombEffect);
		}
	}
	for (int i = 0; i <= bomb->ExplosiveRange; i++) {
		if (UnBreakable(inPosX, inPosY - i)) {
			Map[inPosY-i][inPosX ] = static_cast<int>(TileState::HitBombEffect);
		}
	}

	isPresentBomb = false;
	
}

void GameManager::ExplosiveTileRemove(int inPosX, int inPosY)
{
	if (bomb->ExplosiveRemoveTime <= 0) {
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (UnBreakable(inPosX + i, inPosY)) {
				Map[inPosY][inPosX + i] = static_cast<int>(TileState::Road);
			}
		}
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (UnBreakable(inPosX - i, inPosY)) {
				Map[inPosY][inPosX - i] = static_cast<int>(TileState::Road);
			}
		}
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (UnBreakable(inPosX, inPosY + i)) {
				Map[inPosY + i][inPosX] = static_cast<int>(TileState::Road);
			}
		}
		for (int i = bomb->ExplosiveRange; i >= 0; i--) {
			if (UnBreakable(inPosX, inPosY - i)) {
				Map[inPosY - i][inPosX] = static_cast<int>(TileState::Road);
			}
		}

		Map[inPosY][inPosX] = static_cast<int>(TileState::Road);
	}

	
}

bool GameManager::CanMove(int posX, int posY)
{
	bool CanMove = false;

	if (Map[posY][posX] == static_cast<int>(TileState::Wall) ||
		Map[posY][posX] == static_cast<int>(TileState::Bomb) ||
		Map[posY][posX] == static_cast<int>(TileState::Enemy)) {
		CanMove = false;
	}
	else {
		CanMove = true;
	}

	return CanMove;
}

bool GameManager::UnBreakable(int inPosX, int inPosY)
{
	bool CanBreak = true;
	if (Map[inPosY][inPosX] == static_cast<int>(TileState::Wall)) {
		CanBreak=false;
	}
	return CanBreak;
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
