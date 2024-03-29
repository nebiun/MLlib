#ifndef DEF_ML_VIDEO_H
#define DEF_ML_VIDEO_H

#ifdef __cplusplus
   extern "C" {
#endif /* __cplusplus */

#define DEFAULT_FIFO_SIZE	(256*1024)

/**
* \struct ML_Image
* \brief This is the structure for images.
*/
typedef struct { 
	GXTexObj texObj; /*!< Texture */
	u8 *data; /*!< Data (ARGB) */
	u16 width, /*!< Width */
	height; /*!< Height */
} ML_Image;

/**
* \struct ML_Sprite
* \brief This is the structure for sprites.
*/
typedef struct {
	ML_Image *image;  /*!< Pointer to the image associated with */
	long i;  /*!< Used for the animation */
	s16 x,  /*!< X position */
	y; /*!< Y position */
	s8 dx, /*!< X velocity */
	dy; /*!< Y velocity */
	bool visible; /*!< Member for setting the sprite visible or not */
	u16 width; /*!< Width */
	u16 height; /*!< Height */
	u8 rotated; /*!< Is rotation enabled */
	u8 alpha; /*!< Transparency (0-255) */
	float scaleX, /*!< X scaling */
	scaleY; /*!< Y scaling */
	float angle; /*!< Angle in degrees */
	bool tiled; /*!< Is tiling enabled */
	bool animated; /*!< Is animation enabled */
	u8 waitForXRefreshBetweenFrames;  /*!< Number of cycles between each frame changes */
	u8 animeFrom, /*!< Animation start at... */
	animeTo, /*!< Animation end at... */
	timesAnimated; /*!< Animation will loop X times */
	u16 currentFrame; /*!< Current frame */
	u16 nbTiles; /*!< Number of tiles */
	u16 tileWidth, /*!< Width of one tile */
	tileHeight; /*!< Height of one tile */
	bool flipX, /*!< Is the sprite flipped horizontally or not */
	flipY; /*!< Is the sprite flipped vertically or not */
} ML_Sprite;

/**
* \struct ML_Background
* \brief This is the structure for backgrounds.
*/
typedef struct {
	ML_Image *image;  /*!< Pointer to the image associated with */
	u16 width, /*!< Width */
	height; /*!< Height */
	s16 x,  /*!< X position */
	y; /*!< Y position */
	float scaleX, /*!< X scaling */
	scaleY; /*!< Y scaling */
	u8 rotated; /*!< Is rotation enabled */
	u8 alpha; /*!< Transparency (0-255) */
	float angle; /*!< Angle in degrees */
} ML_Background;

/**
* \struct ML_Rect
* \brief This is the structure for rectangle.
*/
typedef struct {
	s16 x,  /*!< X position */
	y; /*!< Y position */
	u16 width, /*!< Width */
	height; /*!< Height */
} ML_Rect;

// BMP structure
typedef struct
{
  u16 bfMagic;			/*** Always BM ***/
  u32 bfSize;			/*** Size of file ***/
  u32 bfReserved;		/*** Always 0 ***/
  u32 bfOffset;			/*** Offset to pixel data ***/
  u32 biImageHdrSize;		/*** Size of Image info header ***/
  u32 biWidth;			/*** Width of bitmap ***/
  u32 biHeight;			/*** Height of bitmap ***/
  u16 biPlanes;			/*** Number of planes ***/
  u16 biBitsPerPixel;		/*** Bits per pixel ***/
  u32 biCompression;		/*** Is this compressed? ***/
} __attribute__ ((__packed__)) WINBITMAP;

extern GXRModeObj *screenMode;
extern int _screenWidth, _screenHeight;
extern Mtx GXmodelView2D;

/**
* \file
* \brief This file contains video headers.
*/

/*****************************************************
******************       GX         ******************
******************************************************/

/**
* \fn bool ML_LoadSpriteFromBuffer(ML_Image *image, ML_Sprite *sprite, const u8 *filename, int x, int y)
* \brief This function loads a PNG image in memory from the buffer (see tutorial/wiki).
* @param image The image you're loading
* @param sprite The sprite structure you will use after
* @param filename The path to the PNG file. (eg. sprite_png)
* @param x X position
* @param y Y position
* @return 0 if it failed, 1 else.
*/
extern bool ML_LoadSpriteFromBuffer(ML_Image *image, ML_Sprite *sprite, const u8 *filename, int x, int y);

/**
* \fn bool ML_LoadSpriteFromFile(ML_Image *image, ML_Sprite *sprite, char *filename, int x, int y)
* \brief This function loads a PNG image in memory from a file.
* @param image The image you're loading
* @param sprite The sprite structure you will use after
* @param filename The path to the PNG file. (eg. "sprite.png")
* @param x X position
* @param y Y position
* @return 0 if it failed, 1 else.
*/
extern bool ML_LoadSpriteFromFile(ML_Image *image, ML_Sprite *sprite, char *filename, int x, int y);

/**
* \fn bool ML_LoadBackgroundFromBuffer(ML_Image *image, ML_Background *background, const u8 *filename, int x, int y)
* \brief This function loads a PNG image in memory from the buffer (see tutorial/wiki).
* @param image The image you're loading
* @param background The background structure you will use after
* @param filename The path to the PNG file. (eg. background_png)
* @param x X position
* @param y Y position
* @return 0 if it failed, 1 else.
*/
extern bool ML_LoadBackgroundFromBuffer(ML_Image *image, ML_Background *background, const u8 *filename, int x, int y);

/**
* \fn bool ML_LoadBackgroundFromFile(ML_Image *image, ML_Background *background, char *filename, int x, int y)
* \brief This function loads a PNG image in memory from a file.
* @param image The image you're loading
* @param background The background structure you will use after
* @param filename The path to the PNG file. (eg. "background.png")
* @param x X position
* @param y Y position
* @return 0 if it failed, 1 else.
*/
extern bool ML_LoadBackgroundFromFile(ML_Image *image, ML_Background *background, char *filename, int x, int y);

/**
* \fn void ML_DrawTexture(GXTexObj *texObj, u8 *data, int x, int y, u16 width, u16 height, float angle, float scaleX, float scaleY, u8 alpha)
* \brief This function shows the sprite which is already loaded. It can be faster when you have many things to do on the sprites in a time.
* @param texObj GX Texture (it's sprite.image->texObj)
* @param data Image data (it's sprite.image->data)
* @param x X position
* @param y Y position
* @param width Width
* @param height Height
* @param angle Angle in degrees ( -180 -> +180 )
* @param scaleX Horizontal scale
* @param scaleY Vertical scale 
* @param alpha Transparency ( 0 -> 255 )
*/
extern void ML_DrawTexture(GXTexObj *texObj, u8 *data, int x, int y, u16 width, u16 height, float angle, float scaleX, float scaleY, u8 alpha);

/**
* \fn void ML_DrawRect(int x, int y, u16 width, u16 height, u32 rgba, bool filled)
* \brief This function shows a rectangle with the color you want.
* @param x X position
* @param y Y position
* @param width Width
* @param height Height
* @param rgba RGBA Color (HTML Color) like 0xFF0016FF (0xRED+GREEN+BLUE+ALPHA)
* @param filled Should the rectangle be filled or not ?
*/
extern void ML_DrawRect(int x, int y, u16 width, u16 height, u32 rgba, bool filled);

/**
* \fn void ML_DrawCircle(int x, int y, int radius, u32 rgba, bool filled)
* \brief This function shows a rectangle with the color you want.
* @param x X position
* @param y Y position
* @param radius Radius
* @param rgba RGBA Color (HTML Color) like 0xFF0016FF (0xRED+GREEN+BLUE+ALPHA)
* @param filled Should the circle be filled or not ?
*/
extern void ML_DrawCircle(int x, int y, int radius, u32 rgba, bool filled);

/**
* \fn void ML_Brightness(u8 alpha)
* \brief This function changes the opacity of the entire screen.
* In fact, it draws a black rectangle which will be opacified.
* @param alpha Alpha of the screen.
*/
extern void ML_Brightness(u8 alpha);

/**
* \fn bool ML_FadeOut(void)
* \brief This function fades out.
* @return 1 if it's finished, 0 if not.
*/
extern bool ML_FadeOut(void);

/**
* \fn bool ML_FadeIn(void)
* \brief This function fades in (after a fade-out).
* @return 1 if it's finished, 0 if not.
*/
extern bool ML_FadeIn(void);

/**
* \fn void ML_EnableClipping(int x, int y, int width, int height)
* \brief This function disables the clipping.
* @param x X position
* @param y Y position
* @param width Width of the rectangle
* @param height Height of the rectangle
*/
extern void ML_EnableClipping(int x, int y, int width, int height);

/**
* \fn void ML_DisableClipping(void)
* \brief This function disables the clipping.
*/
extern void ML_DisableClipping(void);

/**
* \fn void ML_EnableTextureAntiAliasing(void)
* \brief This function enables the anti-aliasing on textures.
*/
extern void ML_EnableTextureAntiAliasing(void);

/**
* \fn void ML_DisableTextureAntiAliasing(void)
* \brief This function disables the anti-aliasing on textures.
*/
extern void ML_DisableTextureAntiAliasing(void);

/**
* \fn void ML_SetBackgroundColor(GXColor color)
* \brief This function clears the background with the color you want.
* @param color New background color
*/
extern void ML_SetBackgroundColor(GXColor color);

/**
* \fn void ML_SplashScreen(void)
* \brief This function shows the official Splash Screen made by Zeblackos. :)
*/
extern void ML_SplashScreen(void);

/**
* \fn bool ML_Screenshot(const char *filename)
* \brief This function makes a screenshot of the screen at the root of your SD Card.
* @param filename Name of the file which will be created
*/
extern bool ML_Screenshot(const char *filename);

void _drawImage(GXTexObj *texObj, u8 *data, int x, int y, u16 _width, u16 _height, float scaleX, float scaleY, float angle, GXColor color, bool tiled, u16 frame, u16 tileWidth, u16 tileHeight, bool flipX, bool flipY);
void FreeTypeGX_copyTextureToFramebuffer(GXTexObj *texObj, int16_t screenX, int16_t screenY, uint16_t texWidth, uint16_t texHeight, GXColor color, u8 alpha, float scaleX, float scaleY, float angle, bool flipX, bool flipY);
void FreeTypeGX_copyFeatureToFramebuffer(f32 featureWidth, f32 featureHeight, int16_t screenX, int16_t screenY, GXColor color, u8 alpha);

extern void ML_GX_Init(void); // Init GX system
extern void ML_GX_Refresh(void); // Refresh GX system

/*****************************************************
******************       FB         ******************
******************************************************/

/**
* \fn void ML_CleanVideoBG(void)
* \brief This function cleans the BG in black.
*/
extern void ML_CleanVideoBG(void);

/**
* \fn void ML_CleanVideoBGColor(int color)
* \brief This function cleans the BG with a color.
* @param color The color you want.
*/
extern void ML_CleanVideoBGColor(int color);


/*****************************************************
******************      OTHERS      ******************
******************************************************/


/**
* \fn void ML_Refresh(void)
* \brief This function refresh the MLlib (Get pads status, and refresh video)
*/
extern void ML_Refresh(void);

/**
* \fn void ML_RefreshConsoleMode(void)
* \brief CONSOLE MODE - This function refresh the MLlib (Get pads status, and refresh video)
*/
extern void ML_RefreshConsoleMode(void);

extern void ML_InitVideo(void); // Init video
extern void ML_VSync(void);  // Refresh video
extern void ML_GX_FreeMemory(void);

#ifdef __cplusplus
   }
#endif /* __cplusplus */

#endif

