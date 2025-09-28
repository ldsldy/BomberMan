#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"

enum class MTileState
{
	Road = 0,         // ��
	Wall = 1,         // �μ� �� ���� ��
	SoftRock = 10,    // �μ� �� �ִ� ��
	Bomb = 20,        // ��ź
	HitBombEffect = 21, // ���� ȿ��
	ExplosiveWarning = 30, // ���� ���
	Player = 50,      // �÷��̾�
	Enemy = 60        // ��
};
class MapManager
{

public:
	//�������� 1, 2 �ʱⰪ ����
	void InitializeMap1(Player* player,Enemy* enemy, Enemy* enemy2); // �ʱ�ʻ���
	void InitializeMap2(Player* player,Enemy* enemy,Enemy* enemy2); // �ʱ�ʻ���
	// ����ʻ��� ����Ʈ
	void PrintMap(Player* player, Enemy* enemy1, Enemy* enemy2);
	// --- �浹 �� ���� Ȯ�� �Լ� ---
	bool CanMove(int posX, int posY) const; // �ش� ��ǥ�� �̵� �������� Ȯ��
	bool CanBreak(int inPosX, int inPosY) const; // �ش� ��ǥ�� ��ź���� �ı� �������� Ȯ��
	bool isPlayerHit(int inPosX, int inPosY, Player* player) const; // �÷��̾ �¾Ҵ��� Ȯ��
	bool isEnemyHit(int inPosX, int inPosY, Enemy* enemy) const;   // ���� �¾Ҵ��� Ȯ��
	bool isBreakableHit(int inPosX, int inPosY) const; // �μ� �� �ִ� ���� �¾Ҵ��� Ȯ��
	// --- �� ������ ---
	const int Stage1RemainEnemy = 2; // �������� 1�� �� ��
	const int Stage2RemainEnemy = 2; // �������� 2�� �� ��
	int RemainEnemy; // ���� ���������� ���� ���� ��
	static const int MapSize = 11; // ���� ũ�� (11x11)
	int Map[MapSize][MapSize]; // �� Ÿ�� �����͸� �����ϴ� 2���� �迭
};
