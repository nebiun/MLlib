#include <MLlib.h>
#include "MLlib_SplashScreen_png.h"

/*                 CREDITS
 *   These are the functions inspired or in some cases modified from the GRRLib by NoNameNo, Crayon and RedShade. (V 4.0.0) :
 *		- ML_drawImage
 *		- ML_ScreenShot
 *		- ML_GX_Init
 *		- ML_GX_Refresh
 *		- ML_GX_FreeMemory
 */

// FB
static void *xfb[2] = { NULL, NULL };
static u32 whichfb = 0;

// GX
static void *gp_fifo = NULL;
Mtx GXmodelView2D;

// Others
static u8 _alphaFade;
static bool _fadeMode = 0;
#define FADE_OUT	0
#define FADE_IN		1
GXRModeObj *screenMode;
int _screenWidth, _screenHeight;

/**
* \file
* \brief This file contains video functions.
*/

static bool _loadImage(ML_Image *image, ML_Sprite *sprite, ML_Background *background, char *filename, const u8 *buffer, int x, int y, bool fat)
{
	_initImage(image);
	
	if(sprite)
		_initSprite(sprite);
	else if(background) _initBackground(background);
	 
	bool ok = 0;
	
	if(fat)
	{
		if(!fatInitDefault()) return 0;
		
		ok = read_png_gx_file(filename, image);
	}
	else ok = read_png_gx_file_buffer(buffer, image);
	
	if(!ok) return 0;
	
	DCFlushRange(image->data, image->width * image->height * 4);
	
	GX_InitTexObj(&image->texObj, image->data, image->width, image->height, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);	
	if(!getAA())
		GX_InitTexObjLOD(&image->texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
	
	if(sprite)
	{
		sprite->image = image;
		sprite->width = image->width;
		sprite->height = image->height;
		sprite->tileWidth = image->width;
		sprite->tileHeight = image->height;
		sprite->x = x;
		sprite->y = y;
	}
	else if(background)
	{
		background->image = image;
		background->width = image->width;
		background->height = image->height;
		background->x = x;
		background->y = y;
	}
	
	return 1;
}

/** ****************************************************
************************ GX ****************************
**************************************************** **/

bool ML_LoadSpriteFromBuffer(ML_Image *image, ML_Sprite *sprite, const u8 *filename, int x, int y)
{	
	return _loadImage(image, sprite, NULL, NULL, filename, x, y, 0);
}

bool ML_LoadSpriteFromFile(ML_Image *image, ML_Sprite *sprite, char *filename, int x, int y)
{
	return _loadImage(image, sprite, NULL, filename, NULL, x, y, 1);
}

bool ML_LoadBackgroundFromBuffer(ML_Image *image, ML_Background *background, const u8 *filename, int x, int y)
{	
	return _loadImage(image, NULL, background, NULL, filename, x, y, 0);
}

bool ML_LoadBackgroundFromFile(ML_Image *image, ML_Background *background, char *filename, int x, int y)
{
	return _loadImage(image, NULL, background, filename, NULL, x, y, 1);
}

void ML_DrawTexture(GXTexObj *texObj, u8 *data,  int x, int y, u16 width, u16 height, float angle, float scaleX, float scaleY, u8 alpha)
{
	GXColor color = (GXColor){ 0xff, 0xff, 0xff, alpha };
	
	_drawImage(texObj, data, x, y, width, height, scaleX, scaleY, angle, color, 0, 0, 0, 0, 0, 0);
}

void ML_DrawRect(int x, int y, u16 width, u16 height, u32 rgba, bool filled)
{
	int x2 = x + width;
    int y2 = y + height;
    
    if(filled)
    {
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
			GX_Position3f32(x, y, 0.0f);
			GX_Color1u32(rgba);
			GX_Position3f32(x2, y, 0.0f);
			GX_Color1u32(rgba);
			GX_Position3f32(x2, y2, 0.0f);
			GX_Color1u32(rgba);
			GX_Position3f32(x, y2, 0.0f);
			GX_Color1u32(rgba);
		GX_End();
	}
	else
	{
		GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 5);
			GX_Position3f32(x, y, 0.0f);
			GX_Color1u32(rgba);
			GX_Position3f32(x2, y, 0.0f);
			GX_Color1u32(rgba);
			GX_Position3f32(x2, y2, 0.0f);
			GX_Color1u32(rgba);
			GX_Position3f32(x, y2, 0.0f);
			GX_Color1u32(rgba);
			GX_Position3f32(x, y, 0.0f);
			GX_Color1u32(rgba);
		GX_End();
    }
//	GX_DrawDone();
}

