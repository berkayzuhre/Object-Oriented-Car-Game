#ifndef CAR_H
#define CAR_H

#include "stdafx.h"


class Manager;
class Track;

class StatsTab;

class Scenery;

class Block;



class Car
{

private:
	float fDistance;
	float fCarPos;
	float fPlayerCurvature;
	float fSpeed;
	int nCarDirection;
	int nCarPos;
	Track* pTrack;

	float duration;
	int BadCollision;

	int StopCollision;


public:
	Car(Track* pTrack2);

	~Car();



	void ChangeSpeed(int CheckInput,int CheckUp,float fTrackCurvature,float fElapsedTime);

	void DrawCar( Manager* p3,StatsTab* pStatsTab,float fElaspedTime,float fTrackCurvature, int a);

	void CheckCollisionWithBlock(Block* pBlock);

	void StartCurvatureCompute(float fElapsedTime);

	void DrawAll(Manager* pManager, Scenery* pScenery,float fElapsedTime,int ScreenHeight,int ScreenWidth);

	void StartLapCompute(StatsTab* pStatsTab, float fElapsedTime);

	void StartPositionCompute(float fElapsedTime);

	void StartBlockCompute(float fElapsedTime, int ScreenHeight, int ScreenWidth);

	void ChangeBadCollision();

	void ChangeStopCollision();
		
};

#endif