#pragma once
#include "Actor.h"

class Enemy : public Actor
{

public:
	Enemy() = default;
	
	inline int GetPosX() override { return PosX; }
	inline int GetPosY() override { return PosY; }
	inline int GetHP() override { return HP; }


	void setDefault(int x, int y) override;
	int TakeDamage(int indamage) override;
	void PosXMove(int inPosX);
	void PosYMove(int inPosY);

	bool MoveDir = false;
	bool isDead = false;
private:
	int PosX = 9;
	int PosY = 9;
	int HP = 1;
	const int defaultHp = 1;
};

