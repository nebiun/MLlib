/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to emulate a writing machine.


Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>

#include "FreeSerif_ttf.h"
#include "key_mp3.h"

#define LENGTH 700

int main(int argc, char **argv) 
{
	ML_Init();
	ML_InitMP3();
	
	ML_Font font;
	ML_LoadFontFromBuffer(&font, FreeSerif_ttf, FreeSerif_ttf_size, 16);
	
	char *text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque a congue mi. In eros eros, lacinia sit amet bibendum quis, tristique sit amet ligula. Aenean quis urna in neque tempus lacinia. Praesent at vulputate ipsum. Morbi pellentesque, ipsum ac ultrices sodales, magna lectus tincidunt justo, vel volutpat felis enim in nunc. Pellentesque gravida convallis erat et rhoncus. Duis euismod porttitor malesuada. Nulla sed arcu metus, consequat imperdiet eros. Nulla quis felis in ante consequat pellentesque vitae non dolor. Aliquam erat volutpat. Maecenas tempor, justo vel sagittis ullamcorper, diam odio facilisis leo, quis tincidunt eros est eu nunc.";
	
	char toDraw[LENGTH] = "";
		
	int time = 0;
	int cursor = 0;
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_DeleteFont(&font); ML_Exit(); } 
		
		if(time == 35 && cursor < LENGTH)
		{
			time = 0;
			cursor++;
			strncpy(toDraw, text, cursor);
			ML_PlayMP3FromBuffer(key_mp3, key_mp3_size);
		}
		
		ML_DrawText(&font, 16, 16, toDraw);
		
		if(cursor < LENGTH)
			time++;
			
		ML_Refresh();
	} 
	
	return 0;
}

