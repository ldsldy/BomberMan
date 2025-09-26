#pragma once
class Actor
{
public:
	Actor() = default;
	virtual ~Actor()=default; // 소멸자에 virtual 추가

	virtual inline int GetPosX() = 0; // x좌표 반환
	virtual inline int GetPosY() = 0; // y좌표 반환
	virtual inline int GetHP() = 0;   // 체력(HP) 반환
	virtual void setDefault(int x, int y) = 0; // 기본 상태 설정
	virtual int TakeDamage(int indamage) = 0; // 데미지를 받는 처리
	virtual void PosXMove() {}; // x축 이동
	virtual void PosYMove() {}; // y축 이동

};

