
#include <iostream>
#include <string>

#include "StatsTab.h"

#include "Car.h"
#include "Track.h"
#include "TrackSegment.h"
#include "Manager.h"
#include <vector>
#include <iostream>




using namespace std;



StatsTab::StatsTab()
{
	listLapTimes = { 0,0,0,0,0 };

	CurrentLapTime = 0;

	fTrackDistance = 510;

	points = 0;

}

StatsTab::~StatsTab()
{
}

float StatsTab::LapTimingAndCounting(float fDistance, float fElapsedTime) {


	CurrentLapTime += fElapsedTime;

	if (fDistance >= fTrackDistance){

		listLapTimes.push_front(CurrentLapTime);

		listLapTimes.pop_back();

		CurrentLapTime = 0;

		return -fTrackDistance;

	}


	return 0.0;
}


void StatsTab::DrawCarStats(Manager* pManager,float fSpeed, float fPlayerCurvature, float fDistance) {

	pManager->DrawStringAlpha(0, 0, L"Distance: " + to_wstring(fDistance));
	pManager->DrawStringAlpha(0, 2, L"PlayerCurvature: " + to_wstring(fPlayerCurvature));
	pManager->DrawStringAlpha(0, 3, L"Speed    : " + to_wstring(fSpeed));
}

void StatsTab::DrawTrackandTimingStats(Manager* pManager,float fCurvature,float fTrackCurvature,int ActiveBlockNum ) {

	pManager->DrawStringAlpha(0, 1, L"Target Curvature:" + to_wstring(fCurvature));
	pManager->DrawStringAlpha(0, 4, L"TrackCurvature : " + to_wstring(fTrackCurvature));
	pManager->DrawStringAlpha(0, 5, L"BlockNum : " + to_wstring(ActiveBlockNum));

	pManager->DrawStringAlpha(20, 10, L"Points : " + to_wstring(points));

	auto disp_time = [](float t) // Little lambda to turn floating point seconds into minutes:seconds:millis string
	{
		int nMinutes = t / 60.0f;
		int nSeconds = t - (nMinutes * 60.0f);
		int nMilliSeconds = (t - (float)nSeconds) * 1000.0f;
		return to_wstring(nMinutes) + L"." + to_wstring(nSeconds) + L":" + to_wstring(nMilliSeconds);
	};



	pManager->DrawStringAlpha(10, 8, disp_time(CurrentLapTime));

	// Display last 5 lap times
	int j = 10;

	for (auto l : listLapTimes)
	{
		pManager->DrawStringAlpha(10, j, disp_time(l));
		j++;
	}
}

void StatsTab::ChangePoints(float a) {

	points += a;

}