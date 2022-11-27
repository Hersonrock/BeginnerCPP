/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

int Game::ClampScreenX(int x, int size)
{
	if (x <= 0) {
		x = 0;
	}
	else if (x > gfx.ScreenWidth - 1 - size) {
		x = gfx.ScreenWidth - 1 - size;
	}
	return x;
}

int Game::ClampScreenY(int y, int size)
{
	if (y < 0) {
		y = 0;
	}
	else if (y > gfx.ScreenHeight - 1 - size) {
		y = gfx.ScreenHeight - 1 - size;
	}

	return y;
}


void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {

		gyaradosX= gyaradosX+ gyaradosMoveStep;
		gyaradosFaceRight = true;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {

		gyaradosX= gyaradosX- gyaradosMoveStep;
		gyaradosFaceRight = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP)) {

		gyaradosY= gyaradosY- gyaradosMoveStep;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {

		gyaradosY = gyaradosY+ gyaradosMoveStep;
	}

	gyaradosX = ClampScreenX(gyaradosX, gyaradosSize);
	gyaradosY = ClampScreenY(gyaradosY, gyaradosSize);

}

void Game::ComposeFrame()
{

	Game::DrawMagiKarp(magiKarp0X, magiKarp0Y);
	Game::DrawMagiKarpFlipped(magiKarp1X, magiKarp1Y);


	if (!gyaradosFaceRight) {
		Game::DrawGyarados(gyaradosX, gyaradosY);
	}
	else {
		Game::DrawGyaradosFlipped(gyaradosX, gyaradosY);
	}
	


	

}

