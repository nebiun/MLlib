/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to print some text.

Functions explained : 
- void ML_DrawSpriteText(sprite, X, Y, textWithArgumentsAndSomeCoolThings); 
- void ML_DrawSpriteTextLimit()
- void ML_DrawSpriteTextBox()
- void ML_DrawSpriteSimpleText(sprite, X, Y, text);

With ML_Text you can have arguments with your text, like
ML_DrawSpriteText(0, 0, 0, "Var X = %d", x);
And if the text is going to be not shown because screen is not enough large,
it will jump a line ! You can also use '\n' to jump a line.
If you want a simple text, choose ML_DrawSpriteSimpleText.

Take a look in MLlib_Others/fonts for some
example of fonts. PNG fonts need to be initialized like tiles.


Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "font_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	float scale = 1;
	
	ML_Image fontData;
	ML_Sprite font;
	ML_LoadSpriteFromBuffer(&fontData, &font, font_png, 100, 100);
	ML_InitTile(&font, 8, 8);	
	ML_SetSpriteScale(&font, 2, 2);
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&fontData); ML_Exit(); }
		
		if(Wiimote[0].Newpress.One) { scale = 1; }
		else if(Wiimote[0].Newpress.Two) { scale = 2; }
		ML_SetSpriteScale(&font, scale, scale); // Play with the scale of the text !
	
		if(Wiimote[0].Held.Plus) { font.alpha++; }
		else if(Wiimote[0].Held.Minus) { font.alpha--; } // and with alpha
		
		ML_DrawSpriteText(&font, 100, 150, "Hello World !\n- Scale : %f \n- Alpha : %d", scale, font.alpha); 
		ML_DrawSpriteSimpleText(&font, 100, 300, "Simple Text !");
		
		ML_DrawSpriteText(&font, 600, 470, "Auto jump to next line !");
		
		ML_DrawSpriteText(&font, 300, 400, "Width : %d \nHeight : %d\nTime Elapsed: %d", _screenWidth, _screenHeight, ML_ElapsedTime());
		
		ML_DrawSpriteTextBox(&font, 100, 320, 150, 400, "TextBox test ! It fits to the box indicated ! \\o/");
		
		ML_DrawSpriteTextLimit(&font, 0, 0, "Some long text which will be cut ! OMGWTFBBQ o_O", 11);
			
		ML_Refresh();
	} 
	
	return 0;
}

