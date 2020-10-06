

#include "Car.h"

#include "Track.h"

#include "Manager.h"

#include "TrackSegment.h"

#include "StatsTab.h"

#include "Scenery.h"

#include "Block.h"


Car::Car(Track* pTrack2):pTrack(pTrack2)
{
	fDistance=0;
	fCarPos=0;
	fPlayerCurvature=0;
	fSpeed=0;
	nCarDirection=0;
	nCarPos=0;
	duration = 0;
	BadCollision = 0;
}

Car::~Car()
{
}



void Car::CheckCollisionWithBlock(Block* pBlock) {

	pBlock->CollisionCheck(this,nCarPos);
}

void Car::ChangeSpeed(int CheckInput,int CheckUp,float fTrackCurvature,float fElapsedTime) {

	

	nCarDirection = CheckInput;
	
	if (!StopCollision) {
		if (CheckUp)

			fSpeed += 2.0f * fElapsedTime;
		else
			fSpeed -= 1.0f * fElapsedTime;


		if (fabs(fPlayerCurvature - fTrackCurvature) >= 0.8f)
			fSpeed -= 5.0f * fElapsedTime;

		fPlayerCurvature += 0.7f * fElapsedTime * (1.0f - fSpeed / 2.0f)*nCarDirection;

		if (fSpeed < 0.0f)	fSpeed = 0.0f;
		if (fSpeed > 1.0f)	fSpeed = 1.0f;
	}
	else {
		fPlayerCurvature += 0.7f * fElapsedTime * (1.0f -1 / 2.0f)*nCarDirection;
		fSpeed = 0;
		StopCollision = 0;
	}

}

void Car::DrawCar(Manager* p3,StatsTab* pStatsTab,float fElapsedTime,float fTrackCurvature,int ScreenWidth) {
	


	fCarPos = fPlayerCurvature - fTrackCurvature;

	nCarPos = ScreenWidth / 2 + ((int)(ScreenWidth * fCarPos) / 2.0) - 7; 
	if (!BadCollision) {
		switch (nCarDirection)
		{
		case 0:
			p3->DrawStringAlpha(nCarPos, 80, L"   ||####||   ");
			p3->DrawStringAlpha(nCarPos, 81, L"      ##      ");
			p3->DrawStringAlpha(nCarPos, 82, L"     ####     ");
			p3->DrawStringAlpha(nCarPos, 83, L"     ####     ");
			p3->DrawStringAlpha(nCarPos, 84, L"|||  ####  |||");
			p3->DrawStringAlpha(nCarPos, 85, L"|||########|||");
			p3->DrawStringAlpha(nCarPos, 86, L"|||  ####  |||");
			break;

		case +1:
			p3->DrawStringAlpha(nCarPos, 80, L"      //####//");
			p3->DrawStringAlpha(nCarPos, 81, L"         ##   ");
			p3->DrawStringAlpha(nCarPos, 82, L"       ####   ");
			p3->DrawStringAlpha(nCarPos, 83, L"      ####    ");
			p3->DrawStringAlpha(nCarPos, 84, L"///  ####//// ");
			p3->DrawStringAlpha(nCarPos, 85, L"//#######///O ");
			p3->DrawStringAlpha(nCarPos, 86, L"/// #### //// ");
			break;

		case -1:
			p3->DrawStringAlpha(nCarPos, 80, L"\\\\####\\\\      ");
			p3->DrawStringAlpha(nCarPos, 81, L"   ##         ");
			p3->DrawStringAlpha(nCarPos, 82, L"   ####       ");
			p3->DrawStringAlpha(nCarPos, 83, L"    ####      ");
			p3->DrawStringAlpha(nCarPos, 84, L" \\\\\\\\####  \\\\\\");
			p3->DrawStringAlpha(nCarPos, 85, L" O\\\\\\#######\\\\");
			p3->DrawStringAlpha(nCarPos, 86, L" \\\\\\\\ #### \\\\\\");
			break;
		}
		
	}
	else {
		duration += fElapsedTime;
		if (duration > 2) {
			BadCollision = 0;
			duration = 0;
		}

	}
	pStatsTab->DrawCarStats(p3,fSpeed, fPlayerCurvature, fDistance);
}




void Car::DrawAll(Manager* pManager, Scenery* pScenery,float fElapsedTime,int ScreenHeight,int ScreenWidth){

	pTrack->DrawTrack(this, pManager, pScenery, fElapsedTime,fDistance,ScreenHeight, ScreenWidth);

}

void Car::StartCurvatureCompute(float fElapsedTime) {

	pTrack->AccumulateAllCurvature(fSpeed,fElapsedTime);

}

void Car::StartLapCompute(StatsTab* pStatsTab, float fElapsedTime) {


	fDistance += pStatsTab->LapTimingAndCounting(fDistance, fElapsedTime);
}

void Car::StartPositionCompute(float fElapsedTime) {

	fDistance += (70.0f * fSpeed) * fElapsedTime;

	float fOffset = 0;

	pTrack->FindPositionOnTrack(fDistance, fOffset);
	

}


void Car::StartBlockCompute(float fElapsedTime,int ScreenHeight,int ScreenWidth) {

	pTrack->BlockCompute2(fSpeed,fElapsedTime, ScreenHeight, ScreenWidth);

}

void Car::ChangeBadCollision() {
	BadCollision++;
}

void Car::ChangeStopCollision() {

	StopCollision++;

}