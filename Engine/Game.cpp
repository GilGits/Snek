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
	gfx( wnd ),
	rng(rd()),
	yay({ L"coin.wav" }, true)
{
	try
	{
		title = Sound(L"title.wav");
	}
	catch (const SoundSystem::FileException& e)
	{
		(void)e; //gets rid of unreferenced local variable warning
		title = Sound();
	}

	try
	{
		gameover = Sound(L"gameoy.wav");
	}
	catch (const SoundSystem::FileException& e)
	{
		(void)e; //gets rid of unreferenced local variable warning
		gameover = Sound();
	}

	title.Play();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (isStarted && !isGameOver)
	{
		while (!wnd.kbd.KeyIsEmpty()) //con 'if' sembra funzionare allo stesso identico modo
		{
			const Keyboard::Event e = wnd.kbd.ReadKey();

			if (e.IsRelease() && (e.GetCode() == VK_SPACE || e.GetCode() == 'P'))
			{
				isPaused = !isPaused;
			}
		}

		if (!isPaused) 
		{
			const float dt = ft.Mark();
			snake.getInput(wnd.kbd);

			if (moveRateCounter == 0.0f)
			{
				if (snake.hasEaten(food))
				{
					snake.draw(gfx); //altrimenti se dopo aver mangiato fuckdappa, non si vede che ha mangiato (quindi neanche che fuckdappa)
					yay.Play(rng);

					do
					{
						food.setPosition();
					} 
					while (snake.isOverlapping(food.getLocation()));
				}
				//else snake.move(); // GOD MODE
				else if (!snake.move())
				{
					isGameOver = true;
					gameover.Play();
				}
			}

			moveRateCounter += dt*60.0f;
			if (moveRateCounter > Snake::moveRate)
				moveRateCounter = 0.0f;
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		isStarted = true;
		
		if (isGameOver)
		{
			isGameOver = false;
			snake = Snake();
			food.setPosition();
		}
	}
}

void Game::ComposeFrame()
{
	if (isStarted)
	{
		snake.draw(gfx);

		food.draw(gfx);

		if (isGameOver)
		{
			SpriteCodex::DrawGameOver(Graphics::ScreenWidth / 2 - Graphics::ScreenWidth / 18, Graphics::ScreenHeight / 2 - Graphics::ScreenHeight * 2 / 15, gfx); // 1/18 == 50/900 and 2/15 == 80/600
		}
	}
	else
	{
		SpriteCodex::DrawTitle(Graphics::ScreenWidth / 2 - Graphics::ScreenWidth / 10, Graphics::ScreenHeight / 2 - Graphics::ScreenHeight * 19 / 120, gfx); // 1/10 == 90/900 and 19/120 == 95/600
	}
}
