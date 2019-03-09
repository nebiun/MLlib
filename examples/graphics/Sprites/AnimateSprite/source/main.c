/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to animate a sprite.

Functions explained : 
- void ML_AnimateSprite(sprite, isTheAnimationEnabled, numberOfCyclesBetweenEachChanges);
- void ML_AnimateSpriteEx(sprite, isTheAnimationEnabled, numberOfCyclesBetweenEachChanges, fromThatTile, toThisOne);
- void ML_AnimateSpriteEx2(sprite, isTheAnimationEnabled, numberOfCyclesBetweenEachChanges, fromThatTile, toThisOne, forXLoops);

In order to animate a sprite, you need to initialize the tile system before !


Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "sprite_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_Image spriteData;
	ML_Sprite sprite[2];
	
	ML_LoadSpriteFromBuffer(&spriteData, &sprite[0], sprite_png, 200, 20);
	ML_InitTile(&sprite[0], 48, 96); // We init the tile system of the sprite : 48 is the width of a tile, 96 its height.
	ML_SetSpriteScale(&sprite[0], 2, 2); // It sets width * 2 and height * 2 for the sprite
	ML_CloneSprite(&sprite[0], &sprite[1]);
	ML_CloneSprite(&sprite[0], &sprite[2]);
	
	ML_AnimateSprite(&sprite[0], 1, 25); // The sprite[1] will be animated infinitely and between each frames there will be 25 cycles.
	ML_AnimateSpriteEx(&sprite[1], 1, 20, 0, 2); // The sprite[1] will be animated infinitely from the tile 0 to 2 and between each frames there will be 20 cycles.
	ML_AnimateSpriteEx2(&sprite[2], 1, 24, 0, 3, 2); // The sprite[2] will be animated 2 times from the tile 0 to 3 and between each frames there will be 24 cycles.
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&spriteData); ML_Exit(); }
	
		if(Wiimote[0].Newpress.One) { ML_AnimateSprite(&sprite[0], 1, 25); } // Enables the animation of the sprite 0, the lapse of time (in frames) between each tiles is set to 25
		else if(Wiimote[0].Newpress.Two) { ML_AnimateSprite(&sprite[0], 0, 25); } // Disables (25 is obsolete, not needed)
		
		ML_DrawSprite(&sprite[0]);
		ML_DrawSpriteXY(&sprite[1], 400, 20);
		ML_DrawSpriteXY(&sprite[2], 200, 200);
		
		ML_Refresh();
	} 
	
	return 0;
}

