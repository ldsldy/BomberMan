#include "GameManager.h"
#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>

void GameManager::Clear()
{
	for (Bomb* bomb : bombs)
	{
		delete bomb;
	}
	bombs.clear();
	delete enemy2;
	enemy2 = nullptr;
	delete enemy;
	enemy = nullptr;
	delete player;
	player = nullptr;
}

void GameManager::StagePlay(int StageNum)
{
	
	//int 로 받으니 문자들어왔을때 무한루프
	char PlayerSelect = -2;
	if (StageNum == 1) {
		mapManager.InitializeMap1(player, enemy, enemy2);
		mapManager.RemainEnemy = mapManager.Stage1RemainEnemy;
	}
	else if (StageNum == 2) {
		mapManager.InitializeMap2(player, enemy, enemy2);
		mapManager.RemainEnemy = mapManager.Stage2RemainEnemy;
	}

	printf("스테이지를 시작합니다 !!\n");
	printf("모든적을 처치하세요\n");

	while (!isStageClear && !isStageFail) {
		system("cls");
		mapManager.PrintMap(player,enemy,enemy2);
		printf("\n[행동 선택]\n");
		printf(" (W) 위 │ (S) 아래 │ (A) 왼쪽 │ (D) 오른쪽\n");
		printf(" (B) 폭탄 설치 │ (6) 스테이지 포기\n");
		printf(" > ");
		std::cin >> PlayerSelect;
		KeyChange(PlayerSelect);
		BombStateCheck();

		switch (PlayerSelect)
		{
		case 1:
			player->ExpectedPosYMove(-1);
			PlayerMoveYPlus();
			break;
		case 2:
			player->ExpectedPosYMove(+1);
			PlayerMoveYMinus();
			break;
		case 3:
			player->ExpectedPosXMove(-1);
			PlayerMoveXMinus();
			break;
		case 4:
			player->ExpectedPosXMove(+1);
			PlayerMoveXPlus();
			break;
		case 5:
			PlaceBomb();
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
	for (auto it = bombs.begin(); it != bombs.end(); ) {
		Bomb* bomb = *it;

		if (bomb->state == Bomb::BombState::Ticking) {
			bomb->ExplosiveTime--;
			if (bomb->isExplosive()) {
				ExplosiveTileChange(bomb);
				bomb->state = Bomb::BombState::Exploding;
			}
			it++;
		}
		else if (bomb->state == Bomb::BombState::Exploding) {
			bomb->ExplosiveRemoveTime--;
			if (bomb->ExplosiveRemoveTime <= 0) {
				ExplosiveTileRemove(bomb);
				delete bomb;
				it = bombs.erase(it);
				player->currentBombs--;
			}
			else {
				it++;
			}
		}
		else {
			it++;
		}
	}
}
void GameManager::PlaceBomb()
{
	if (player->currentBombs < player->maxBombs) {
		Bomb* newBomb = new Bomb(player->bombRange);
		newBomb->PosX = player->GetPosX();
		newBomb->PosY = player->GetPosY();
		bombs.push_back(newBomb);
		player->currentBombs++;
		mapManager.Map[newBomb->PosY][newBomb->PosX] = static_cast<int>(MTileState::Bomb);
		printf("현재 위치에 폭탄이 설치되었습니다.\n");
	}
	else {
		printf("설치가 불가능합니다. 최대 폭탄 개수 초과\n");
	}
}

void GameManager::StageMenu()
{
	char MenuNumber = 0;
	while (MenuNumber != -1)
	{
		system("cls"); // 메뉴 표시 전 화면 지우기
		isStageClear = false;
		isStageFail = false;
		printf("==================================================\n");
		printf("##                 BOMBER MAN                 ##\n");
		printf("==================================================\n");
		printf("   [1] 스테이지 1 시작\n");
		printf("   [2] 스테이지 2 시작\n");
		printf("   [3] 업그레이드 (남은 횟수: %d)\n", player->UpgradeChance);
		printf("   [-1] 게임 종료\n");
		printf("--------------------------------------------------\n");
		printf(" > ");

		std::cin >> MenuNumber;
		switch (MenuNumber) {
		case '1': StagePlay(MenuNumber-'0');
			break;
		case '2': StagePlay(MenuNumber-'0');
			break;
		case '3': 
			printf("현재 업그레이드 가능횟수는 : %d 입니다\n", player->UpgradeChance);
			printf("업그레이드 횟수를 소모하여 폭탄 범위를 업그레이드 하시겠습니까?\n");
			printf("[ 1.폭탄 범위 증가 ] [ 2.최대 폭탄 개수 증가 ] [ 3.취소 ]\n");
			std::cin >> MenuNumber;
			if (MenuNumber == '1'&&player->UpgradeChance>0) {
				// 플레이어의 bombRange를 증가시키고 UpgradeChance를 소모합니다.
				player->bombRange++;
				player->UpgradeChance--;
				printf("폭탄 범위가 %d (으)로 업그레이드되었습니다.\n", player->bombRange);
			}
			else if (MenuNumber == '2'&& player->UpgradeChance > 0) {
				player->maxBombs++;
				player->UpgradeChance--;
				printf("최대 폭탄 개수가 %d 가 되었습니다.\n", player->maxBombs);
			}
			else {
				printf("업그레이드 횟수가 부족합니다 : %d\n", player->UpgradeChance);
			}
			printf("계속하려면 엔터\n");
			getchar(); getchar();
			break;
		default:
			break;
		}
	}
}

void GameManager::ExplosiveTileChange(Bomb* bomb)
{
	int inPosX = bomb->PosX;
	int inPosY = bomb->PosY;

	if (mapManager.CanBreak(inPosX, inPosY)) {
		isHit(inPosX, inPosY);
		mapManager.Map[inPosY][inPosX] = static_cast<int>(MTileState::HitBombEffect);
		bomb->changedTiles.push_back({ inPosX, inPosY });
	}

	for (int i = 1; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.CanBreak(inPosX + i, inPosY)) {
			if (isHit(inPosX + i, inPosY)) {
				mapManager.Map[inPosY][inPosX + i] = static_cast<int>(MTileState::HitBombEffect);
				bomb->changedTiles.push_back({ inPosX + i, inPosY });
				break;
			}
			mapManager.Map[inPosY][inPosX + i] = static_cast<int>(MTileState::HitBombEffect);
			bomb->changedTiles.push_back({ inPosX + i, inPosY });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.CanBreak(inPosX - i, inPosY)) {
			if (isHit(inPosX - i, inPosY)) {
				mapManager.Map[inPosY][inPosX - i] = static_cast<int>(MTileState::HitBombEffect);
				bomb->changedTiles.push_back({ inPosX - i, inPosY });
				break;
			}
			mapManager.Map[inPosY][inPosX - i] = static_cast<int>(MTileState::HitBombEffect);
			bomb->changedTiles.push_back({ inPosX - i, inPosY });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.CanBreak(inPosX, inPosY + i)) {
			if (isHit(inPosX, inPosY + i)) {
				mapManager.Map[inPosY + i][inPosX] = static_cast<int>(MTileState::HitBombEffect);
				bomb->changedTiles.push_back({ inPosX, inPosY + i });
				break;
			}
			mapManager.Map[inPosY + i][inPosX] = static_cast<int>(MTileState::HitBombEffect);
			bomb->changedTiles.push_back({ inPosX, inPosY + i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= bomb->ExplosiveRange; i++) {
		if (mapManager.CanBreak(inPosX, inPosY - i)) {
			if (isHit(inPosX, inPosY - i)) {
				mapManager.Map[inPosY - i][inPosX] = static_cast<int>(MTileState::HitBombEffect);
				bomb->changedTiles.push_back({ inPosX, inPosY - i });
				break;
			}
			mapManager.Map[inPosY - i][inPosX] = static_cast<int>(MTileState::HitBombEffect);
			bomb->changedTiles.push_back({ inPosX, inPosY - i });
		}
		else {
			break;
		}
	}
}

void GameManager::ExplosiveTileRemove(Bomb* bomb)
{
	
	for (const auto& tilePos : bomb->changedTiles) {
		int x = tilePos.first;
		int y = tilePos.second;
		if (mapManager.Map[y][x] == static_cast<int>(MTileState::HitBombEffect)) {
			mapManager.Map[y][x] = static_cast<int>(MTileState::Road);
		}
	}
	bomb->changedTiles.clear(); 
}

bool GameManager::isHit(int inPosX, int inPosY)
{
	bool isBlockingHit = false; // 폭발이 벽이나 적에 막혔는지 확인하는 변수

	// --- 1. 플레이어 피격 처리 ---
	if (mapManager.isPlayerHit(inPosX, inPosY, player)) {
		player->TakeDamage(1);
		printf("플레이어가 맞았습니다 : %d\n", player->GetHP());
		if (player->isDead == true) {
			player->isDead = false; // 다음 스테이지를 위해 리셋
			printf("스테이지 클리어 실패!\n");
			isStageFail = true;
		}
	}

	// --- 2. 적 피격 처리 ---
	// 적 1
	if (!enemy->isDead && mapManager.isEnemyHit(inPosX, inPosY, enemy)) {
		enemy->TakeDamage(1);
		isBlockingHit = true;
		printf("[ 적1이 맞았습니다 : %d ]\n", enemy->GetHP());
		if (enemy->isDead == true) {
			mapManager.Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Road);
			enemy->isDead = false;
			enemy->setDefault(20, 20); // 맵 밖으로 이동시켜 비활성화
			mapManager.RemainEnemy--;
		}
	}
	// 적 2
	if (!enemy2->isDead && mapManager.isEnemyHit(inPosX, inPosY, enemy2)) {
		enemy2->TakeDamage(1);
		isBlockingHit = true;
		printf("[ 적2가 맞았습니다 : %d ]\n", enemy2->GetHP());
		if (enemy2->isDead == true) {
			mapManager.Map[enemy2->GetPosY()][enemy2->GetPosX()] = static_cast<int>(MTileState::Road);
			enemy2->isDead = false;
			enemy2->setDefault(20, 20); // 맵 밖으로 이동시켜 비활성화
			mapManager.RemainEnemy--;
		}
	}

	// --- 3. 부술 수 있는 벽 피격 처리 ---
	if (mapManager.isBreakableHit(inPosX, inPosY)) {
		if (mapManager.Map[inPosY][inPosX] == static_cast<int>(MTileState::SoftRock)) {
			mapManager.Map[inPosY][inPosX] = static_cast<int>(MTileState::Road);
			isBlockingHit = true;
		}
	}

	// --- 4. 스테이지 클리어 처리 ---
	// 모든 적을 처치했고, 아직 클리어 처리가 되지 않았다면 실행
	if (mapManager.RemainEnemy <= 0 && !isStageClear) {
		isStageClear = true; // 중복 실행 방지
		printf("※모든 적을 처치했습니다\n");
		printf("※스테이지 클리어!\n");
		player->UpgradeChance++;
		printf("업그레이드 횟수 : %d\n", player->UpgradeChance);
		mapManager.PrintMap(player,enemy,enemy2);
		printf("[ 계속하려면 엔터 ]\n");
		// 버퍼에 남아있을 수 있는 개행 문자를 처리하기 위해 getchar()를 두 번 호출
		getchar();
		getchar();
	}

	return isBlockingHit;
}
