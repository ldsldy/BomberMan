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
	
	//int �� ������ ���ڵ������� ���ѷ���
	char PlayerSelect = -2;
	if (StageNum == 1) {
		mapManager.InitializeMap1(player, enemy, enemy2);
		mapManager.RemainEnemy = mapManager.Stage1RemainEnemy;
	}
	else if (StageNum == 2) {
		mapManager.InitializeMap2(player, enemy, enemy2);
		mapManager.RemainEnemy = mapManager.Stage2RemainEnemy;
	}

	printf("���������� �����մϴ� !!\n");
	printf("������� óġ�ϼ���\n");

	while (!isStageClear && !isStageFail) {
		//system("cls");
		mapManager.PrintMap(player,enemy,enemy2);
		printf("\n[�ൿ ����]\n");
		printf(" (W) �� �� (S) �Ʒ� �� (A) ���� �� (D) ������\n");
		printf(" (B) ��ź ��ġ �� (6) �������� ����\n");
		printf(" > ");


		/*====================================================================*/
		int countbomb;
		std::cout << "��ź ȿ���� ����� Ÿ���� ���� : " << StackedExplosiveEffectMap.size() << std::endl;
		if (StackedExplosiveEffectMap.size() > 0)
		{
			for (const auto& elem : StackedExplosiveEffectMap) {
				int x = elem.first.first;      // x��ǥ
				int y = elem.first.second;     // y��ǥ
				countbomb = elem.second;       // ��ø Ƚ��
			}
		}
			
		std::cout << "���� �÷��̾� ��ġ: (" << player->GetPosX() << "," << player->GetPosY() << ")" << std::endl;
		/*====================================================================*/



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
			printf("�������� ����\n");
			isStageFail = true;
			break;
		default: printf("��ȿ���� ���� �޴� ��ȣ�Դϴ�.\n");
			break;
		}
		if (StageNum == 1) {
			EnemyYMove(enemy);
			EnemyYMove(enemy2);
		}
		else if (StageNum == 2) {
			EnemyXMove(enemy);
			EnemyXMove(enemy2);
		}
		
	}
}

void GameManager::EnemyYMove(Enemy* enemy)
{
	//false �� -y���� true�� +y����
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
void GameManager::EnemyXMove(Enemy* enemy)
{
	//false �� -x���� true�� +x����
	if (enemy->MoveDir) {
		if (mapManager.CanMove(enemy->GetPosX()-1, enemy->GetPosY())) {
			mapManager.Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Road);
			enemy->PosXMove(-1);
			mapManager.Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Enemy);
		}
		else {
			enemy->MoveDir = false;
		}
	}
	else {
		if (mapManager.CanMove(enemy->GetPosX()+1, enemy->GetPosY())) {
			mapManager.Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Road);
			enemy->PosXMove(+1);
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
		//�÷��̾� �̵���ġ ����ȭ
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	}
	else {
		printf("�̵� �Ұ����մϴ� .\n");
	}
}

void GameManager::PlayerMoveXMinus()
{
	if (mapManager.CanMove(player->GetPosX() - 1, player->GetPosY())) {
		if (mapManager.Map[player->GetPosY()][player->GetPosX()] != static_cast<int>(MTileState::Bomb)) {
			mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Road);
		}
		player->PosXMove();
		//�÷��̾� �̵���ġ ����ȭ
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	}
	else {
		printf("�̵� �Ұ����մϴ� .\n");
	}
}

void GameManager::PlayerMoveYMinus()
{
	
	if (mapManager.CanMove(player->GetPosX(), player->GetPosY() + 1)) {
		if (mapManager.Map[player->GetPosY()][player->GetPosX()] != static_cast<int>(MTileState::Bomb)) {
			mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Road);
		}
		player->PosYMove();
		//�÷��̾� �̵���ġ ����ȭ
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	}
	else {
		printf("�̵� �Ұ����մϴ� .\n");
	}
}

void GameManager::PlayerMoveYPlus()
{
	//�÷��̾� ������ġ
	if (mapManager.CanMove(player->GetPosX(), player->GetPosY() - 1)) {
		if (mapManager.Map[player->GetPosY()][player->GetPosX()] != static_cast<int>(MTileState::Bomb)) {
			mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Road);
		}
		player->PosYMove();
		//�÷��̾� �̵���ġ ����ȭ
		mapManager.Map[player->GetPosY()][player->GetPosX()] = static_cast<int>(MTileState::Player);
	}
	else {
		printf("�̵� �Ұ����մϴ� .\n");
	}
}

