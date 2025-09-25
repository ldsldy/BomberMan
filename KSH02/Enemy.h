#pragma once
#include "Enemy.h"
class Enemy
{

public:

inline int GetPosX() { return PosX; }
inline int GetPosY() { return PosY; }
inline int GetHP() { return HP; }


int TakeDamage(int indamage);
void PosXMove(int inPosX);
void PosYMove(int inPosY);

bool isDead = false;
private:

	int PosX = 9;
	int PosY = 9;
	int HP = 1;
};

