
#ifndef TRACKSEG_H
#define TRACKSEG_H


#include "stdafx.h"



class Car;
class Track;


class TrackSegment
{
public:
	TrackSegment(float x, float y);

	~TrackSegment();

	void Lenght(float& a);

	void Curve(int& a);



private:

	int TargetCurvature;

	float SegmentLenght;
	


};


#endif