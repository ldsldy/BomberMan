#include "Bomb.h"
#include <stdio.h>

Bomb::Bomb(int range)
{
	ExplosiveRange = range;
}

bool Bomb::isExplosive()
{
	if (ExplosiveTime<=0) {
		return true;
	}
	else {
		return false;
	}
}


