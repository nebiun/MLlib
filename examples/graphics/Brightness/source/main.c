/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to control the brightness of the screen.

Functions explained :
- void ML_Brightness(u8 alpha);
- bool ML_FadeOut();
- bool ML_FadeIn();

[------] ML_Brightness :
Alpha is a u8 value, from 0 to 255.
This function changes the opacity of the entire screen.
That's useful when you want to fade in and fade out ! 
It draws in fact a black rectangle with the "alpha" transparency.

[------] ML_FadeOut :
This function fades out, just that simple !
It returns 1 when it's finished. (0 if not)

[------] ML_FadeIn :
Thus functions fades in (after fade-out).
It returns 1 when it's finished. (0 if not)


In this example, I placed a "exit" flag, so that there is a fade-out 
when you press Home.

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "Minishlink_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_SplashScreen();
	
	ML_Image spriteData;
	ML_Sprite sprite;
	ML_LoadSpriteFromBuffer(&spriteData, &sprite, Minishlink_png, 100, 100); // Inits sprite
 	
 	u8 alpha = 0;
 	bool exit = false;
	
	while(1)
	{
		if(Wiimote[0].Newpress.Home) { exit = true; } 
	 	
		if(Wiimote[0].Held.Plus) { if(alpha < 255) alpha++; }
		else if(Wiimote[0].Held.Minus) { if(alpha > 0) alpha--; } 
		
		ML_DrawSprite(&sprite);
		
		ML_Brightness(alpha);
		
		if(exit)
			if(ML_FadeOut()) ML_Exit(); // ML_FadeOut (and In) returns 1 when the fading is finished
			
		ML_Refresh();
	} 
	
	return 0;
}

