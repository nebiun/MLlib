#include <MLlib.h>

int main(int argc, char **argv) 
{	ML_InitConsoleMode();
	
	printf("\n\nHello World ! \n\n");
	
	while(1)
	{
		if(Pad[0].Held.Start) { printf("Pad Start\n"); ML_ReturnToWii(); }
		if(Pad[0].Held.A) { printf("Pad A\n"); ML_ExitConsoleMode(); }
		if(Pad[0].Held.B) { printf("Pad B\n"); }
		if(Pad[0].Held.X) { printf("Pad X\n"); }
		if(Pad[0].Held.Y) { printf("Pad Y\n"); }
		if(Pad[0].Held.L) { printf("Pad L\n"); }
		if(Pad[0].Held.R) { printf("Pad R\n"); }
		if(Pad[0].Held.Z) { printf("Pad Z\n"); }
		if(Pad[0].Held.Left) { printf("Pad Left\n"); }
		if(Pad[0].Held.Right) { printf("Pad Right\n"); }
		if(Pad[0].Held.Up) { printf("Pad Up\n"); }
		if(Pad[0].Held.Down) { printf("Pad Down\n"); }
		if(Pad[0].Held.Left) { printf("Stick Left\n"); }
		if(Pad[0].Stick.Held.Right) { printf("Stick Right\n"); }
		if(Pad[0].Stick.Held.Up) { printf("Stick Up\n"); }
		if(Pad[0].Stick.Held.Down) { printf("Stick Down\n"); }
		
		ML_RefreshConsoleMode();
	}
	
	return 0;
}

