#pragma once

class Manager;
class Car;
class Track;
class StatsTab;

class Block
{
public:
	Block();
	~Block();

	virtual void DrawBlock(Manager* p1,int ScreenHeight)=0;

	virtual bool DeleteCheck() = 0;

	virtual void Move(float fCurvature, float fSpeed, float fElapsedTime, int ScreenHeight, int ScreenWidth)=0;

	void CollisionCheck(Car* pCar,int nCarPos);
	
	virtual void ApplyEffect(Car* pCar)=0;

protected:

	int BlockX;
	int BlockY;
	float y;
	float value;
	StatsTab* pStatsTab;
	float xPos;
	float d;
	float fPerspective;
	float fRoadWidth;
	float fMiddlePoint;
	int LeftEdge;
	int RightEdge;
	int Collision;

};