void GameManager::StageMenu()
{
	char MenuNumber = 0;
	while (MenuNumber != 'E'&& MenuNumber != 'e')
	{
		system("cls"); // �޴� ǥ�� �� ȭ�� �����
		isStageClear = false;
		isStageFail = false;
		printf("==================================================\n");
		printf("##                 BOMBER MAN                 ##\n");
		printf("==================================================\n");
		printf("   [1] �������� 1 ����\n");
		printf("   [2] �������� 2 ����\n");
		printf("   [3] ���׷��̵� (���� Ƚ��: %d)\n", player->UpgradeChance);
		printf("   [E] ���� ����\n");
		printf("--------------------------------------------------\n");
		printf(" > ");

		std::cin >> MenuNumber;
		switch (MenuNumber) {
		case '1': StagePlay(MenuNumber-'0');
			break;
		case '2': StagePlay(MenuNumber-'0');
			break;
		case '3': 
			printf("���� ���׷��̵� ����Ƚ���� : %d �Դϴ�\n", player->UpgradeChance);
			printf("���׷��̵� Ƚ���� �Ҹ��Ͽ� ��ź ������ ���׷��̵� �Ͻðڽ��ϱ�?\n");
			printf("[ 1.��ź ���� ���� ] [ 2.�ִ� ��ź ���� ���� ] [ 3.��� ]\n");
			std::cin >> MenuNumber;
			if (MenuNumber == '1'&&player->UpgradeChance>0) {
				// �÷��̾��� bombRange�� ������Ű�� UpgradeChance�� �Ҹ��մϴ�.
				player->bombRange++;
				player->UpgradeChance--;
				printf("��ź ������ %d (��)�� ���׷��̵�Ǿ����ϴ�.\n", player->bombRange);
			}
			else if (MenuNumber == '2'&& player->UpgradeChance > 0) {
				player->maxBombs++;
				player->UpgradeChance--;
				printf("�ִ� ��ź ������ %d �� �Ǿ����ϴ�.\n", player->maxBombs);
			}
			else {
				printf("���׷��̵� Ƚ���� �����մϴ� : %d\n", player->UpgradeChance);
			}
			printf("����Ϸ��� ����\n");
			getchar(); getchar();
			//fflush(stdin);
			break;
		default: 
			MenuNumber = 'E';
			break;
		}
	}
}

void GameManager::BombStateCheck()
{
	for (auto it = bombs.begin(); it != bombs.end(); ) {
		Bomb* bomb = *it;

		//PreviewExplosion(bomb);
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
		printf("���� ��ġ�� ��ź�� ��ġ�Ǿ����ϴ�.\n");
		PreviewExplosion(newBomb);
	}
	else {
		printf("��ġ�� �Ұ����մϴ�. �ִ� ��ź ���� �ʰ�\n");
	}
}

void GameManager::ExplosiveRangeInDirection(Bomb* bomb, int StartX, int StartY, int DirX, int DirY)
{
	for (int i = 1; i <= bomb->ExplosiveRange; i++) {
		int Dx = StartX + i * DirX;
		int Dy = StartY + i * DirY;
		if (mapManager.CanBreak(Dx, Dy)) {
			if (isHit(Dx, Dy)) {
				mapManager.Map[Dx][Dy] = static_cast<int>(MTileState::ExplosiveWarning);
				bomb->changedTiles.push_back({ Dx, Dy });
				break;
			}
			mapManager.Map[Dy][Dx] = static_cast<int>(MTileState::ExplosiveWarning);
		}
		else {
			break;
		}
	}
}

// ���� ������ �̸� �����ְ� ������ changedTiles�� ����
void GameManager::PreviewExplosion(Bomb* bomb)
{
	int inPosX = bomb->PosX;
	int inPosY = bomb->PosY;

	if (mapManager.CanBreak(inPosX, inPosY)) {
		//isHit(inPosX, inPosY);
		mapManager.Map[inPosY][inPosX] = static_cast<int>(MTileState::ExplosiveWarning);
		bomb->changedTiles.push_back({ inPosX, inPosY });//�ٲ�� Ÿ��  ��� x,y������ ����
	}

	ExplosiveRangeInDirection(bomb, inPosX, inPosY, 1, 0);
	ExplosiveRangeInDirection(bomb, inPosX, inPosY, -1, 0);
	ExplosiveRangeInDirection(bomb, inPosX, inPosY, 0, 1);
	ExplosiveRangeInDirection(bomb, inPosX, inPosY, 0, -1);
}

