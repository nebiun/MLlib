/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to draw a background simply from the buffer (the .dol itself).

Functions explained : 
- void ML_LoadBackgroundFromBuffer(image, background, filename, x, y);
- void ML_DrawBackground(background);

The only thing which has to be explained here in filename,
it has to be like file_png .
You need to place the picture in the data folder.
And at least you have to #include "file_png.h" ! ;)

Some transformation functions are also explained :
- ML_CloneBackground(newBackground, clonedBackgroundNumber);
- ML_SetBackgroundSize(background, width, height); <- you can also scale the background with ML_SetBackgroundScale(background, scaleWidth, scaleHeight);
- ML_SetBackgroundAlpha(background, alpha);
- ML_RotateBackground(background, angle, willItRotateAutomaticalyOrNot);


Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "background_png.h"

int main(int argc, char **argv) 
{
	ML_Init();

	ML_SetBackgroundColor(GX_COLOR_WHITE); // Background is now white
	
	ML_Image backgroundData;
	ML_Background background, background2; // we declare our background	
	
	ML_LoadBackgroundFromBuffer(&backgroundData, &background, background_png, 100, 100); // we load the background	
	ML_CloneBackground(&background, &background2);
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&backgroundData); ML_Exit(); }
	 	
		if(Wiimote[0].Held.Plus) { background.width++; background.height++; } 
		else if(Wiimote[0].Held.Minus) { background.width--; background.height--; }  // we change width and height of the background
		
		if(Wiimote[0].Held.One && background.alpha > 0) background.alpha--;
		else if(Wiimote[0].Held.Two && background.alpha < 255) background.alpha++; // we change transparency (opacity) of the background
			
		ML_RotateBackground(&background, Wiimote[0].Orient.Roll, 0); // Here the background will rotate with the angle of the wiimote
		ML_RotateBackground(&background2, 25, 1); // Here the background2 will rotate by 25 degrees each frame because "autoRotate" is enabled
		
		ML_DrawBackground(&background2); // Draws the background2 on the screen
		ML_DrawBackground(&background); // Draws the background on the screen
		
		ML_Refresh();
	} 
	
	return 0;
}

