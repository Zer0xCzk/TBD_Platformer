#include "engine.h"
#include "sprite.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "object.h"

void Update(float dt);
void RenderFrame(float dt);

#define WW 1200
#define WH 900

//=============================================================================

int main(int argc, char* argv[])
{
	if (!InitSDL())
	{
		return 1;
	}

	if (!CreateWindow("Cyper", WW, WH))
	{
		return 1;
	}

	StartLoop(Update, RenderFrame);

	return 0;
}

bool jump;
const int ammount = 10;
Object player = { 0, 0, 50, 50, 200, 0};
Object pastplayer = player;
Object terrain[ammount] = {0, 0, 0, 0, 0, 0};

//=============================================================================

void TerGen()
{
	int spacing = 150;
	int xoffset = 75;
	int yoffset = 75;
	for (int i = 0; i < ammount; i++)
	{
		if (i % 2 == 0)
		{
			terrain[i].box.w = 450;
			terrain[i].box.h = 200;
			terrain[i].box.x = xoffset;
			terrain[i].box.y = yoffset + (i * spacing);
		}
		else
		{
			terrain[i].box.w = 450;
			terrain[i].box.h = 100;
			terrain[i].box.x = WW - xoffset - terrain[i].box.w;
			terrain[i].box.y = yoffset + (i * spacing);
		}
	}
}

void PosUp(float dt)
{
	if (IsKeyDown(SDL_SCANCODE_A))
	{
		player.box.x -= (int)(player.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_W) && jump)
	{
		player.vely = -700;
		jump = false;
	}
	if (IsKeyDown(SDL_SCANCODE_D))
	{
		player.box.x += (int)(player.speed * dt + 0.5f);
	}
	player.vely += 15;
	player.box.y += (int)(player.vely * dt + 0.5f);
}

void ColUp(float dt)
{
	SDL_Point left_top = { player.box.x, player.box.y};
	SDL_Point right_top = { player.box.x + player.box.w, player.box.y };
	SDL_Point left_bottom = { player.box.x, player.box.y + player.box.h };
	SDL_Point right_bottom = { player.box.x + player.box.w, player.box.y + player.box.h };
	for (int i = 0; i < ammount; i++)
	{
		//Keeps the player above a rectangle
		if ((SDL_PointInRect(&right_bottom, &terrain[i].box) || SDL_PointInRect(&left_bottom, &terrain[i].box)) && pastplayer.box.y + pastplayer.box.h <= terrain[i].box.y)
		{
			player.box.y = terrain[i].box.y  - player.box.h;
			player.vely = 0;
			jump = true;
		}
		//Keeps the player below a rectangle
		else if ((SDL_PointInRect(&right_top, &terrain[i].box) || SDL_PointInRect(&left_top, &terrain[i].box)) && pastplayer.box.y >= terrain[i].box.y + terrain[i].box.h)
		{
			player.box.y = terrain[i].box.y + terrain[i].box.h;
			player.vely = 0;
		}
		//Keeps the player to the left of a rectangle
		else if (SDL_PointInRect(&right_bottom, &terrain[i].box) || SDL_PointInRect(&right_top, &terrain[i].box))
		{
			player.box.x = terrain[i].box.x - player.box.w;
			jump = true;
		}
		//Keeps the player to the right of a rectangle
		else if (SDL_PointInRect(&left_bottom, &terrain[i].box) || SDL_PointInRect(&left_top, &terrain[i].box))
		{
			player.box.x = terrain[i].box.x + terrain[i].box.w;
			jump = true;
		}
	}
	pastplayer = player;
}

void Update(float dt)
{
	TerGen();
	PosUp(dt);
	ColUp(dt);
	if (IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		ExitGame();
	}
}

void RenderFrame(float interpolation)
{
	
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);

	SDL_SetRenderDrawColor(gRenderer, 160, 0, 160, 255);
	SDL_RenderFillRect(gRenderer, &player.box);
	SDL_SetRenderDrawColor(gRenderer, 120, 120, 120, 255);
	for (int i = 0; i < ammount; i++)
	{
		SDL_RenderFillRect(gRenderer, &terrain[i].box);
	}
}
