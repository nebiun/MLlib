#include <MLlib.h>

int main(int argc, char **argv) 
{	ML_InitConsoleMode();
	ML_InitRand();
	
	printf("\n\nHello World !\n\n");
	printf("%s", ML_GetTimeChar());
	printf("\nPress B to print a ramdom number between 0 and 100 !\n\n");

	while(1)
	{
		if(Wiimote[0].Newpress.Home) ML_ExitConsoleMode();
		if(Wiimote[0].Newpress.B) printf(" %d\n", ML_Rand(0, 100));
		
		ML_RefreshConsoleMode();
	}
	
	return 0;
}
