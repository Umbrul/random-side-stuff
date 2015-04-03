#ifndef GRID_H
#define GRID_H

#include "Constants.h"
#include "Common.h"
#include <GLFW\glfw3.h>

namespace Display
{



	class Grid
	
	{
	private:
		float height;
		float width;
		int xGap;
		int yGap;

		// offset = center offset (grid in center) + misc offsets
		float xOffsetCenter = 0;
		float yOffsetCenter = 0;
		float xOffsetMisc = 0;
		float yOffsetMisc = 0;

		// Open Squares in each direction
		int top;
		int bottom;
		int right;
		int left;

		short thickness = 1;

		void glVertex2Offset(int x, int y);
		void refresh();//Recalculates key values when key settings (zoom, etc) are modified.
		void drawPoints();
	public:
		Grid();
		~Grid() {};

		void render();
		void increaseThickness();
		void decreaseThickness();
		void modifyXOffset(int x);
		void modifyYOffset(int x);
		
		void screenToGrid(double &x, double &y);

		TileInfo getTileAtPoint(double x, double y);

		void selectPoint(double x, double y); //for testing
		void selectTileAtPoint(double x, double y); 
		void selectTile(int x, int y);
		bool isTileVisible(int x, int y);
		bool isVisible(int x, int y);
	};

}

#endif