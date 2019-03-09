/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to show the MLlib SplashScreen.

Functions explained : 
- void ML_SplashScreen();

If you like my library, and/or support it (or if not :p ),
feel free to show this SplashScreen ! :-)
And thanks a lot for that ! :-D


Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_SplashScreen();
	
	while(1)
	{
		if(Wiimote[0].Newpress.Home) { ML_Exit(); }
		
		ML_Refresh();
	} 
	
	return 0;
}