void ML_DrawCircle(int x, int y, int radius, u32 rgba, bool filled)
{
	int i;
    u32 a;
    f32 ra, G_DTOR = M_DTOR * 10, x1[36], y1[36];

    for(a = 0; a < 36; a++)
    {
        ra = a * G_DTOR;

        x1[a] = cos(ra) * radius + x;
        y1[a] = sin(ra) * radius + y;
    }
	
	if(filled) GX_Begin(GX_TRIANGLEFAN, GX_VTXFMT0, 36);
	else GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 36);
	for(i = 0; i < 36; i++) 
	{
		GX_Position3f32(x1[i], y1[i], 0.0f);
		GX_Color1u32(rgba);
	}
	GX_End();
//	GX_DrawDone();
}

void ML_Brightness(u8 alpha)
{ 
    guVector v[] = {{0,0,0.0f}, {screenMode->fbWidth,0,0.0f}, {screenMode->fbWidth,screenMode->xfbHeight,0.0f}, {0,screenMode->xfbHeight,0.0f}, {0,0,0.0f}};    
    int i;

    GX_Begin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
    for(i = 0; i < 4; i++) 
    {
        GX_Position3f32(v[i].x, v[i].y,  v[i].z);
        GX_Color4u8(0x00, 0x00, 0x00, alpha);
    }
    GX_End();
//	GX_DrawDone();
}

bool ML_FadeIn(void)
{
	if(_fadeMode != FADE_IN)
	{
		_fadeMode = FADE_IN;
		_alphaFade = 255;
	}
	
	if(_alphaFade < 5) _alphaFade--;
	else if(_alphaFade > 240) _alphaFade -= 5;
	else if(_alphaFade <= 240 && _alphaFade > 7) _alphaFade-=4;
			
	ML_Brightness(_alphaFade);
	
	if(_alphaFade == 0) return 1;
	else return 0;
}

bool ML_FadeOut(void)
{
	if(_fadeMode != FADE_OUT)
	{
		_fadeMode = FADE_OUT;
		_alphaFade = 0;
	}
	
	if(_alphaFade >= 250) _alphaFade++;
 	else if(_alphaFade < 240) _alphaFade += 4;
	else if(_alphaFade >= 240 && _alphaFade < 249) _alphaFade+=5;
			
	ML_Brightness(_alphaFade);
	
	if(_alphaFade == 255) return 1;
	else return 0;
}

void ML_EnableClipping(int x, int y, int width, int height)
{
	GX_SetClipMode(GX_CLIP_ENABLE);
    GX_SetScissor(x, y, width, height);
}

void ML_DisableClipping(void)
{
	GX_SetClipMode(GX_CLIP_DISABLE);
	GX_SetScissor(0, 0, screenMode->fbWidth, screenMode->efbHeight);
}

void ML_EnableTextureAntiAliasing(void)
{
	_aa_enabled = true;
}

void ML_DisableTextureAntiAliasing(void)
{
	_aa_enabled = false;
}

void ML_SetBackgroundColor(GXColor color)
{
	GX_SetCopyClear(color, 0x00ffffff);	
}

