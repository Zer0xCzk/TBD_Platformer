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

Object player = { 350, 100, 50, 50, 100, 0};
Object terrain[20] = {0, 0, 0, 0, 0, 0};
Object terrain1 = { 500, 100, 600, 100, 100, 0};
Object terrain2 = { 100, 300, 300, 300, 100, 0};

//=============================================================================

void TerGen()
{
	int spacing = 150;
	int xoffset = 350;
	int yoffset = 100;
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			terrain[i].box.w = 200;
			terrain[i].box.h = 100;
			terrain[i].box.x = xoffset;
			terrain[i].box.y = yoffset + (i * spacing);
		}
		else
		{
			terrain[i].box.w = 200;
			terrain[i].box.h = 100;
			terrain[i].box.x = WW - xoffset - terrain[i].box.w;
			terrain[i].box.y = yoffset + (i * spacing);
		}
	}
}

void PosUp(float dt)
{
	player.box.y += (int)(player.vely * dt + 0.5f);
	if (IsKeyDown(SDL_SCANCODE_A))
	{
		player.box.x -= (int)(player.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_W))
	{
		player.vely = -600;
	}
	if (IsKeyDown(SDL_SCANCODE_D))
	{
		player.box.x += (int)(player.speed * dt + 0.5f);
	}
	player.vely += 15;
	return;
}

void ColUp(float dt)
{
	SDL_Point left_top = { player.box.x, player.box.y};
	SDL_Point right_top = { player.box.x + player.box.w, player.box.y };
	SDL_Point left_bottom = { player.box.x, player.box.y + player.box.h };
	SDL_Point right_bottom = { player.box.x + player.box.w, player.box.y + player.box.h };
	for (int i = 0; i < 10; i++)
	{
		//Keeps the player to the left of a rectangle
		if ((SDL_PointInRect(&right_bottom, &terrain[i].box) && player.box.y < terrain[i].box.y + terrain[i].box.h && player.box.y > terrain[i].box.y) || (SDL_PointInRect(&right_top, &terrain[i].box) && player.box.y > terrain[i].box.y && player.box.y < terrain[i].box.y + terrain[i].box.h))
		{
		player.box.x = terrain[i].box.x - 1 - player.box.w;
		player.speed = 0;
		}
		//Keeps the player above a rectangle
		else if (SDL_PointInRect(&right_bottom, &terrain[i].box) || SDL_PointInRect(&left_bottom, &terrain[i].box))
		{
			player.box.y = terrain[i].box.y - 1 - player.box.h;
			player.vely = 0;
		}
		//Keeps the player below a rectangle
		else if (SDL_PointInRect(&right_top, &terrain[i].box) || SDL_PointInRect(&left_top, &terrain[i].box))
		{
			player.box.y = terrain[i].box.y + terrain[i].box.h + 1;
			player.vely = 0;
		}
		player.speed = 100;
		
		
	}
	return;
}

void Update(float dt)
{
	TerGen();
	PosUp(dt);
	ColUp(dt);
	if (IsKeyDown(SDL_SCANCODE_ESCAPE))
		ExitGame();
}

void RenderFrame(float interpolation)
{
	
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 160, 0, 160, 255);
	SDL_RenderFillRect(gRenderer, &player.box);
	SDL_SetRenderDrawColor(gRenderer, 120, 120, 120, 255);
	for (int i = 0; i < 10; i++)
	{
		SDL_RenderFillRect(gRenderer, &terrain[i].box);
	}
}
