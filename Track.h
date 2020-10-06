
#ifndef TRACK_H
#define TRACK_H

#include "stdafx.h"

#include <vector>
using namespace std;


class TrackSegment;
class Car;
class Manager;
class Block;
class StatsTab;
class Scenery;

class Track
{
public:

	Track(StatsTab* pStatsTab2);

	~Track();


	void DrawTrack(Car* pCar,Manager* pManager,Scenery* pScenery,float fElapsedTime,float fDistance,int ScreenHeight,int ScreenWidth);

	void AccumulateAllCurvature(float fSpeed,float fElapsedTime);

	void StartSpeedCompute(Car* pCar,int CheckInput,int CheckUp, float fElapsedTime);

	void FindPositionOnTrack(float fDistance, float fOffset);

	void BlockCompute2(float fSpeed, float fElapsedTime, int ScreenHeight, int ScreenWidth);

	void DeleteBlock();

	void CreateBlock();

	void StartCollisionCheck(Car* pCar);

private:



	int nTrackSection;

	TrackSegment* m[4];

	Block* b[10];

	int ActiveBlockNum;

	float fTrackCurvature;

	float fCurvature;

	float fTrackCurveDiff;

	StatsTab* pStatsTab;




};

#endif