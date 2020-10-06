
#include "TrackSegment.h"


#include "Car.h"
#include "Track.h"

TrackSegment::TrackSegment(float x, float y) : TargetCurvature(x), SegmentLenght(y)
{


}


TrackSegment::~TrackSegment()
{
}




void TrackSegment::Lenght(float& a) {
	
		a= SegmentLenght;
	
}

void TrackSegment::Curve(int& a) {

	a= TargetCurvature;
}

