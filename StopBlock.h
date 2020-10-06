#pragma once


#include "Block.h"

class Car;

class Manager;



class StopBlock	: public Block
{
public:
	StopBlock();
	~StopBlock();

	void DrawBlock(Manager* pManager, int ScreenHeight);

	void ApplyEffect(Car* pCar);

	void Move(float fCurvature, float fSpeed, float fElapsedTime, int ScreenHeight, int ScreenWidht);

	bool DeleteCheck();

private:

	float SPos;

};

