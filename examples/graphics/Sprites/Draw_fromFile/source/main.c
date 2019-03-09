/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to draw a sprite previously loaded from a file.

Functions explained : 
- bool ML_LoadSpriteFromFile(image, sprite, filename, x, y);
- void ML_DrawSprite(sprite);

The only thing which has to be explained here in filename,
it has to be like "/file.png" or "file.png" or "/folder/file.png" et c...

Some transformation functions are also explained :
- ML_CloneSprite(newsprite, clonedsprite);
- ML_SetSpriteSize(sprite, width, height); <- you can also scale the sprite with ML_SetSpriteScale(sprite, scaleWidth, scaleHeight);
- ML_SetSpriteAlpha(sprite, alpha);
- ML_MoveSpriteWiimoteIR(sprite, wiimoteNumber);
- ML_MoveSpriteWiimotePad(sprite, wiimoteNumber);
- ML_RotateSprite(sprite, angle, willItRotateAutomaticalyOrNot);

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>

int main(int argc, char **argv) 
{
	ML_Init();
	ML_InitFAT();
	
	ML_SplashScreen(); // Shows the SplashScreen 
	
	ML_Image spriteData;
	ML_Sprite sprite, sprite_clone; // we declare two sprites
	ML_LoadSpriteFromFile(&spriteData, &sprite, "/texture.png", 100, 100); // <- you must have a texture.png in ARGB (32 bits) at the root of your card so that you can test this example
	ML_CloneSprite(&sprite, &sprite_clone); // Create a sprite_clone from sprite
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_Exit(); }
		
		if(Wiimote[0].Held.Plus) { sprite.width++; sprite.height++; } 
		else if(Wiimote[0].Held.Minus) { sprite.width--; sprite.height--; } 
		
		if(Wiimote[0].Held.One && sprite.alpha > 0) sprite.alpha--;
		else if(Wiimote[0].Held.Two && sprite.alpha < 255) sprite.alpha++;
		
		ML_MoveSpriteWiimoteIR(&sprite, 0); // ML_MoveSpriteWiimoteIR(ML_Sprite *sprite, u16 wiimoteNumber)
		ML_MoveSpriteWiimotePad(&sprite_clone, 0); // ML_MoveSpriteWiimotePad(ML_Sprite *sprite, u16 wiimoteNumber)
		
		ML_RotateSprite(&sprite, Wiimote[0].Orient.Roll, 0); // Here the sprite will rotate with the angle of the wiimote
		ML_RotateSprite(&sprite_clone, 25, 1); // Here the sprite_clone will rotate by 25 degrees each frame because "autoRotate" is enabled
		
		ML_DrawSprite(&sprite); // Draws the sprite on the screen
		ML_DrawSprite(&sprite_clone); // Draws the sprite_clone on the screen
		
		ML_Refresh();
	} 
	
	return 0;
}

