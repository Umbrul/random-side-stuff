#include "Grid.h"


namespace Display
{


	void Grid::draw()
	{

		float xHalfWidth = width / 2.0;
		float yHalfHeight = height / 2.0;


		glPointSize(10);

		/*glBegin(GL_POINTS);


		for (int i = bottom; i <= top; i++)
		{
			for (int j = left; j <= right; j++)
			{
				glVertex2f((i*xGap) + xOffset, (j*yGap) + yOffset);
			}
		}
		glEnd();*/

		glPointSize(1);
		glBegin(GL_LINES);
		for (int i = bottom; i <= top; i++)
		{

			glVertex2UI(xHalfWidth, (i*yGap) +  (yOffsetMisc+yOffsetCenter)%yGap);
			glVertex2UI(-xHalfWidth, (i*yGap) + (yOffsetMisc+yOffsetCenter)%yGap);
		}
		for (int i = left; i <= right; i++)
		{
			glVertex2UI((i*xGap ) + (xOffsetMisc+xOffsetCenter)%xGap, yHalfHeight);
			glVertex2UI((i*xGap)  + (xOffsetMisc+xOffsetCenter)%xGap, -yHalfHeight);
		}
		glEnd();
	}


	void Grid::selectTile(int x, int y)
	{
		//Map::map[0][y + (int)Constants::MAP_LENGTH / 2][x + (int)Constants::MAP_WIDTH / 2];
		glPointSize(20);
		glColor3f(0, 1, 0);
		glBegin(GL_POINT);
		glVertex2Offset(x, y);
		glEnd();
	}

	void Grid::selectTileAtPoint(float x, float y)
	{

		int divX = (x + xOffsetCenter) / xGap;
		int tileX;

		if (x+xOffsetCenter>=0)
			tileX = divX;
		else
			tileX = divX - 1;

		int divY = (y + yOffsetCenter) / yGap;
		int tileY;

		if (y + yOffsetCenter>=0)
			tileY = divY;
		else
			tileY = divY - 1;

		//Map::map[0][y + (int)Constants::MAP_LENGTH / 2][x + (int)Constants::MAP_WIDTH / 2];
			glPointSize(20);
			glColor3f(0, 1, 0);
			glBegin(GL_POINTS);
				glVertex2UI(tileX*xGap, tileY*yGap);
			glEnd();

		glColor3f(1, 1, 1);
	}

	void Grid::selectPoint(float x, float y)
	{
		//Map::map[0][y + (int)Constants::MAP_LENGTH / 2][x + (int)Constants::MAP_WIDTH / 2];
		glPointSize(20);
		glColor3f(0, 1, 0);
		glBegin(GL_POINTS);
		glVertex2UI(x, y);
		glEnd();

		glColor3f(1, 1, 1);
	}

	TileInfo Grid::getTileAtPoint(float x, float y)
	{

		int divX = (x + xOffsetCenter) / xGap;
		int tileX;

		if (divX >= 0)
			tileX = divX;
		else
			tileX = divX - 1;

		int divY = (y + yOffsetCenter) / yGap;
		int tileY;

		if (divY >= 0)
			tileY = divY;
		else
			tileY = divY - 1;
		return Map::map[0][tileY + (int)Constants::MAP_LENGTH / 2][tileX + (int)Constants::MAP_WIDTH / 2];
	}

	bool Grid::isTileVisible(int x, int y)
	{
		
		if ((center.x + left <= x || center.x + right >= x) && (center.y + bottom <= y || center.y + top >= y))
			return true;
		return false;

	}

	bool Grid::isVisible(int x, int y)
	{
		if ((center.x - width / 2 <= x && center.x + width / 2 >= x) && (center.y - height / 2 <= y && center.y + height / 2 >= y))
			return true;
		return false;

	}

	void Grid::decreaseThickness()
	{
		if (thickness > 1)
			thickness -= 5;
		else
			thickness = 1;
	}

	void Grid::increaseThickness()
	{
		if (thickness < 26)
			thickness += 5;
		else
			thickness = 26;
	}

	void Grid::modifyXOffset(int n)
	{
		xOffsetMisc += n;
	}

	void Grid::modifyYOffset(int n)
	{
		yOffsetMisc += n;
	}

	

	void Grid::refresh()
	{
	/*	screenToGridWidthRatio = Constants::SCREEN_WIDTH / (double)Constants::GRID_WIDTH;
		screenToGridHeightRatio = Constants::SCREEN_HEIGHT / (double)Constants::GRID_HEIGHT;
*/
		UIPanel::refresh();

		xGap = width / zoom;
		yGap = height / zoom;

		xOffsetCenter = (xGap) / 2;
		yOffsetCenter = (yGap) / 2;

		top = (height / 2 - (yOffsetMisc%yGap)) / yGap;
		bottom = (height / 2 + (yOffsetMisc % yGap)) / yGap *-1;
		right = ((width - xOffsetMisc )/ 2) / xGap;
		left = ((width - xOffsetMisc) / 2) / xGap*-1;
	}

	void Grid::glVertex2Offset(float x, float y)
	{
		glVertex2f(x + xOffsetCenter + xOffsetMisc, y + yOffsetMisc + yOffsetCenter);
	}

	

}