void ML_SplashScreen(void)
{
	int i = 0;
	bool ok = 0, ok2 = 0, fadeOk = 0, fadeOk2 = 0;
	
	ML_Image image;
	_initImage(&image);
	ok = read_png_gx_file_buffer(MLlib_SplashScreen_png, &image);
	
	if(!ok)
		return;
	
	DCFlushRange(image.data, image.width * image.height * 4);
	
	GX_InitTexObj(&image.texObj, image.data, image.width, image.height, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
	if(!getAA())
		GX_InitTexObjLOD(&image.texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
	
	while(ok)
	{
		if(Wiimote[0].Held.A) { ok2 = 1; }
		
		_drawImage(&image.texObj, image.data, 0, 0, image.width, image.height, 1, 1, 0, (GXColor){255, 255, 255, 255}, 0, 0, 0, 0, 0, 0);
		
		i++;
		if(i >= 500) ok2 = 1;
		
		if(!fadeOk && !fadeOk2)
		{
			if(ML_FadeIn())
				fadeOk = 1;
		}
		
		if(ok2 && !fadeOk2 && fadeOk)
		{
			if(ML_FadeOut())
			{
				fadeOk2 = 1;
				ok = 0;
			}
		}
	
		ML_Refresh();
	}
	
	ML_Refresh();
	VIDEO_WaitVSync();
	ML_DeleteImage(&image);
}

bool ML_Screenshot(const char *filename)
{
	if(fatInitDefault()) 
	{
		png_uint_32 rowbytes;
		unsigned int x, y, buffWidth;
		unsigned int width = screenMode->fbWidth;
		unsigned int height = screenMode->efbHeight;
		void *buffer = xfb[whichfb];
		FILE *fp;		

		// Check if the user has selected a file to write the image
		if (!(fp = fopen(filename, "wb")))
			return 0;
		
		// Allocation of libpng structs
		png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
		{
			fclose (fp);
			return 0;
		}

		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
		{
			png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
			fclose(fp);
			return 0;
		}

		// Default data writer uses function fwrite, so it needs to use our FILE*
		png_init_io(png_ptr, fp);

		// Setup output file properties
		png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, 
				PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		// Allocate memory to store the image in RGB format
		rowbytes = width * 3;
		if (rowbytes % 4)
			rowbytes = ((rowbytes / 4) + 1) * 4; // Add extra padding so each row starts in a 4 byte boundary

		png_bytep img_data = malloc(rowbytes * height);
		if(!img_data)
		{
			png_destroy_write_struct (&png_ptr, (png_infopp)NULL);
			fclose (fp);
			return 0;
		}

		png_bytep *row_pointers = malloc (sizeof (png_bytep) * height);
		if (!row_pointers)
		{
			png_destroy_write_struct (&png_ptr, (png_infopp)NULL);
			fclose (fp);
			return 0;
		}

		// Encode YCbYCr image into RGB8 format
		buffWidth = width / 2;
		for (y = 0; y < height; y++)
		{
			row_pointers[y] = img_data + (y * rowbytes);

			for (x = 0; x < (width / 2); x++)
				_PNGU_YCbYCr_TO_RGB8(((unsigned int *)buffer)[y*buffWidth+x], 
					((unsigned char *) row_pointers[y]+x*6), ((unsigned char *) row_pointers[y]+x*6+1),
					((unsigned char *) row_pointers[y]+x*6+2), ((unsigned char *) row_pointers[y]+x*6+3),
					((unsigned char *) row_pointers[y]+x*6+4), ((unsigned char *) row_pointers[y]+x*6+5) );
		}

		// Tell libpng where is our image data
		png_set_rows(png_ptr, info_ptr, row_pointers);

		// Write file header and image data
		png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

		// Tell libpng we have no more data to write
		png_write_end(png_ptr, (png_infop) NULL);

		// Free resources
		free (img_data);
		free (row_pointers);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose (fp);

		return 1;
	} 
	
	return 0;
}

//---------------------------------------------
void _drawImage(GXTexObj *texObj, u8 *data, int x, int y, u16 _width, u16 _height, float scaleX, float scaleY, float angle, GXColor color, bool tiled, u16 frame, u16 tileWidth, u16 tileHeight, bool flipX, bool flipY)
{
	Mtx44 m, m1, m2, mv;
	u16 width, height;
		
	if(!tiled)
	{
		GX_InitTexObj(texObj, data, _width, _height, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);	
			if(!getAA())
		GX_InitTexObjLOD(texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
		
		if(getAA())
			GX_SetCopyFilter(screenMode->aa, screenMode->sample_pattern, GX_TRUE, screenMode->vfilter);
		else
			GX_SetCopyFilter(GX_FALSE, screenMode->sample_pattern, GX_FALSE, screenMode->vfilter);
		
		GX_LoadTexObj(texObj, GX_TEXMAP0);

		GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

		//width = (_width*scaleX)*0.5;
		//height = (_height*scaleY)*0.5;
		width = _width>>1;
		height = _height>>1;
		
		guMtxIdentity (m1);
		guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0);
		guVector axis = (guVector) {0, 0, 1};
		guMtxRotAxisDeg (m2, &axis, angle);
		guMtxConcat(m2, m1, m);

		guMtxTransApply(m, m, x+width, y+height, 0);
		guMtxConcat (GXmodelView2D, m, mv);
		GX_LoadPosMtxImm (mv, GX_PNMTX0);
		
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
			GX_Position3f32(-width*scaleX, -height*scaleY, 0);
			GX_Color4u8(color.r, color.g, color.b, color.a);
			GX_TexCoord2f32(flipX, flipY);

			GX_Position3f32(width*scaleX, -height*scaleY, 0);
			GX_Color4u8(color.r, color.g, color.b, color.a);
			GX_TexCoord2f32(!flipX, flipY);

			GX_Position3f32(width*scaleX, height*scaleY, 0);
			GX_Color4u8(color.r, color.g, color.b, color.a);
			GX_TexCoord2f32(!flipX, !flipY);

			GX_Position3f32(-width*scaleX, height*scaleY, 0);
			GX_Color4u8(color.r, color.g, color.b, color.a);
			GX_TexCoord2f32(flipX, !flipY);
		GX_End();
	}
	else
	{	
		u16 nbTileW = _width/tileWidth;
		u16 nbTileH = _height/tileHeight;
	
		// Frame Correction by spiffen
		f32 FRAME_CORR = 0.001f;
		f32 s1 = (((frame%nbTileW))/(f32)nbTileW)+(FRAME_CORR/_width);
		f32 s2 = (((frame%nbTileW)+1)/(f32)nbTileW)-(FRAME_CORR/_width);
		f32 t1 = (((int)(frame/nbTileW))/(f32)nbTileH)+(FRAME_CORR/_height);
		f32 t2 = (((int)(frame/nbTileW)+1)/(f32)nbTileH)-(FRAME_CORR/_height);
		
		f32 tmp = 0;
		
		if(flipX)
		{
			tmp = s1;
			s1 = s2;
			s2 = tmp;
		}
		if(flipY)
		{
			tmp = t1;
			t1 = t2;
			t2 = tmp;
		}
		
		GX_InitTexObj(texObj, data, _width, _height, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);	
			if(!getAA())
		GX_InitTexObjLOD(texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
		
		if(getAA())
			GX_SetCopyFilter(screenMode->aa, screenMode->sample_pattern, GX_TRUE, screenMode->vfilter);
		else
			GX_SetCopyFilter(GX_FALSE, screenMode->sample_pattern, GX_FALSE, screenMode->vfilter);

		GX_LoadTexObj(texObj, GX_TEXMAP0);
	
		GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	
		width = tileWidth>>1;
		height = tileHeight>>1;
		
		guMtxIdentity (m1);
		guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0);
		guVector axis = (guVector) {0, 0, 1};
		guMtxRotAxisDeg (m2, &axis, angle);
		guMtxConcat(m2, m1, m);

		guMtxTransApply(m, m, x+width*scaleX, y+height*scaleY, 0);
		guMtxConcat (GXmodelView2D, m, mv);
		GX_LoadPosMtxImm (mv, GX_PNMTX0);
		
	
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
			GX_Position3f32(-width, -height, 0);
			GX_Color4u8(color.r, color.g, color.b, color.a);
			GX_TexCoord2f32(s1, t1);

			GX_Position3f32(width, -height, 0);
			GX_Color4u8(color.r, color.g, color.b, color.a);
			GX_TexCoord2f32(s2, t1);

			GX_Position3f32(width, height, 0);
			GX_Color4u8(color.r, color.g, color.b, color.a);
			GX_TexCoord2f32(s2, t2);

			GX_Position3f32(-width, height, 0);
			GX_Color4u8(color.r, color.g, color.b, color.a);
			GX_TexCoord2f32(s1, t2);
		GX_End();
	}
//	GX_DrawDone();
	GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);

	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
}

// not the same as the real FreeTypeGX::copyTextureToFramebuffer at all (just like my _drawImage with colors)
void FreeTypeGX_copyTextureToFramebuffer(GXTexObj *texObj, int16_t screenX, int16_t screenY, uint16_t texWidth, uint16_t texHeight, GXColor color, u8 alpha, float scaleX, float scaleY, float angle, bool flipX, bool flipY)
{
	Mtx44 m, m1, m2, mv;
	u16 width, height;
	
	if(getAA())
		GX_SetCopyFilter(screenMode->aa, screenMode->sample_pattern, GX_TRUE, screenMode->vfilter);
	else
		GX_SetCopyFilter(GX_FALSE, screenMode->sample_pattern, GX_FALSE, screenMode->vfilter);
		
	GX_LoadTexObj(texObj, GX_TEXMAP0);

	GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	
	width = texWidth>>1;
	height = texHeight>>1;
	
	guMtxIdentity (m1);
	guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0);
	guVector axis = (guVector) {0, 0, 1};
	guMtxRotAxisDeg (m2, &axis, angle);
	guMtxConcat(m2, m1, m);

	guMtxTransApply(m, m, screenX+width, screenY+height, 0);
	guMtxConcat (GXmodelView2D, m, mv);
	GX_LoadPosMtxImm (mv, GX_PNMTX0);
	
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-width*scaleX, -height*scaleY, 0);
		GX_Color4u8(color.r, color.g, color.b, alpha);
		GX_TexCoord2f32(flipX, flipY);

		GX_Position3f32(width*scaleX, -height*scaleY, 0);
		GX_Color4u8(color.r, color.g, color.b, alpha);
		GX_TexCoord2f32(!flipX, flipY);

		GX_Position3f32(width*scaleX, height*scaleY, 0);
		GX_Color4u8(color.r, color.g, color.b, alpha);
		GX_TexCoord2f32(!flipX, !flipY);

		GX_Position3f32(-width*scaleX, height*scaleY, 0);
		GX_Color4u8(color.r, color.g, color.b, alpha);
		GX_TexCoord2f32(flipX, !flipY);
	GX_End();
