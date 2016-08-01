#include "Pinball.h"

int main()
{
	Pinball p;
	p.changeState(Pinball::GameState::IN_MENU);
	p.gameLoop();
	return 0;
}