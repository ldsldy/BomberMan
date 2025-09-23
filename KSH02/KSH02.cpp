#include <iostream>
#include <stdio.h>
#include "GameManager.h"

int main()
{
    GameManager gameManager;
    gameManager.InitializeMap();
    gameManager.PrintMap();
    gameManager.Clear();
}

