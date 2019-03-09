/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to make a screenshot.

Function explained : 
- bool ML_Screenshot(filename);

You must init the FAT before calling this function !

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "Minishlink_png.h"
#include "blue_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	ML_InitFAT(); // you MUST to init FAT ! 
	
	ML_SplashScreen();
	
	ML_SetBackgroundColor(GX_COLOR_WHITE);
	
	ML_Image spriteData, blueData;
	ML_Sprite sprite, blue;
	ML_LoadSpriteFromBuffer(&spriteData, &sprite, Minishlink_png, 100, 100);
	ML_LoadSpriteFromBuffer(&blueData, &blue, blue_png, 200, 200);
	
	bool ok = false;
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&spriteData); ML_DeleteImage(&blueData); ML_Exit(); }
	 	
		if(Wiimote[0].Held.One && Wiimote[0].Held.Two && ok == false) { ok = ML_Screenshot("/screenshot.png"); } 
		
		if(ok == false)
		{
			ML_DrawSprite(&sprite);
			ML_DrawSprite(&blue); 
		}
		else 
		{
			ML_DrawSpriteXY(&sprite, 400, 300);
			ML_DrawSpriteXY(&blue, 400, 400); 
		}
		
		ML_Refresh();
	} 
	
	return 0;
}