//	GX_DrawDone();
	
	GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);

	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
}

// a very modified FreeTypeGX::copyFeatureToFramebuffer at all
void FreeTypeGX_copyFeatureToFramebuffer(f32 featureWidth, f32 featureHeight, int16_t screenX, int16_t screenY, GXColor color, u8 alpha)
{
	Mtx44 m, m1, m2, mv;
	u16 width, height;
	
	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
	
	width = featureWidth*0.5;
	height = featureHeight*0.5;
	
	guMtxIdentity (m1);
	guMtxScaleApply(m1, m1, 1, 1, 1.0);
	guVector axis = (guVector) {0, 0, 1};
	guMtxRotAxisDeg (m2, &axis, 0);
	guMtxConcat(m2, m1, m);

	guMtxTransApply(m, m, screenX+width, screenY+height, 0);
	guMtxConcat (GXmodelView2D, m, mv);
	GX_LoadPosMtxImm (mv, GX_PNMTX0);

	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
			GX_Position3f32(-width, -height, 0.0f);
			GX_Color4u8(color.r, color.g, color.b, alpha);

			GX_Position3f32(width, -height, 0.0f);
			GX_Color4u8(color.r, color.g, color.b, alpha);

			GX_Position3f32(width, height, 0.0f);
			GX_Color4u8(color.r, color.g, color.b, alpha);

			GX_Position3f32(-width, height, 0.0f);
			GX_Color4u8(color.r, color.g, color.b, alpha);
	GX_End();
//	GX_DrawDone();
	
	GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);

	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
}


