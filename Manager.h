
#ifndef MANAGER_H
#define MANAGER_H

#include "stdafx.h"
#include "olcConsoleGameEngine.h"

class Mountain;
class Sky;
class StatsTab;
class Car;
class Track;
class TrackSegment;
class Rabbit;
class Scenery;


class Manager	:	public olcConsoleGameEngine
{
public:
	Manager();

	~Manager();

	int CheckUp();

	int CheckInput();

	virtual bool OnUserUpdate(float fElapsedTime);

	virtual bool OnUserCreate();

	void Stop();


private:
	Car* pCar;

	Track* pTrack;

	StatsTab* pStatsTab;

	Scenery* pScenery;

	



};



#endif

