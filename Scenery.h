#pragma once


#ifndef Scenery_H
#define Scenery_H

#include "stdafx.h"

class Track;
class Manager;

class Scenery
{
public:
	Scenery();
	~Scenery();

	void DrawScenery(Manager* p2,float fTrackCurvature, int SWidht, int SHeight);

private:

};

#endif