void ML_GX_Init(void)
{
    Mtx44 perspective; 
	f32 yscale;
	u32 xfbHeight;

	// setup the fifo and then init the flipper
	gp_fifo = (u8 *) memalign(32,DEFAULT_FIFO_SIZE);
	if(gp_fifo == NULL)
        return;
	memset(gp_fifo,0,DEFAULT_FIFO_SIZE);
	GX_Init(gp_fifo,DEFAULT_FIFO_SIZE);
	
	// clears the bg to color and clears the z buffer
	GX_SetCopyClear((GXColor){ 0, 0, 0, 0xff }, GX_MAX_Z24);

	// other gx setup
	yscale = GX_GetYScaleFactor(screenMode->efbHeight,screenMode->xfbHeight);
	xfbHeight = GX_SetDispCopyYScale(yscale);
	GX_SetDispCopySrc(0, 0, screenMode->fbWidth, screenMode->efbHeight);
	GX_SetDispCopyDst(screenMode->fbWidth, xfbHeight);
	GX_SetCopyFilter(screenMode->aa, screenMode->sample_pattern, GX_TRUE, screenMode->vfilter);
	GX_SetFieldMode(screenMode->field_rendering,((screenMode->viHeight==2*screenMode->xfbHeight)?GX_ENABLE:GX_DISABLE));

	if (screenMode->aa)
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	else
		GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
		
	GX_SetDispCopyGamma(GX_GM_1_0);
	
	// setup the vertex descriptor
    // tells the flipper to expect direct data
    
	// Setup the vertex descriptor
	GX_ClearVtxDesc();      // clear all the vertex descriptors
	GX_InvVtxCache();       // Invalidate the vertex cache
	GX_InvalidateTexAll();  // Invalidate all textures

    // Tells the flipper to expect direct data
	GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS,  GX_POS_XYZ, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST,  GX_F32, 0);
	// Colour 0 is 8bit RGBA format
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);

	GX_SetNumChans(1);    // colour is the same as vertex colour
	GX_SetNumTexGens(1);  // One texture exists
    GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

    guMtxIdentity(GXmodelView2D);
    guMtxTransApply(GXmodelView2D, GXmodelView2D, 0.0f, 0.0f, -100.0f);
    GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);
	
 /* 
	if(CONF_GetAspectRatio() == CONF_ASPECT_16_9) 
	{
		_screenWidth = 746;
		_screenHeight = 480;		
	}
	else
	{	
		_screenWidth = 640;
		_screenHeight = 480;
	}
*/
	guOrtho(perspective,0, _screenHeight, 0, _screenWidth, 0, 1000.0F);
    GX_LoadProjectionMtx(perspective, GX_ORTHOGRAPHIC);

    GX_SetViewport(0, 0, _screenWidth, _screenHeight, 0, 1);
    GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GX_SetAlphaUpdate(GX_TRUE);
    GX_SetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GX_SetColorUpdate(GX_TRUE);
    GX_SetCullMode(GX_CULL_NONE);
	GX_SetClipMode( GX_CLIP_ENABLE );
    GX_SetScissor(0, 0, _screenWidth, _screenHeight);

	VIDEO_SetBlack(false);
}

