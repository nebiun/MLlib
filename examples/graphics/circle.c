#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <unistd.h>

#include "GRRLIB/GRRLIB.h"

int gohome = 0;
Mtx GXmodelView2D;

/* http://www.inversereality.org/tutorials/graphics%20programming/circles.html
   http://groups.csail.mit.edu/graphics/classes/6.837/F98/Lecture6/circle.html
 */

void _CirclePoints (s32 cx, s32 cy, s32 x, s32 y, u32 c)
{
    if (x == 0)
    {
        GRRLIB_Plot(cx, cy+y, c);
        GRRLIB_Plot(cx, cy-y, c);
        GRRLIB_Plot(cx+y, cy, c);
        GRRLIB_Plot(cx-y, cy, c);
    }
    else if (x == y)
    {
        GRRLIB_Plot(cx+x, cy+y, c);
        GRRLIB_Plot(cx-x, cy+y, c);
        GRRLIB_Plot(cx+x, cy-y, c);
        GRRLIB_Plot(cx-x, cy-y, c);
    }
    else if (x < y)
    {
        GRRLIB_Plot(cx+x, cy+y, c);
        GRRLIB_Plot(cx-x, cy+y, c);
        GRRLIB_Plot(cx+x, cy-y, c);
        GRRLIB_Plot(cx-x, cy-y, c);
        GRRLIB_Plot(cx+y, cy+x, c);
        GRRLIB_Plot(cx-y, cy+x, c);
        GRRLIB_Plot(cx+y, cy-x, c);
        GRRLIB_Plot(cx-y, cy-x, c);
    }
}

void Circle (s32 xcenter, s32 ycenter, s32 radius, u32 color)
{
    s32 x = 0;
    s32 y = radius;
    s32 p = (5 - radius*4)/4;
    _CirclePoints(xcenter, ycenter, x, y, color);
    while (x < y)
    {
        x++;
        if (p < 0)
        {
            p += 2*x+1;
        }
        else
        {
            y--;
            p += 2*(x-y)+1;
        }
        _CirclePoints(xcenter, ycenter, x, y, color);
    }
}

void draw_screen()
{
    static s32 xcenter = 320;
    static s32 ycenter = 240;
    static s32 radius = 100;
    static u32 color = 0xFFFFFFFF;
    
    f32 rectw = 480;
    f32 recth = 480;
    GRRLIB_Rectangle(xcenter-rectw/2, ycenter-recth/2, rectw, recth, color, 0);// l t r b
    Circle (xcenter, ycenter, radius, color);
    rectw = 640;
    recth = 640;
    GRRLIB_Rectangle(xcenter-rectw/2, ycenter-recth/2, rectw, recth, color, 0);// l t r b
    
    u16 r;
    for(r=240;r<=320;r=r+20)
    {
        Circle (xcenter, ycenter, r, color);
    }
    Circle (xcenter, ycenter, 426, color);

    
}

void clear_screen()
{
    GRRLIB_FillScreen(0xFF000000);
    GRRLIB_Render();
}

void fade_screen()
{
    u16 i;
    int step = 8;
    for(i=1;i<255;i=i+step)
    {
        draw_screen();
        GRRLIB_FillScreen(i<<24);
        GRRLIB_Render();
    }
    GRRLIB_FillScreen(0xFF000000);
    GRRLIB_Render();
}

void check_wiimote()
{
    int res;
    u32 type;
    WPADData *wd;

    WPAD_ReadPending(WPAD_CHAN_ALL, 0 /*countevs*/);
    res = WPAD_Probe(0, &type);
    if (res == WPAD_ERR_NONE)
    {
        wd = WPAD_Data(0);
        if (wd->btns_h & WPAD_BUTTON_HOME)
        {
            gohome = 1;
        }
    }
}


void goodbye()
{
    fade_screen();
    //blink_dvd_led()
}


int main(int argc, char **argv) {
    
    VIDEO_Init();
    WPAD_Init();
    
    GRRLIB_InitVideo();
    GRRLIB_Start();
    
    while (!gohome)
    {
        draw_screen();
        GRRLIB_Render();

        check_wiimote();
    }
    goodbye();
    return 0;
}
