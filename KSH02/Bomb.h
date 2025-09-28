#pragma once
#include <vector>   
#include <utility>  
#include <map>
#include <set>
class Bomb
{
public:
	Bomb() = default;
	Bomb(int range); // �÷��̾��� ���׷��̵�� ������ �޾� ����
	bool isExplosive(); // ������ �ð����� Ȯ��
	// ��ź�� ����
	enum class BombState
	{
		Ticking,
		Exploding
	};
	// --- ��ź �Ӽ� ---
	int PosX = -1; // ��ġ�� x��ǥ
	int PosY = -1; // ��ġ�� y��ǥ
	int ExplosiveTime = 5; // ���߱��� ���� ��
	const int DefaultExplosiveTime = 5; // ���� �ð� �ʱⰪ
	int ExplosiveRemoveTime = 3; // ���� ȿ���� ���������� ���� ��
	const int DefaultExplosiveRemoveTime = 3; // ���� ȿ�� �ð� �ʱⰪ
	int ExplosiveRange = 2; // ���� ����

	BombState state = BombState::Ticking; // ���� ��ź ����
	std::vector<std::pair<int, int>> changedTiles; // ���߷� ���� ����� Ÿ�� ��ǥ ����;
};