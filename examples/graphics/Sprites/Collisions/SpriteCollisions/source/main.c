/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to detect collision between sprites.

Functions explained : 
- bool ML_IsCollision(sprite1, sprite2);
- bool ML_IsCollisionEx(sprite1, sprite2);
- bool ML_IsWiimoteCollision(nbWiimote, sprite);

Two Wiimotes are required in order to test this example.

You have to know that :
	- ML_IsCollision is very fast, but not very accurate;
	- ML_IsCollisionEx is very accurate, but not very fast !

The second one (Ex) is accurate because the collision test is calculated with pixels. (Pixel Collision Detection)
Well, I don't know how to express it in english at the moment, but you will know what I'm saying if you test the example ! :p


Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "red_png.h"
#include "blue_png.h"
#include "font_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_Image redData, blueData, fontData;
	ML_Sprite red, blue, font;
	ML_LoadSpriteFromBuffer(&redData, &red, red_png, 200, 200);
	ML_LoadSpriteFromBuffer(&blueData, &blue, blue_png, 200, 400);
	
	ML_LoadSpriteFromBuffer(&fontData, &font, font_png, 0, 0);
	ML_InitTile(&font, 8, 8);	
	ML_SetSpriteScale(&font, 2, 2);
	
	ML_SetNumberOfPads(2, 0);
	
	while(1)
	{		
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&blueData); ML_DeleteImage(&redData); ML_DeleteImage(&fontData); ML_Exit(); }
		
		ML_MoveSpriteWiimotePad(&blue, 0);
		ML_MoveSpriteWiimotePad(&red, 1);
		
		ML_DrawSpriteText(&font, 30, 300, "ML_Collision : %d\nML_CollisionEx : %d\n", ML_IsCollision(&blue, &red), ML_IsCollisionEx(&blue, &red));
		ML_DrawSpriteText(&font, 30, 100, "Collision between red sprite and Wiimote : %d", ML_IsWiimoteInSprite(0, &red));
		ML_DrawSprite(&red);
		ML_DrawSprite(&blue);
		
		ML_Refresh();
	} 
	
	return 0;
}

