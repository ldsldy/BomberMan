#pragma once

class Player
{
public:

	Player() = default;
	~Player();


	inline int GetPosX() { return PosX; }
	inline int GetPosY() { return PosY; }
	
	void PosXMove(int inPosX);
	void PosYMove(int inPosY);
	void PlaceBomb();

private:
	int PosX = 1;
	int PosY= 1;
	const int StartPosX = 1;
	const int StartPosY = 1;
};

