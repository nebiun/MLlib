/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to draw a sprite simply from the buffer (the .dol itself).

Functions explained : 
- void ML_LoadSpriteFromBuffer(image, sprite, filename, x, y);
- void ML_DrawSprite(sprite);
- void ML_DrawSpriteXY(sprite, X, Y); <- will not be in there though
- void ML_DrawSpriteFull(sprite, X, Y, angle, scaleWidth, scaleHeight, alpha);

The only thing which has to be explained here in filename,
it has to be like file_png .
You need to place the picture in the data folder.
And at least you have to #include "file_png.h" ! ;)

Some transformation functions are also explained :
- ML_CloneSprite(newSprite, clonedSpriteNumber);
- ML_SetSpriteSize(sprite, width, height); <- you can also scale the sprite with ML_SetSpriteScale(sprite, scaleWidth, scaleHeight);
- ML_SetSpriteAlpha(sprite, alpha);
- ML_MoveSpriteWiimoteIR(sprite, wiimoteNumber);
- ML_MoveSpriteWiimotePad(sprite, wiimoteNumber);
- ML_RotateSprite(sprite, angle, willItRotateAutomaticalyOrNot);


Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "Minishlink_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	ML_SplashScreen(); // Shows the SplashScreen 
	ML_SetBackgroundColor(GX_COLOR_WHITE); // Background is now white
	
	ML_Image spriteData;
	ML_Sprite sprite, sprite2; // we declare our sprite	
	
	ML_LoadSpriteFromBuffer(&spriteData, &sprite, Minishlink_png, 100, 100); // we load the sprite	
	ML_CloneSprite(&sprite, &sprite2);
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&spriteData); ML_Exit(); }
	 	
		if(Wiimote[0].Held.Plus) { sprite.width++; sprite.height++; } 
		else if(Wiimote[0].Held.Minus) { sprite.width--; sprite.height--; }  // we change width and height of the sprite
		
		if(Wiimote[0].Held.One && sprite.alpha > 0) sprite.alpha--;
		else if(Wiimote[0].Held.Two && sprite.alpha < 255) sprite.alpha++; // we change transparency (opacity) of the sprite
		
		ML_MoveSpriteWiimoteIR(&sprite, 0); // ML_MoveSpriteWiimoteIR(ML_Sprite *sprite, u8 wiimoteNumber);
		ML_MoveSpriteWiimotePad(&sprite2, 0); // ML_MoveSpriteWiimotePad(u16 spriteNumber, u16 wiimoteNumber)
		
		ML_RotateSprite(&sprite, Wiimote[0].Orient.Roll, 0); // Here the sprite will rotate with the angle of the wiimote
		ML_RotateSprite(&sprite2, 25, 1); // Here the sprite2 will rotate by 25 degrees each frame because "autoRotate" is enabled
		
		ML_DrawSprite(&sprite); // Draws the sprite on the screen
		ML_DrawSprite(&sprite2); // Draws the sprite2 on the screen
		
		// Here we draw another time the image using the texture of this one
		ML_DrawTexture(&spriteData.texObj, spriteData.data, 300, 350, 100, 100, 50, 1.5, 0.5, 255); // texture, X position, Y position, Width, Height, Angle in degrees, Scale X, Scale Y, Transparency (0->255)
		
		ML_Refresh();
	} 
	
	return 0;
}

