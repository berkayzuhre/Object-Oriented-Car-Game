#include "MovingBlock.h"
#include <math.h>


MovingBlock::MovingBlock()
{
}

MovingBlock::~MovingBlock()
{
}

void MovingBlock::Move(float fCurvature, float fSpeed, float fElapsedTime, int ScreenHeight, int ScreenWidth) {

	// Perspective is used to modify the width of the track row segments
	fPerspective = y / (ScreenHeight / 2.0f);
	fRoadWidth = 0.1f + fPerspective * 0.8f; // Min 10% Max 90%
	fRoadWidth *= 0.5f;	// Halve it as track is symmetrical around center of track, but offset...

						// ...depending on where the middle point is, which is defined by the current
						// track curvature.
	fMiddlePoint = 0.5f + fCurvature * powf((1.0f - fPerspective), 3);

	BlockY = ScreenHeight / 2 + y;

	RightEdge = (fMiddlePoint + fRoadWidth) * ScreenWidth + 5;
	LeftEdge = (fMiddlePoint - fRoadWidth) * ScreenWidth - 10;



	BlockX = (fMiddlePoint + d*fRoadWidth + xPos) * ScreenWidth;

	xPos -= d*fPerspective*0.2*fElapsedTime;

	y += (fSpeed * 8 * fElapsedTime);






}

bool MovingBlock::DeleteCheck() {

	if (BlockY > 110 || BlockX > RightEdge || BlockX < LeftEdge || Collision) {
		Collision = 0;
		return true;
	}
	return false;

}
