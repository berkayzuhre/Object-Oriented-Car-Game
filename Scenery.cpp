#include "Scenery.h"
#include "Manager.h"
#include "Track.h"
#include <cmath>

Scenery::Scenery()
{
}

Scenery::~Scenery()
{
}

void Scenery::DrawScenery(Manager* p2,float fTrackCurvature, int SWidth, int SHeight) {


	for (int y = 0; y < SHeight / 2; y++)
		for (int x = 0; x <SWidth; x++)
			p2->Draw(x, y, y< SHeight / 4 ? PIXEL_HALF : PIXEL_SOLID, FG_DARK_BLUE);


	for (int x = 0; x < SWidth; x++)
	{
		int nHillHeight = (int)(fabs(sinf(x * 0.01f + fTrackCurvature)*16.0f));
		for (int y = (SHeight / 2) - nHillHeight; y < SHeight / 2; y++)
			p2->Draw(x, y, PIXEL_SOLID, FG_DARK_YELLOW);
	}
}

