#include <MLlib.h>

#include "tetris_mod.h"

static MODPlay mod;

int main()
{
	ML_InitConsoleMode(); // we don't need graphics for this example
	ML_InitMOD(&mod); // inits the mod previously declared
	
	ML_PlayMODFromBuffer(&mod, tetris_mod);
	
	printf("\n");
	printf("Press A to return to the HBC.\n");
	printf("Press Home to reset your Wii.");
	
	while(1) 
	{
		if(Wiimote[0].Held.Home) { ML_ReturnToWii(); }
		else if(Wiimote[0].Held.A) { ML_ExitConsoleMode(); }
		
		ML_RefreshConsoleMode();
	}
	
	return 0;
}

