/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to apply some transformations on an image while playing with colors.

Functions explained :
- void ML_ApplyGrayscaleToImage(image);
- void ML_InvertImageColors(image);

After doing any modification on an image, pay attention to call ML_FlushImage(image) ! It won't be modified else. ;)

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "Minishlink_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_SplashScreen(); // Shows the SplashScreen 

	ML_Image spriteData;
	ML_Sprite sprite;
	ML_LoadSpriteFromBuffer(&spriteData, &sprite, Minishlink_png, 100, 100); // Inits sprite
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&spriteData); ML_Exit(); }

		if(Wiimote[0].Held.Plus) { sprite.width++; sprite.height++; } 
		else if(Wiimote[0].Held.Minus) { sprite.width--; sprite.height--; } 
		
		if(Wiimote[0].Newpress.One) { ML_ApplyGrayscaleToImage(&spriteData); ML_FlushImage(&spriteData); }
		else if(Wiimote[0].Newpress.Two) { ML_InvertImageColors(&spriteData); ML_FlushImage(&spriteData); }
		
		ML_DrawSprite(&sprite); // Draws the sprite 0 on the screen

		ML_Refresh();
	} 
	
	return 0;
}

