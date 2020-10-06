
#include "Manager.h"
#include "Car.h"
#include "StatsTab.h"
#include "Track.h"
#include "TrackSegment.h"
#include "Block.h"
#include "Scenery.h"



Manager::Manager()
{
	
}

Manager::~Manager()
{
}

int Manager::CheckUp() {

	if (m_keys[VK_UP].bHeld)

		return 1;
	else
		return 0;
}


int Manager::CheckInput() {

	if (m_keys[VK_LEFT].bHeld)
	{
		return -1;
	}

	else if (m_keys[VK_RIGHT].bHeld)
	{
		return 1;
	}


	else return 0;

}



bool Manager::OnUserCreate() {

	pStatsTab = new StatsTab();

	pTrack = new Track(pStatsTab);

	pCar = new Car(pTrack);


	pScenery = new Scenery();



	return true;
}


bool Manager::OnUserUpdate(float fElapsedTime) {

	pCar->StartCurvatureCompute(fElapsedTime);

	pTrack->StartSpeedCompute(pCar,CheckInput(),CheckUp(),fElapsedTime);

	pTrack->StartCollisionCheck(pCar);

	pCar->StartBlockCompute(fElapsedTime, ScreenHeight(), ScreenWidth());

	pCar->StartPositionCompute(fElapsedTime);

	pCar->StartLapCompute(pStatsTab, fElapsedTime);

	pCar->DrawAll(this, pScenery,fElapsedTime,ScreenHeight(),ScreenWidth());

	if (m_keys[VK_ESCAPE].bPressed) {
		this->Stop();
		m_bAtomActive = false;
	}


	return true;


}

void Manager::Stop() {

	delete pTrack;
	delete pStatsTab;
	delete pCar;
	delete pScenery;
	Manager::~Manager();
}

