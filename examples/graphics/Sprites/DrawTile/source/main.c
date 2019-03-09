/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to draw a tile of a sprite.

Functions explained : 
- void ML_InitTile(sprite, widthOfOneTile, heightOfOneTile);
- void ML_DrawTile(sprite, X, Y, whichTile);

When you want to use the tile system on a sprite, you need to 
initialize the sprite with ML_InitTile.
Then you can use ML_DrawTile ! :-)

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "sprite_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_Image spriteData;
	ML_Sprite sprite;
	ML_LoadSpriteFromBuffer(&spriteData, &sprite, sprite_png, 100, 100);
	ML_InitTile(&sprite, 48, 96);
	
	while(1)
	{
		if(Wiimote[0].Newpress.Home) { ML_DeleteImage(&spriteData); ML_Exit(); }
			
		if(Wiimote[0].Held.Left) { sprite.currentFrame = 3; sprite.x--; }
		else if(Wiimote[0].Held.Right) { sprite.currentFrame = 1; sprite.x++; }
		
		if(Wiimote[0].Held.Up) { sprite.currentFrame = 0; sprite.y--; }
		else if(Wiimote[0].Held.Down) { sprite.currentFrame = 2; sprite.y++; }
		
		ML_DrawTile(&sprite, sprite.x, sprite.y, sprite.currentFrame);
			
		ML_Refresh();
	} 
	
	return 0;
}

