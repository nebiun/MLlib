#include <MLlib.h>

int main(int argc, char **argv) 
{	ML_InitConsoleMode();
	ML_EnableNunchuk(true);
	
	printf("Hello World !\n\n");
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_ExitConsoleMode(); }
		if(Nunchuk[0].Held.C) { printf("C pressed\n"); }
		if(Nunchuk[0].Held.Z) { printf("Z pressed\n"); }
		if(Nunchuk[0].Stick.Magnitude > 0.2)
		{
			if(Nunchuk[0].Stick.Angle > 80 && Nunchuk[0].Stick.Angle < 100) printf("Right\n");
			else if(Nunchuk[0].Stick.Angle > 170 && Nunchuk[0].Stick.Angle < 190) printf("Down\n");
			else if(Nunchuk[0].Stick.Angle > 260 && Nunchuk[0].Stick.Angle < 280) printf("Left\n");
			else if(Nunchuk[0].Stick.Angle > -10 && Nunchuk[0].Stick.Angle < 10) printf("Up\n");
		}
		
		ML_RefreshConsoleMode();
	}
	
	return 0;
}


