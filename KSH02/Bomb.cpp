#include "Bomb.h"
#include <stdio.h>

bool Bomb::isExplosive()
{
	if (ExplosiveTime<=0) {
		return true;
	}
	else {
		return false;
	}
}


