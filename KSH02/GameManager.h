#pragma once
#include "MapManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"
#include <vector>
#include <utility>
class GameManager
{
public:

	GameManager() = default;
	~GameManager()=default;
	// --- ���� ��ü�� ---
	MapManager mapManager;
	Player* player = new Player();
	Enemy* enemy = new Enemy();
	Enemy* enemy2 = new Enemy();
	//std::vector<Enemy*> Enemys;
	std::vector<Bomb*> bombs; // ���� ���� ��ź�� �����ϴ� ����

	// --- ���� �帧 ���� �Լ� ---
	void Clear(); // ���� ���� �� ���� �Ҵ�� �޸� ����
	void StagePlay(int StageNum); // ���� ���� �÷��̰� ����Ǵ� �Լ�
	void StageMenu(); // �������� ���� �� ���׷��̵� �޴�

	// --- ��ü�� �ൿ �Լ� ---
	void EnemyYMove(Enemy* enemy);
	void EnemyXMove(Enemy* enemy);
	void KeyChange(char& PlayerSelect); // ����� �Է�(char)�� ���� ����(int)���� ��ȯ
	void PlayerMoveXPlus();
	void PlayerMoveXMinus();
	void PlayerMoveYMinus();
	void PlayerMoveYPlus();
	// --- ��ź ���� ���� �Լ� ---
	void BombStateCheck(); // ��� ��ź�� ����(�ð� ����, ���� ��)�� ������Ʈ
	void PlaceBomb();
	void PreviewExplosion(Bomb* bomb);
	void ExplosiveRangeInDirection(Bomb* bomb, int StartX, int StartY, int DirX, int DirY); // Ư�� �������� ���� ���� ó��
	// �÷��̾� ��ġ�� ��ź ��ġ
	void ExplosiveTileChange(Bomb* bomb); // ���� ������ Ÿ���� ���� ȿ���� ����
	void ExplosiveTileRemove(Bomb* bomb); // ���� ȿ�� Ÿ���� �ٽ� ��� ����
	
	// --- ���� Ȯ�� �� Ʈ���� ---
	bool isHit(int inPosX, int inPosY); // Ư�� ��ǥ�� ��ź�� ����� �� �浹 ó��
	bool isStageClear = false;  // �������� Ŭ���� ����
	bool isStageFail = false;   // �������� ���� ����

private:
	std::map<std::pair<int, int>, int> StackedExplosiveEffectMap; // Ÿ�� ��ǥ�� ��ø�� Ƚ�� ����
	//std::map<std::set<Bomb*>, std::vector<std::pair<int, int>>> BombRangeMap; // �� ��ź�� ������ �ִ� Ÿ���� ���� ����
};

