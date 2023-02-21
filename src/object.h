#include "sprite.h"

enum Type { Player };

struct Object
{
	SDL_Rect box;
	double speed;
	Type type;
};