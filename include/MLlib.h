#ifndef DEF_MLLIB_H
#define DEF_MLLIB_H

/**
 * @mainpage MLlib Documentation
 * @image html MLlib_logo.png
 * Hi and welcome to the MLlib documentation !
 */
 
/**
* \file
* \brief This file is the "central-mother" of the lib.
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <network.h>
#include <errno.h>
#include <math.h>
#include <gccore.h>
#include <ogcsys.h>
#include <ogc/ios.h>
#include <ogc/ipc.h>
#include <ogc/lwp_watchdog.h>
#include <asndlib.h>
#include <aesndlib.h>
#include <gcmodplay.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <wchar.h>
#include <mp3player.h>

// libpng ported to Wii by mavakadachi 
#include <png.h>

// FreeTypelib ported to Wii by Tantric
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H

// MLlib now
#include "MLlib/ML_define.h"
#include "MLlib/ML_globals.h"

#include "MLlib/ML_draw.h"
#include "MLlib/ML_time.h"
#include "MLlib/ML_init.h"
#include "MLlib/ML_system.h"
#include "MLlib/ML_video.h"
#include "MLlib/ML_sprites.h"
#include "MLlib/ML_input.h"
#include "MLlib/ML_mp3player.h"
#include "MLlib/ML_modplayer.h"
#include "MLlib/ML_backgrounds.h"
#include "MLlib/ML_images.h"
#include "MLlib/ML_math.h"
#include "MLlib/ML_font.h"
#include "MLlib/ML_png.h"

#endif

