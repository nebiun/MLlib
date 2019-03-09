/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to get or set the color value of a pixel on a sprite.

Functions explained :
- void ML_SetPixelColor(image, X, Y, color);
- u32 ML_GetPixelColor(image, X, Y); <- Will not be explained, it's obvious when you know the Set function ;)

These colors are ARGB (Alpha Red Green Blue). Why ARGB and not RGB or YCbCr ? Because your png are in ARGB colors ! :)
You can find the RGB color on different software or online; it's also named HTML color.
For example, HTML color red is "FF0000" or "#FF0000" if you search through software or online, BUT !
But you need to enter "0xFF0000" to convert it to a RGB color !
And finally add FF (it's in fact alpha) to the end, so it'll look like : "0xFF0000FF". That's ARGB. ;)
Here are some colors for us : (Color | ARGB)
- Black 	0x000000FF
- White 	0xFFFFFFFF
- Grey		0x808080FF
- Red 		0xFF0000FF
- Blue		0x0000FFFF
- Green		0x00FF00FF
- Yellow	0xFFFF00FF

After doing any modification on an image, pay attention to call ML_FlushImage(image) ! It won't be modified else. ;)

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "Minishlink_png.h"
#include "font_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_SplashScreen(); // Shows the SplashScreen 

	ML_Image spriteData;
	ML_Sprite sprite;
	ML_LoadSpriteFromBuffer(&spriteData, &sprite, Minishlink_png, 100, 100); // Inits sprite
	
	u16 x, y;
	for(y=0;y<50;y++)
        for(x=0;x<50;x++)
        	ML_SetPixelColor(&spriteData, x, y, 0xFFFF00FF); // This will sets the pixels from (0;0) to (50;50) in yellow. (yes, it's awful)
	ML_FlushImage(&spriteData);
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&spriteData); ML_Exit(); }

		if(Wiimote[0].Held.Plus) { sprite.width++; sprite.height++; } 
		else if(Wiimote[0].Held.Minus) { sprite.width--; sprite.height--; } 
		
		ML_DrawSprite(&sprite); // Draws the sprite 0 on the screen

		ML_Refresh();
	} 
	
	return 0;
}

