/*		-==========================-
		|		MLlib Example	   |
		-==========================-

How to detect collision between circle/circle, rect/rect, rect/circle.

Functions explained : 
- bool ML_IsCollisionRectRect(x1, y1, width1, height1, x2, y2, width2, height2)
- bool ML_IsCollisionCircleCircle(centerX1, centerY1, radius1, centerX2, centerY2, radius2)
- bool ML_IsCollisionRectCircle(rectX, rectY, rectWidth, rectHeight, circleCenterX, circleCenterY, circleRadius)

Two Wiimotes are required in order to test this example.

Author : Minishlink
MLlib Website : http://louislagrange.free.fr/MLlib 

Thanks ! 													*/

#include <MLlib.h>
#include "rect_png.h"
#include "circle_png.h"
#include "font_png.h"

int main(int argc, char **argv) 
{
	ML_Init();
	
	ML_Image rectData, circleData, fontData;
	ML_Sprite rect1, rect2, circle1, circle2, font;
	ML_LoadSpriteFromBuffer(&rectData, &rect1, rect_png, 100, 100);
	ML_LoadSpriteFromBuffer(&circleData, &circle1, circle_png, 150, 300);
	
	ML_CloneSprite(&rect1, &rect2);
	ML_CloneSprite(&circle1, &circle2);
	
	ML_LoadSpriteFromBuffer(&fontData, &font, font_png, 0, 0);
	ML_InitTile(&font, 8, 8);
	ML_SetSpriteScale(&font, 1.5, 1.5);
	
	ML_SetNumberOfPads(2, 0);
	
	while(1)
	{		
		if(Wiimote[0].Held.Home) { ML_DeleteImage(&rectData); ML_DeleteImage(&circleData); ML_DeleteImage(&fontData); ML_Exit(); }
		
		ML_MoveSpriteWiimotePad(&rect2, 0);
		ML_MoveSpriteWiimotePad(&circle2, 1);
		
		ML_DrawSprite(&rect1);
		ML_DrawSprite(&rect2);
		ML_DrawSprite(&circle1);
		ML_DrawSprite(&circle2);
		
		ML_DrawSpriteText(&font, 30, 300, "Rect/Rect: %d\nCircle/Circle: %d\nRect/Circle: %d", 
			ML_IsCollisionRectRect (rect1.x, rect1.y, rect1.width, rect1.height,
									rect2.x, rect2.y, rect2.width, rect2.height),
			ML_IsCollisionCircleCircle (circle1.x + circle1.width/2, circle1.y + circle1.height/2, circle1.width/2,
										circle2.x + circle2.width/2, circle2.y + circle2.height/2, circle2.width/2),
			ML_IsCollisionRectCircle (rect1.x, rect1.y, rect1.width, rect1.height,
									  circle2.x + circle2.width/2, circle2.y + circle2.height/2, circle2.width/2));
		
		ML_Refresh();
	} 
	
	return 0;
}

