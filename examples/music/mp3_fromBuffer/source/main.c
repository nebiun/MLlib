#include <MLlib.h>

#include "WorldOfGoo_SoundTrack22_mp3.h"

int main()
{
	ML_Init();
	ML_InitMP3();
	
	ML_SplashScreen();
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_Exit(); }
			
		if (!ML_IsPlayingMP3()) { ML_PlayMP3FromBuffer(WorldOfGoo_SoundTrack22_mp3, WorldOfGoo_SoundTrack22_mp3_size); }
		
		ML_Refresh();
	}	
	return 0;
}