//�ϴ� ���� ���� ������ ���� ȿ���� �����ϰ� StackedExplosiveEffectMap�� ��ø Ƚ�� ����
void GameManager::ExplosiveTileChange(Bomb* bomb)
{
	std::cout << "���� ȿ�� ���� ��...\n";
	for (const auto& tilePos : bomb->changedTiles) {
		int x = tilePos.first;
		int y = tilePos.second;
		StackedExplosiveEffectMap[{x, y}]++;
		mapManager.Map[y][x] == static_cast<int>(MTileState::HitBombEffect);
		isHit(x, y);

		std::cout << "x:" << x << " y:" << y << std::endl;
	}
}

//����� changedTiles�� �̿��� ���� ȿ���� �����ϰ� ��ø �ϳ� ����
// ���� ��ø Ƚ���� 0�̶�� �ٽ� ��� �����ϰ� StackedExplosiveEffectMap���� ����
void GameManager::ExplosiveTileRemove(Bomb* bomb)
{
	std::cout << "���� ȿ�� ���� ��...\n";
	for (const auto& tilePos : bomb->changedTiles)
	{
		StackedExplosiveEffectMap[tilePos]--;
		if (StackedExplosiveEffectMap[tilePos] <= 0)
		{
			int x = tilePos.first;
			int y = tilePos.second;
			if (mapManager.Map[y][x] == static_cast<int>(MTileState::HitBombEffect))
			{
				mapManager.Map[y][x] = static_cast<int>(MTileState::Road);
			}
			StackedExplosiveEffectMap.erase(tilePos);

			std::cout << "x:" << x << " y:" << y << std::endl;
		}
	}
	bomb->changedTiles.clear(); 
}

bool GameManager::isHit(int inPosX, int inPosY)
{
	bool isBlockingHit = false; // ������ ���̳� ���� �������� Ȯ���ϴ� ����

	// --- 1. �÷��̾� �ǰ� ó�� ---
	if (mapManager.isPlayerHit(inPosX, inPosY, player)) {
		player->TakeDamage(1);
		printf("�÷��̾ �¾ҽ��ϴ� : %d\n", player->GetHP());
		if (player->isDead == true) {
			player->isDead = false; // ���� ���������� ���� ����
			printf("�������� Ŭ���� ����!\n");
			isStageFail = true;
		}
	}

	// --- 2. �� �ǰ� ó�� ---
	// �� 1
	if (!enemy->isDead && mapManager.isEnemyHit(inPosX, inPosY, enemy)) {
		enemy->TakeDamage(1);
		isBlockingHit = true;
		printf("[ ��1�� �¾ҽ��ϴ� : %d ]\n", enemy->GetHP());
		if (enemy->isDead == true) {
			mapManager.Map[enemy->GetPosY()][enemy->GetPosX()] = static_cast<int>(MTileState::Road);
			enemy->isDead = false;
			enemy->setDefault(20, 20); // �� ������ �̵����� ��Ȱ��ȭ
			mapManager.RemainEnemy--;
		}
	}
	// �� 2
	if (!enemy2->isDead && mapManager.isEnemyHit(inPosX, inPosY, enemy2)) {
		enemy2->TakeDamage(1);
		isBlockingHit = true;
		printf("[ ��2�� �¾ҽ��ϴ� : %d ]\n", enemy2->GetHP());
		if (enemy2->isDead == true) {
			mapManager.Map[enemy2->GetPosY()][enemy2->GetPosX()] = static_cast<int>(MTileState::Road);
			enemy2->isDead = false;
			enemy2->setDefault(20, 20); // �� ������ �̵����� ��Ȱ��ȭ
			mapManager.RemainEnemy--;
		}
	}

	// --- 3. �μ� �� �ִ� �� �ǰ� ó�� ---
	if (mapManager.isBreakableHit(inPosX, inPosY)) {
		if (mapManager.Map[inPosY][inPosX] == static_cast<int>(MTileState::SoftRock)) {
			mapManager.Map[inPosY][inPosX] = static_cast<int>(MTileState::Road);
			isBlockingHit = true;
		}
	}

	// --- 4. �������� Ŭ���� ó�� ---
	// ��� ���� óġ�߰�, ���� Ŭ���� ó���� ���� �ʾҴٸ� ����
	if (mapManager.RemainEnemy <= 0 && !isStageClear) {
		isStageClear = true; // �ߺ� ���� ����
		printf("�ظ�� ���� óġ�߽��ϴ�\n");
		printf("�ؽ������� Ŭ����!\n");
		player->UpgradeChance++;
		printf("���׷��̵� Ƚ�� : %d\n", player->UpgradeChance);
		mapManager.PrintMap(player,enemy,enemy2);
		printf("[ ����Ϸ��� ���� ]\n");
		// ���ۿ� �������� �� �ִ� ���� ���ڸ� ó���ϱ� ���� getchar()�� �� �� ȣ��
		getchar();
		getchar();
	}

	return isBlockingHit;
}
