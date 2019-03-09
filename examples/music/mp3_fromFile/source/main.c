#include <MLlib.h>

int main()
{
	ML_InitConsoleMode();
	ML_InitFAT();
	ML_InitMP3();
	
	printf("\nPlaying... or not ?");
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_ReturnToWii(); }
		else if(Wiimote[0].Newpress.A) { ML_ExitConsoleMode(); }	
			
		if (!ML_IsPlayingMP3()) { ML_PlayMP3FromFile("/music.mp3"); }  // to test this example, you need a "music.mp3" file in the root of your SD card
		
		ML_RefreshConsoleMode();
	}	
	return 0;
}

