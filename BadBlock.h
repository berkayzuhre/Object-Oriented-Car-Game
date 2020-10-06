#pragma once



#include "MovingBlock.h"
class Car;

class Manager;
class StatsTab;


class BadBlock : public MovingBlock {


public:
	BadBlock(StatsTab* pStatsTab2);

	~BadBlock();

	void DrawBlock(Manager* p1, int ScreenHeight);
	
	void ApplyEffect(Car* pCar);



};