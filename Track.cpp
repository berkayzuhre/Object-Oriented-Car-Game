
#include "Track.h"
#include "Car.h"
#include "Manager.h"
#include "TrackSegment.h"
#include "Block.h"
#include "GoodBlock.h"
#include "BadBlock.h"
#include "StatsTab.h"
#include "Scenery.h"
#include "StopBlock.h"

Track::Track(StatsTab* pStatsTab2):pStatsTab(pStatsTab2)
{

	m[0] = new TrackSegment(0, 10);
	m[1] = new TrackSegment(1, 200);
	m[2] = new TrackSegment(0, 200);
	m[3] = new TrackSegment(-1, 100);

	for (int i = 0; i < 10; i++)	b[i] = NULL;

	nTrackSection=0;

	ActiveBlockNum = 0;

	fTrackCurvature = 0;

	fCurvature = 0;

	fTrackCurveDiff = 0;


}

Track::~Track()
{
	for (int i = 0; i < 4; i++) {
		delete m[i];
	}
	for (int i = 0; i < 10; i++) {
		if (b[i] != NULL) {
			delete b[i];
		}
	}

}


void Track::DrawTrack(Car* pCar,Manager* pManager,Scenery* pScenery,float fElapsedTime,float fDistance,int ScreenHeight,int ScreenWidth) {
	
	// Draw Track - Each row is split into grass, clip-board and track

	

	for (int y = 0; y < ScreenHeight/ 2; y++)
		for (int x = 0; x < ScreenWidth; x++)
		{
			// Perspective is used to modify the width of the track row segments
			float fPerspective = (float)y / (ScreenHeight / 2.0f);
			float fRoadWidth = 0.1f + fPerspective * 0.8f; // Min 10% Max 90%
			float fClipWidth = fRoadWidth * 0.15f;
			fRoadWidth *= 0.5f;	// Halve it as track is symmetrical around center of track, but offset...

								// ...depending on where the middle point is, which is defined by the current
								// track curvature.
			float fMiddlePoint = 0.5f + fCurvature * powf((1.0f - fPerspective), 3);

			// Work out segment boundaries
			int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * ScreenWidth;
			int nLeftClip = (fMiddlePoint - fRoadWidth) * ScreenWidth;
			int nRightClip = (fMiddlePoint + fRoadWidth) * ScreenWidth;
			int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * ScreenWidth;

			int nRow = ScreenHeight / 2 + y;

			// Using periodic oscillatory functions to give lines, where the phase is controlled
			// by the distance around the track. These take some fine tuning to give the right "feel"
			int nGrassColour = sinf(20.0f *  powf(1.0f - fPerspective, 3) + fDistance * 0.1f) > 0.0f ? FG_GREEN : FG_DARK_GREEN;
			int nClipColour = sinf(80.0f *  powf(1.0f - fPerspective, 2) + fDistance) > 0.0f ? FG_RED : FG_WHITE;

			// Start finish straight changes the road colour to inform the player lap is reset
			int nRoadColour = (nTrackSection) == 0 ? FG_WHITE : FG_GREY;




			// Draw the row segments
			if (x >= 0 && x < nLeftGrass)
				pManager->Draw(x, nRow, PIXEL_SOLID, nGrassColour);
			if (x >= nLeftGrass && x < nLeftClip)
				pManager->Draw(x, nRow, PIXEL_SOLID, nClipColour);
			if (x >= nLeftClip && x < nRightClip)
				pManager->Draw(x, nRow, PIXEL_SOLID, nRoadColour);
			if (x >= nRightClip && x < nRightGrass)
				pManager->Draw(x, nRow, PIXEL_SOLID, nClipColour);
			if (x >= nRightGrass && x < pManager->ScreenWidth())
				pManager->Draw(x, nRow, PIXEL_SOLID, nGrassColour);
		}

	for (int i = 0; i < 10; i++) {
		if (b[i] != NULL) {

			b[i]->DrawBlock(pManager,ScreenHeight);
			

		}

	
	}


	pScenery->DrawScenery(pManager, fTrackCurvature, ScreenWidth, ScreenHeight);

	pStatsTab->DrawTrackandTimingStats(pManager, fCurvature, fTrackCurvature, ActiveBlockNum);

	pCar->DrawCar(pManager, pStatsTab,fElapsedTime,fTrackCurvature, ScreenWidth);




}





void Track::AccumulateAllCurvature(float fSpeed,float fElapsedTime) {

	
	int a;
	m[nTrackSection]->Curve(a);

	fTrackCurveDiff = (a - fCurvature)*fElapsedTime*fSpeed;

	fCurvature += fTrackCurveDiff;

	fTrackCurvature += fCurvature* fElapsedTime * fSpeed;

}

void Track::StartSpeedCompute(Car* pCar,int CheckInput,int CheckUp, float fElapsedTime) {
	
	pCar->ChangeSpeed(CheckInput,CheckUp,fTrackCurvature,fElapsedTime);

}

void Track::FindPositionOnTrack(float fDistance, float fOffset) {

	nTrackSection = 0;

	while (nTrackSection < 4 && fOffset <= fDistance)
	{
		float a;
		m[nTrackSection]->Lenght(a);

		fOffset +=a;

		nTrackSection++;
	}

	nTrackSection--;

}

void Track::DeleteBlock() {

	for (int i = 0; i < 10; i++) {
		if(b[i]!=NULL)
		if (b[i]->DeleteCheck()) {
			delete b[i];
			b[i] = NULL;
			ActiveBlockNum--;
		}

	}
}

void Track::CreateBlock() {


	if (rand() % 50 == 0) {
		for (int i = 0; i < 10; i++) {
			if (b[i] == NULL) {
				int a = rand() % 5;
				if (a == 0||a==3||a==4)
					b[i] = new GoodBlock(pStatsTab);
				else if (a == 1)
					b[i] = new BadBlock(pStatsTab);
				else if(a==2)
					b[i] = new StopBlock();
				ActiveBlockNum++;
				break;
			}
		}
	}


}

void Track::BlockCompute2(float fSpeed,float fElapsedTime,int ScreenHeight,int ScreenWidth) {

	CreateBlock();

	DeleteBlock();

	for (int i = 0; i < 10; i++) {
		if (b[i] != NULL) {
			b[i]->Move(fCurvature, fSpeed, fElapsedTime, ScreenHeight, ScreenWidth);
		}
	}

}

void Track::StartCollisionCheck(Car* pCar) {

	for (int i = 0; i < 10; i++) {
		if (b[i] != NULL) {
			pCar->CheckCollisionWithBlock(b[i]);
		}
	}



}