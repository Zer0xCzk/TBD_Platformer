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

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

//=============================================================================
int main(int argc, char* argv[])
{
	if (!InitSDL())
	{
		return 1;
	}

	if (!CreateWindow("Cyper", WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		return 1;
	}

	StartLoop(Update, RenderFrame);

	return 0;
}

Object player = { 200, 300, 50, 50, 100, 0};
Object terrain[20] = {200, 300, 50, 50, 100, 0};
Object terrain1 = { 500, 100, 600, 100, 100, 0 };
Object terrain2 = { 100, 300, 300, 300, 100, 0 };
int desy = 400;

//=============================================================================

void PosUp(float dt)
{
	player.box.y += (int)(player.vely * dt + 0.5f);
	if (IsKeyDown(SDL_SCANCODE_A))
	{
		player.box.x -= (int)(player.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_D))
	{
		player.box.x += (int)(player.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_W))
	{
		player.vely = -600;
	}
	player.vely += 15;
	return;
}

void ColUp(float dt)
{
	//SDL_Point left_bottom = { ebullet[i].box.x, ebullet[i].box.y + ebullet[i].box.h };
	SDL_Point left_bottom = { player.box.x, player.box.y + player.box.h };
	SDL_Point right_bottom = { player.box.x + player.box.w, player.box.y + player.box.h };
	if (SDL_PointInRect(&right_bottom, &terrain1.box) || SDL_PointInRect(&left_bottom, &terrain1.box))
	{
		player.box.y = terrain1.box.y - 1 - player.box.h;
		player.vely = 0;
	}
	if (SDL_PointInRect(&right_bottom, &terrain2.box) || SDL_PointInRect(&left_bottom, &terrain2.box))
	{
		player.box.y = terrain2.box.y - 1 - player.box.h;
		player.vely = 0;
	}
	return;
}

void Update(float dt)
{
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
	SDL_RenderFillRect(gRenderer, &terrain1.box);
	SDL_RenderFillRect(gRenderer, &terrain2.box);
}