//---------------------------------------------

void ML_GX_Refresh(void)
{
	GX_DrawDone();
	
	GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	GX_SetColorUpdate(GX_TRUE);
	GX_CopyDisp(xfb[whichfb],GX_TRUE);
}


/** ****************************************************
************************ FB ****************************
**************************************************** **/


void ML_InitVideo(void)
{
	VIDEO_Init();
	VIDEO_SetBlack(TRUE);
	screenMode = VIDEO_GetPreferredMode(NULL);

	// Video Mode Correction
	switch (screenMode->viTVMode) {
		case VI_DEBUG_PAL:  // PAL 50hz 576i
			//screenMode = &TVPal574IntDfScale;
			screenMode = &TVPal528IntDf; // BC ...this is still wrong, but "less bad" for now
			break;
	}
	
	// 16:9 and 4:3 Screen Adjustment
	if (CONF_GetAspectRatio() == CONF_ASPECT_16_9) {
		screenMode->viWidth = 678;
		screenMode->viXOrigin = (VI_MAX_WIDTH_NTSC - 678)/2;  // This probably needs to consider PAL
	} else {    // 4:3
		screenMode->viWidth = 672;
		screenMode->viXOrigin = (VI_MAX_WIDTH_NTSC - 672)/2;
	}
	
	VIDEO_Configure(screenMode);
	
	_screenWidth = screenMode->fbWidth;
	_screenHeight = screenMode->xfbHeight;

	xfb[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(screenMode));
	xfb[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(screenMode));	
	
	console_init(xfb[0], 20, 64, screenMode->fbWidth, screenMode->xfbHeight, screenMode->fbWidth*VI_DISPLAY_PIX_SZ);

	VIDEO_SetNextFramebuffer(xfb[0]);
	VIDEO_ClearFrameBuffer(screenMode, xfb[0], COLOR_BLACK);
	VIDEO_ClearFrameBuffer(screenMode, xfb[1], COLOR_BLACK);
	VIDEO_Flush();

	VIDEO_WaitVSync();
	if(screenMode->viTVMode & VI_NON_INTERLACE)
		VIDEO_WaitVSync();
	else
		while(VIDEO_GetNextField())
			VIDEO_WaitVSync();
}

