#include "Block.h"
#include "Manager.h"
#include "Car.h"
#include "Track.h"
#include "StatsTab.h"

Block::Block()
{
	if (rand() % 2 == 0)	d = 1;
	else d = -1;

	xPos = 0;
	y = 0;
	BlockX = 0;
	BlockY = 0;
	LeftEdge = 0;
	RightEdge = 0;
	Collision = 0;
	fPerspective = 0;
	fRoadWidth = 0;
	fMiddlePoint = 80;
}

Block::~Block()
{
}

void Block::CollisionCheck(Car* pCar,int nCarPos) {

	if (abs(nCarPos - BlockX) < 10 && BlockY > 79 && BlockY < 90){

		this->ApplyEffect(pCar);

		Collision = 1;
	}

}