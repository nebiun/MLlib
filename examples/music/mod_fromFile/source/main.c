#include <MLlib.h>

static MODPlay mod;

int main()
{
	ML_InitConsoleMode(); // we don't need graphics for this example
	ML_InitFAT(); // needed for access to the SD card
	ML_InitMOD(&mod); // inits the mod previously declared
	
	ML_PlayMODFromFile(&mod, "music.mod"); // to test this example, you must have a "music.mod" file in the root of your SD card
	
	printf("\n");
	printf("Press A to return to the HBC.\n");
	printf("Press Home to reset your Wii.");
	printf("\n");
	printf("MOD is playing from file.");
	
	while(1) 
	{
		if(Wiimote[0].Held.Home) { ML_ReturnToWii(); }
		else if(Wiimote[0].Held.A) { ML_ExitConsoleMode(); }
		
		ML_RefreshConsoleMode();
	}
}

