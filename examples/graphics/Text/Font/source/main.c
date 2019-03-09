/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to print some text with fonts.

Functions explained : 
- ML_LoadFontFromBuffer(fontStructure, nameofthefont_ttf, nameofthefont_ttf_size, pointSize)
- ML_LoadFontFromFile(fontStructure, "/path/to/the/font.ttf", pointSize)
- ML_DrawText(fontStructure, xPosition, yPosition, text)
- ML_GetTextInfo(fontStructure, text)
- ML_DeleteFont(fontStructure)


To make a new line, insert "#n".
To make an indentation, insert "#t".
To change the color, insert "#cX" where X is :  (or modify (GXColor)font.color)
- "0" : white;
- "1" : red;
- "2" : green;
- "3" : deep-blue;
- "4" : purple;
- "5" : light-blue;
- "6" : yellow;
- "7" : grey;
- "8" : dark-grey;
- "9" : black;
- nothing ("#c" only) : the original color will be applied.

Take a look in MLlib_Others/fonts for some
example of fonts.

You need a file HappyHell.ttf in your SD card at "/data/mllib/" to execute this code.


Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>

#define FREE_SERIF 0
#define HAPPY_HELL 1

#include "FreeSerif_ttf.h"
#include "HappyHell_ttf.h"

int main(int argc, char **argv) 
{
	usleep(1000*20);
	ML_Init();
	ML_InitFAT();
	ML_EnableTextureAntiAliasing(); // it's better with TTF fonts if they are moving
	srand(time(NULL));
	
	int x = 20, y = 15;
	int step = 0;
	
	int TTF = FREE_SERIF;
	
	ML_TextInfo textInfo;

	ML_Font font;
	ML_LoadFontFromBuffer(&font, FreeSerif_ttf, FreeSerif_ttf_size, 24);
	font.style = FONT_DEFAULT | FONT_UNDERLINE;

	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteFont(&font); ML_Exit(); }
		
		if(Wiimote[0].Released.One)
		{ 
			if(TTF != FREE_SERIF)
			{ 
				ML_DeleteFont(&font);
				ML_LoadFontFromBuffer(&font, FreeSerif_ttf, FreeSerif_ttf_size, 24);
				TTF = FREE_SERIF;
			}
		}
		else if(Wiimote[0].Released.Two) 
		{ 
			if(TTF != HAPPY_HELL)
			{ 
				ML_DeleteFont(&font);
				if(!ML_LoadFontFromFile(&font, "/data/mllib/HappyHell.ttf", 32)) // load a font from the file HappyHell.ttf located in the SD Card
				{ 
					// load fails (are you sure the file is in your SD Card ?)
					ML_DeleteFont(&font);
					ML_Exit();
				}
				
				TTF = HAPPY_HELL;
			}
		} 
		
		if(Wiimote[0].Newpress.B) // change the font color randomly when pressing B 
			font.color = (GXColor){rand() & 0xff, rand() & 0xff, rand() & 0xff, rand() & 0xff};
	
		if(Wiimote[0].Held.Plus) { font.alpha++; }
		else if(Wiimote[0].Held.Minus) { font.alpha--; } // play with alpha
		
		if(Wiimote[0].Held.Right) x++;
		else if(Wiimote[0].Held.Left) x--;
		if(Wiimote[0].Held.Down) y++;
		else if(Wiimote[0].Held.Up) y--;
		
		if(Wiimote[0].Newpress.A)
		{
			if(step < 3)
				step++;
			else step = 0;
			
			switch(step)
			{
				case 0:
					font.style = FONT_DEFAULT;
					break;
				case 1:
					font.style = FONT_DEFAULT | FONT_STRIKE;
					break;
				case 2:
					font.style = FONT_DEFAULT | FONT_UNDERLINE;
					break;
				case 3:
					font.style = FONT_DEFAULT | FONT_UNDERLINE | FONT_STRIKE;
					break;
			}
		}
		
		ML_DrawText(&font, x, y, "#tTabulation#nN#c0ew#c1li#c2ne #c3wi#c4th c#c7ol#c8ors#c ! :)#n#nPress A to strike or underline the text !");
		ML_DrawText(&font, 20, 300, "Alpha : %d", font.alpha);
		
		textInfo = ML_GetTextInfo(&font, "Bla bla bla text");
		ML_DrawText(&font, 20, 200, "'Bla bla bla text' has a width of %d and a height of %d", textInfo.width, textInfo.height);
		ML_DrawText(&font, 20, 350, "Step : %d (style = %x)", step, font.style);
		ML_Refresh();
	} 
	
	return 0;
}

