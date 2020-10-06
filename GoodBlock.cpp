#include "GoodBlock.h"

#include "Manager.h"
#include "StatsTab.h"


GoodBlock::GoodBlock(StatsTab* pStatsTab2) {
	pStatsTab = pStatsTab2;
	value = 30.500;
}

GoodBlock::~GoodBlock() {



}

void GoodBlock::DrawBlock(Manager* pManager,int ScreenHeight) {

	float fPerspective = y / (ScreenHeight / 2.0f);


	for (int i = 0; i < 16 * fPerspective*1.5; i++) {
		for (int j = i; j < 8 * fPerspective*1.5; j++) {
			pManager->Draw(BlockX + i, BlockY - j, PIXEL_SOLID, FG_BLUE);
		}
	}



}

void GoodBlock::ApplyEffect(Car* pCar) {

	pStatsTab->ChangePoints(value);


}