#include <MLlib.h>

int main(int argc, char **argv) 
{
	ML_InitConsoleMode();
	
	printf("Hello World !\n\n");
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { printf("Home pressed\n"); ML_ExitConsoleMode();}
		if(Wiimote[0].Held.A) { printf("A pressed\n"); }
		if(Wiimote[0].Held.B) { printf("B pressed\n"); }
		if(Wiimote[0].Held.One) { printf("1 pressed\n"); }
		if(Wiimote[0].Held.Two) { printf("2 pressed\n"); }
		if(Wiimote[0].Held.Plus) { printf("+ pressed\n"); }
		if(Wiimote[0].Held.Minus) { printf("- pressed\n"); }
		if(Wiimote[0].Held.Left) { printf("Left pressed\n"); }
		if(Wiimote[0].Held.Right) { printf("Right pressed\n"); }
		if(Wiimote[0].Held.Up) { printf("Up pressed\n"); }
		if(Wiimote[0].Held.Down) { printf("Down pressed\n"); }
		
		ML_RefreshConsoleMode();
	}
	
	return 0;
}


