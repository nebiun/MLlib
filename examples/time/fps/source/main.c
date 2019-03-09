/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to do show the FPS.

Functions explained : 
- int ML_GetFPS();

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>

#include "plop_png.h"
#include "font_png.h"
#include "cursor_png.h"

#define MAX_PLOP 2048 //you can increase this number if you want

int main(int argc, char **argv) 
{
	ML_Init();
	ML_SplashScreen();
	
	int i, j;
	
	ML_Image plopData;
	ML_Sprite plop[MAX_PLOP];
	ML_LoadSpriteFromBuffer(&plopData, &plop[0], plop_png, 100, 100);
	
	plop[0].visible = 0;
	for(i = 1; i < MAX_PLOP; i++)
	{
		plop[i] = plop[0];
	}
	i = 0;
	
	ML_Image fontData;
	ML_Sprite font;
	ML_LoadSpriteFromBuffer(&fontData, &font, font_png, 100, 100);
	ML_InitTile(&font, 8, 8);	
	ML_SetSpriteScale(&font, 2, 2);
	
	ML_Image cursorData;
	ML_Sprite cursor;
	ML_LoadSpriteFromBuffer(&cursorData, &cursor, cursor_png, 100, 100);
	
	while(1)
	{
		if(Wiimote[0].Newpress.Home) { ML_DeleteImage(&plopData); ML_DeleteImage(&fontData); ML_DeleteImage(&cursorData); ML_Exit(); }
	 	
	 	if(Wiimote[0].Released.A && i < MAX_PLOP)
	 	{
	 		plop[i].x = cursor.x - plop[i].tileWidth/2;
			plop[i].y = cursor.y - plop[i].tileHeight/2;
			plop[i].visible = 1;
			i++;
		}
		
		for(j = 0; j < i; j++)
		{
			if(plop[j].visible)
			{
				ML_DrawSprite(&plop[j]);
			}
		}
		
		ML_DrawSpriteText(&font, 20, 20, "%d", ML_GetFPS());
		
		ML_RotateSprite(&cursor, Wiimote[0].Orient.Roll, 0); 
		ML_Cursor(&cursor, 0);
		
		ML_Refresh();
	} 
	
	return 0;
}

