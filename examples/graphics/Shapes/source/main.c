/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to render some simple shapes.

Functions explained : 
- void ML_DrawRect(x, y, width, height, rgbaColor, filled)

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>

int main(int argc, char **argv) 
{
	ML_Init();
	
	while(1)
	{
		if(Wiimote[0].Held.Home) { ML_Exit(); }
	
		ML_DrawRect(100, 200, 400, 50, 0x00FF00FF, false); // a green rectangle at (100, 200) with a width of 400 and a height of 50
		ML_DrawCircle(200, 100, 40, 0xFF0000FF, true); // a red filled circle at (200, 100) with a radius of 40px
		
		ML_Refresh();
	} 
	
	return 0;
}

