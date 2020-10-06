#include "StopBlock.h"
#include "Manager.h"
#include "Car.h"

StopBlock::StopBlock()
{
	SPos = rand()%150;

}

StopBlock::~StopBlock()
{
}

void StopBlock::DrawBlock(Manager* pManager, int ScreenHeight) {


	float fPerspective = y / (ScreenHeight / 2.0f);


	for (int i = 0; i < 16 * fPerspective*1.5; i++) {
		for (int j = 0; j < 8 * fPerspective*1.5; j++) {
			pManager->Draw(BlockX + i, BlockY - j, PIXEL_SOLID, FG_YELLOW);
		}
	}



}

void StopBlock::ApplyEffect(Car* pCar) {

	pCar->ChangeStopCollision();

}

void StopBlock::Move(float fCurvature, float fSpeed, float fElapsedTime, int ScreenHeight, int ScreenWidth) {

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



		BlockX = (fMiddlePoint - fRoadWidth) * ScreenWidth + SPos*fPerspective;

	y += (fSpeed * 8 * fElapsedTime);




}

bool StopBlock::DeleteCheck() {

	if (BlockY > 90) {
		Collision = 0;
		return true;
	}


	return false;
}