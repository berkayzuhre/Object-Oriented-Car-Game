#pragma once


#include "MovingBlock.h"

class StatsTab;
class Manager;




class GoodBlock : public MovingBlock {

	

public:

	GoodBlock(StatsTab* pStatsTab2);

	~GoodBlock();

	void DrawBlock(Manager* pManager, int ScreenHeight);

	void ApplyEffect(Car* pCar);


	

	


};