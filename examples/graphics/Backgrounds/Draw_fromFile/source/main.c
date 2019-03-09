/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to draw a background previously loaded from a file.

Functions explained : 
- bool ML_LoadBackgroundFromFile(image, background, filename, x, y);
- void ML_DrawBackground(background);

The only thing which has to be explained here in filename,
it has to be like "/file.png" or "file.png" or "/folder/file.png" et c...

Some transformation functions are also explained :
- ML_CloneBackground(newBackground, clonedBackground);
- ML_SetBackgroundSize(background, width, height); <- you can also scale the background with ML_SetBackgroundScale(background, scaleWidth, scaleHeight);
- ML_SetBackgroundAlpha(background, alpha);
- ML_RotateBackground(background, angle, willItRotateAutomaticalyOrNot);

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>

int main(int argc, char **argv) 
{
	ML_Init();
	ML_InitFAT();
	
	ML_SplashScreen(); // Shows the SplashScreen 
	
	ML_Image backgroundData;
	ML_Background background, background_clone; // we declare two backgrounds
	ML_LoadBackgroundFromFile(&backgroundData, &background, "/background.png", 100, 100); // <- you must have a background.png in ARGB (32 bits) at the root of your card so that you can test this example
	ML_CloneBackground(&background, &background_clone); // Create a background_clone from background
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&backgroundData); ML_Exit(); }
		
		if(Wiimote[0].Held.Plus) { background.width++; background.height++; } 
		else if(Wiimote[0].Held.Minus) { background.width--; background.height--; } 
		
		if(Wiimote[0].Held.One && background.alpha > 0) background.alpha--;
		else if(Wiimote[0].Held.Two && background.alpha < 255) background.alpha++;
			
		ML_RotateBackground(&background, Wiimote[0].Orient.Roll, 0); // Here the background will rotate with the angle of the wiimote
		ML_RotateBackground(&background_clone, 25, 1); // Here the background_clone will rotate by 25 degrees each frame because "autoRotate" is enabled
		
		ML_DrawBackground(&background); // Draws the background on the screen
		ML_DrawBackground(&background_clone); // Draws the background_clone on the screen
		
		ML_Refresh();
	} 
	
	return 0;
}

