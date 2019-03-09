/*		-==========================-
		|		MLlib Example	   |
		-==========================-

What is anti-aliasing for textures ?

Launch this example to know. You will notice the difference between the 2 sprites. :)

Functions explained : 
- void ML_EnableTextureAntiAliasing();
- void ML_DisableTextureAntiAliasing();

Notes: 
- Anti-Aliasing for textures is disabled by default.
- Don't use with tiled sprites with non-opaque pixels. It's weird.

(you'll need two wiimotes, but you can modify the code in order to use just one)


Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "spr_png.h"
#include "spr_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_Image spriteData[2];
	ML_Sprite sprite[2];
	
	// the first sprite will have anti-alising enabled
	//ML_EnableTextureAntiAliasing();
	_aa_enabled = true;
	ML_LoadSpriteFromBuffer(&spriteData[0], &sprite[0], spr_png, 100, 100);
	//the second will not, it will be less nice to see
	ML_DisableTextureAntiAliasing();
	ML_LoadSpriteFromBuffer(&spriteData[1], &sprite[1], spr_png, 400, 100);

	while(1)
	{
		if(Wiimote[0].Newpress.Home) { ML_DeleteImage(&spriteData[0]); ML_DeleteImage(&spriteData[1]); ML_Exit(); }
			
		if(Wiimote[0].Held.Left) { sprite[0].x--; sprite[1].x--; }
		else if(Wiimote[0].Held.Right) { sprite[0].x++; sprite[1].x++; }
	
		if(Wiimote[0].Held.Up) { sprite[0].y--; sprite[1].y--; }
		else if(Wiimote[0].Held.Down) { sprite[0].y++; sprite[1].y++; }
		
		ML_EnableTextureAntiAliasing();
		ML_DrawSprite(&sprite[0]);
		ML_DisableTextureAntiAliasing();
		ML_DrawSprite(&sprite[1]);
			
		ML_Refresh();
	} 
	
	return 0;
}

