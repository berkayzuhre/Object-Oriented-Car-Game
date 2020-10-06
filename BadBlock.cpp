#include "BadBlock.h"
#include "Manager.h"
#include "StatsTab.h"
#include "Car.h"

BadBlock::BadBlock(StatsTab* pStatsTab2)
{
	pStatsTab = pStatsTab2;
	value = -30.500;
}


BadBlock::~BadBlock() {



}

void BadBlock::DrawBlock(Manager* pManager,int ScreenHeight) {

	float fPerspective = y / (ScreenHeight / 2.0f);

	float a = 16;
	float b = 0;

	for (float j = 0; j < 8*fPerspective*1.5; j++) {

		for (float i = 0; i<16*fPerspective*1.5; i++) {

			if(i < a * fPerspective*1.5 && i >b*fPerspective*1.5)
			pManager->Draw(BlockX + i, BlockY - j, PIXEL_SOLID, FG_BLACK);
		}

		a--;
		b++;
	}


}

void BadBlock::ApplyEffect(Car* pCar) {

	pStatsTab->ChangePoints(value);

	pCar->ChangeBadCollision();

}