//---------------------------------------------

void ML_CleanVideoBG(void)
{
	VIDEO_ClearFrameBuffer(screenMode, xfb[0], COLOR_BLACK);
	VIDEO_ClearFrameBuffer(screenMode, xfb[1], COLOR_BLACK);
}

//---------------------------------------------

void ML_CleanVideoBGColor(int color)
{
	VIDEO_ClearFrameBuffer(screenMode, xfb[0], color);
	VIDEO_ClearFrameBuffer(screenMode, xfb[1], color);
}

//---------------------------------------------

void ML_VSync(void)
{
	VIDEO_SetNextFramebuffer(xfb[whichfb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if (screenMode->viTVMode &VI_NON_INTERLACE)
		VIDEO_WaitVSync();
}

//---------------------------------------------

void ML_RefreshConsoleMode(void)
{
	ML_GetPads();
	ML_VSync();
	
	whichfb ^= 1;	
	ML_CallbackForPowerAndReset(0);
}

//---------------------------------------------

void ML_Refresh(void)
{
	ML_GX_Refresh();
	ML_VSync();
	ML_GetPads();

	whichfb ^= 1;
	ML_CallbackForPowerAndReset(1);
}

void ML_GX_FreeMemory(void)
{
	if(xfb[0] != NULL)  { free(MEM_K1_TO_K0(xfb[0])); xfb[0] = NULL; }
	if(xfb[1] != NULL)  { free(MEM_K1_TO_K0(xfb[1])); xfb[1] = NULL; }
	if(gp_fifo != NULL) { free(gp_fifo); gp_fifo = NULL; }
}

