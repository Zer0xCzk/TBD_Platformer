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

Object player = { 200, 200, 50, 50, 100, Player };

//=============================================================================

int PosUp(float dt)
{
	if (IsKeyDown(SDL_SCANCODE_A))
	{
		player.box.x -= (int)(player.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_D))
	{
		player.box.x += (int)(player.speed * dt + 0.5f);
	}
	return 0;
}

void Update(float dt)
{
	PosUp(dt);
	if (IsKeyDown(SDL_SCANCODE_ESCAPE))
		ExitGame();
}

void RenderFrame(float interpolation)
{
	
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 0, 200, 200, 255);
	SDL_RenderFillRect(gRenderer, &player.box);
}
