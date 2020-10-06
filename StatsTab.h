#ifndef STATSTAB_H
#define STATSTAB_H

#include "stdafx.h"



#include <list>
using namespace std;

class Manager;
class TrackSegment;
class Track;
class Car;



class StatsTab
{
public:
	StatsTab();

	~StatsTab();

	float LapTimingAndCounting(float fDistance, float fElapsedTime);

	void DrawCarStats(Manager* pManager,float fSpeed, float fPlayerCurvature, float fDistance);

	void DrawTrackandTimingStats(Manager* pManager, float fCurvature, float fTrackCurvature, int ActiveBlockNum);

	void ChangePoints(float a);

private:
	list<float> listLapTimes;
	float CurrentLapTime;
	float fTrackDistance;

	float points;
};

#endif