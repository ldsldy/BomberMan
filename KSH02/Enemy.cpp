#include "Enemy.h"
#include <stdio.h>
int Enemy::TakeDamage(int indamage)
{
	HP -= indamage;
	if (HP <= 0) {
		isDead = true;
		printf("적이 죽었습니다.\n");
	}
	
	return HP;
}

void Enemy::PosXMove(int inPosX)
{
	PosX += inPosX;
}

void Enemy::PosYMove(int inPosY)
{
	PosY += inPosY;
}