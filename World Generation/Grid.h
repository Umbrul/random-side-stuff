#ifndef GRID_H
#define GRID_H

#include "Constants.h"
#include "Common.h"
#include "UIPanel.h"
#include <GLFW\glfw3.h>

namespace Display
{



	class Grid : public UIPanel
	
	{
	private:
		int xGap;
		int yGap;

		// offset = center offset (grid in center) + misc offsets
		int xOffsetCenter = 0;
		int yOffsetCenter = 0;
		int xOffsetMisc = 0;
		int yOffsetMisc = 0;

		// Open Squares in each direction
		int top;
		int bottom;
		int right;
		int left;

		short thickness = 1;

		float screenToGridWidthRatio;
		float screenToGridHeightRatio;

		void glVertex2Offset(float x, float y); //Only applies offset
	
		void refresh();
		void draw();
	public:

		void increaseThickness();
		void decreaseThickness();
		void modifyXOffset(int x);
		void modifyYOffset(int x);
		

		TileInfo getTileAtPoint(float x, float y);

		void selectPoint(float x, float y); //for testing
		void selectTileAtPoint(float x, float y);
		void selectTile(int x, int y);
		bool isTileVisible(int x, int y);
		bool isVisible(int x, int y);
	};

}

#endif