/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to flip a sprite horizontally and vertically.

Functions explained : 
- void ML_FlipSpriteX(sprite, flipX_enabled);
- void ML_FlipSpriteY(sprite, flipY_enabled);
- void ML_FlipSpriteXY(sprite, flipX_enabled, flipY_enabled);

Don't use a pixel-detection after that. Well, you can if it's a rectangle.

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "sprite_png.h"
#include "minishlink_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_Image spriteData, minishlinkData;
	ML_Sprite sprite, minishlink;
	
	ML_LoadSpriteFromBuffer(&spriteData, &sprite, sprite_png, 100, 100);
	ML_InitTile(&sprite, 48, 96);
	
	ML_LoadSpriteFromBuffer(&minishlinkData, &minishlink, minishlink_png, 300, 100);
	
	while(1)
	{
		if(Wiimote[0].Newpress.Home) { ML_DeleteImage(&spriteData); ML_Exit(); }
			
		if(Wiimote[0].Newpress.One) { ML_FlipSpriteX(&sprite, 1); }
		else if(Wiimote[0].Newpress.Two) { ML_FlipSpriteX(&sprite, 0); }
		
		if(Wiimote[0].Newpress.Plus) { ML_FlipSpriteY(&sprite, 1); }
		else if(Wiimote[0].Newpress.Minus) { ML_FlipSpriteY(&sprite, 0); }
		
		if(Wiimote[0].Newpress.Up) { ML_FlipSpriteY(&minishlink, 1); }
		else if(Wiimote[0].Newpress.Down) { ML_FlipSpriteY(&minishlink, 0); }
		else if(Wiimote[0].Newpress.Right) { ML_FlipSpriteXY(&minishlink, 1, 1); }
		else if(Wiimote[0].Newpress.Left) { ML_FlipSpriteXY(&minishlink, 0, 0); }
 		
		ML_DrawTile(&sprite, sprite.x, sprite.y, sprite.currentFrame);
		ML_DrawSprite(&minishlink);
			
		ML_Refresh();
	} 
	
	return 0;
}

