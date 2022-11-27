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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
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

bool Game::IsColliding(int x1, int y1, int x2, int y2, int size1, int size2)
{
	int topx1 = x1;
	int botx1 = x1 + size1;
	int topy1 = y1;
	int boty1 = y1 + size1;
	int topx2 = x2;
	int botx2 = x2 + size2;
	int topy2 = y2;
	int boty2 = y2 + size2;

	if (botx1<topx2 || topx1>botx2 || boty1<topy2 || topy1>boty2) {
		return false;
	}
	else {

		return true;
	}
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {

		gyaradosX = gyaradosX + gyaradosMoveStep;
		gyaradosFaceRight = true;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {

		gyaradosX = gyaradosX - gyaradosMoveStep;
		gyaradosFaceRight = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP)) {

		gyaradosY = gyaradosY - gyaradosMoveStep;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {

		gyaradosY = gyaradosY + gyaradosMoveStep;
	}

	gyaradosX = ClampScreenX(gyaradosX, gyaradosSize);
	gyaradosY = ClampScreenY(gyaradosY, gyaradosSize);
	if (!karp0IsEaten){ 
		karp0IsEaten = Game::IsColliding(gyaradosX, gyaradosY, magiKarp0X, magiKarp0Y, gyaradosSize, magiKarpSize); 
	}
	if (!karp1IsEaten) {
		karp1IsEaten = Game::IsColliding(gyaradosX, gyaradosY, magiKarp1X, magiKarp1Y, gyaradosSize, magiKarpSize);
	}
	if (!karp2IsEaten) {
		karp2IsEaten = Game::IsColliding(gyaradosX, gyaradosY, magiKarp2X, magiKarp2Y, gyaradosSize, magiKarpSize);
	}
	}
void Game::ComposeFrame()
{

	if (!karp0IsEaten) {
		Game::DrawMagiKarp(magiKarp0X, magiKarp0Y);
	}
	if (!karp1IsEaten) {
	Game::DrawMagiKarpFlipped(magiKarp1X, magiKarp1Y);
	}
	if (!karp2IsEaten) {
		Game::DrawMagiKarpFlipped(magiKarp2X, magiKarp2Y);
	}

	if (!gyaradosFaceRight) {
		Game::DrawGyarados(gyaradosX, gyaradosY);
	}
	else {
		Game::DrawGyaradosFlipped(gyaradosX, gyaradosY);
	}





}

