#pragma once


#include "Block.h"


class MovingBlock:public Block
{
public:
	MovingBlock();
	~MovingBlock();

	void Move(float fCurvature, float fSpeed, float fElapsedTime, int ScreenHeight, int ScreenWidht);

	bool DeleteCheck();
	


private:

};

