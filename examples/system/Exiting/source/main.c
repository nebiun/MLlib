#include <MLlib.h>

int main(int argc, char **argv) 
{	ML_Init();
	ML_SplashScreen(); // You can delete this instruction, but please let it if you can :)
		
	while(1)
	{
		if(Wiimote[0].Newpress.Home) ML_Exit(); // returns to HBC
		else if(Wiimote[0].Newpress.One) ML_ReturnToWii(); // returns to Wii
		else if(Wiimote[0].Newpress.Two) ML_ShutdownWii(); // shuts down Wii
		
		ML_Refresh();
	}
	
	return 0;
}

