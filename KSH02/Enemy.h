#pragma once
#include "Enemy.h"
class Enemy
{

public:
	Enemy() = default;
	Enemy(int posX,int posY)
		:PosX(posX),PosY(posY){}
inline int GetPosX() { return PosX; }
inline int GetPosY() { return PosY; }
inline int GetHP() { return HP; }


int TakeDamage(int indamage);
void PosXMove(int inPosX);
void PosYMove(int inPosY);

bool isDead = false;
private:

	int PosX = 1;
	int PosY = 9;
	int HP = 1;
};

