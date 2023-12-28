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
	
	int idx=0;
	GXColor color = (GXColor){0xff,0xff,0xff,0x00};
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&fontData); ML_Exit(); }
		
		if(Wiimote[0].Newpress.One) { 
			if(scale > 1)
				scale -= 1; 
		}
		else if(Wiimote[0].Newpress.Two) { 
			if(scale < 10)
				scale += 1; 
		}
		ML_SetSpriteScale(&font, scale, scale); // Play with the scale of the text !
	
		// Play with color
		if(Wiimote[0].Newpress.A) {
			idx++;
			if(idx == 3)
				idx = 0;
		}
		if(Wiimote[0].Newpress.Up) {
			switch(idx) {
			case 0:
				if(color.r < 255) color.r += 1;
				break;
			case 1:
				if(color.g < 255) color.g += 1;
				break;
			case 2:
				if(color.b < 255) color.b += 1;
				break;
			}
		}			
		if(Wiimote[0].Newpress.Down) {
			switch(idx) {
			case 0:
				if(color.r > 0) color.r -= 1;
				break;
			case 1:
				if(color.g > 0) color.g -= 1;
				break;
			case 2:
				if(color.b > 0) color.b -= 1;
				break;
			}
		}
		
		// and with alpha
		if(Wiimote[0].Held.Plus) {
			if (font.alpha < 255)
				font.alpha++; 
		}
		else if(Wiimote[0].Held.Minus) { 
			if (font.alpha > 1)
				font.alpha--; 
		}
		color.a = font.alpha;
		
		ML_DrawSpriteText(&font, 100, 150, "Hello World !\n- Scale : %f (press 1 or 2)\n- Alpha : %d (use key + and -)\n- rgb   : %2x %2x %2x (A to switch, up and down to change)\n          %2s %2s %2s", 
			scale, color.a, color.r, color.g, color.b,
			(idx == 0)?"^^":"  ", (idx == 1)?"^^":"  ", (idx == 2)?"^^":"  "); 
		ML_DrawSpriteSimpleText(&font, 100, 300, "Simple Text !");
		
		ML_DrawSpriteText(&font, 600, 440, "Auto jump to next line !");
		
		ML_DrawSpriteColorText(&font, 300, 400, color, "Width : %d \nHeight : %d\nTime Elapsed: %d", _screenWidth, _screenHeight, ML_ElapsedTime());
		
		ML_DrawSpriteColorTextBox(&font, 100, 320, 150, 400, color, "TextBox test ! It fits to the box indicated ! \\o/");
		
		ML_DrawSpriteTextLimit(&font, 0, 0, "Some long text which will be cut ! OMGWTFBBQ o_O", 11);
			
		ML_Refresh();
	} 
	
	return 0;
}
