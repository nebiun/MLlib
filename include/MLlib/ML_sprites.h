#ifndef DEF_ML_SPRITES_H
#define DEF_ML_SPRITES_H

/**
* \file
* \brief This file contains sprites headers.
*/

#ifdef __cplusplus
   extern "C" {
#endif /* __cplusplus */

extern void _initSprite(ML_Sprite *sprite);

/**
* \fn void ML_DrawSprite(ML_Sprite *sprite)
* \brief This function shows the sprite which is already loaded, of course.
* @param sprite Sprite
*/
extern void ML_DrawSprite(ML_Sprite *sprite);

/**
* \fn void ML_DrawSpriteXY(ML_Sprite *sprite, int x, int y)
* \brief This function shows the sprite which is already loaded. At X and Y positions.
* @param sprite Sprite
* @param x X position
* @param y Y position
*/
extern void ML_DrawSpriteXY(ML_Sprite *sprite, int x, int y);

/**
* \fn void ML_DrawSpriteFull(ML_Sprite *sprite, int x, int y, float angle, float scaleX, float scaleY, u8 alpha)
* \brief This function shows the sprite which is already loaded. \n
It can be faster when you have many things to do on the sprites in a time.
* @param sprite Sprite
* @param x X position
* @param y Y position
* @param angle Angle in degrees ( -180 -> +180 )
* @param scaleX Horizontal scale
* @param scaleY Vertical scale 
* @param alpha Transparency ( 0 -> 255 )
*/
extern void ML_DrawSpriteFull(ML_Sprite *sprite, int x, int y, float angle, float scaleX, float scaleY, u8 alpha);

/**
* \fn void ML_InitTile(ML_Sprite *sprite, u16 width, u16 height)
* \brief This function inits the tile system of the sprite.
* @param sprite Sprite
* @param width Width of the tile
* @param height Height of the tile
*/
extern void ML_InitTile(ML_Sprite *sprite, u16 width, u16 height);

/**
* \fn void ML_DrawTileColor(ML_Sprite *sprite, int x, int y, GXColor color, u16 frame);
* \brief This function draws a colored tile.
* @param sprite Sprite
* @param x X position
* @param y Y position
* @param color Tile color in RGBA
* @param frame Tile n°<frame>
*/
extern void ML_DrawTileColor(ML_Sprite *sprite, int x, int y, GXColor color, u16 frame);

/**
* \fn void ML_DrawTile(ML_Sprite *sprite, int x, int y, u16 frame)
* \brief This function draws a tile.
* @param sprite Sprite
* @param x X position
* @param y Y position
* @param frame Tile n°<frame>
*/
#define ML_DrawTile(sprite, x, y, frame)	ML_DrawTileColor(sprite, x, y, (GXColor){0xff,0xff,0xff,((ML_Sprite *)sprite)->alpha}, frame)

/**
* \fn void ML_DrawSpriteColorText(ML_Sprite *sprite, int x, int y, GXColor color, const char *text, ...)
* \brief This function draws some graphic text.
* @param sprite Sprite for extra-features like transparency, etc...
* @param x X position
* @param y Y position
* @param color Tile color in RGBA
* @param text Text which can have arguments
*/
extern void ML_DrawSpriteColorText(ML_Sprite *sprite, int x, int y, GXColor color, const char *text, ...);

/**
* \fn void ML_DrawSpriteText(ML_Sprite *sprite, int x, int y, const char *text, ...)
* \brief This function draws some graphic text.
* @param sprite Sprite for extra-features like transparency, etc...
* @param x X position
* @param y Y position
* @param text Text which can have arguments
*/
#define ML_DrawSpriteText(sprite, x, y, ...)		ML_DrawSpriteColorText(sprite, x, y, (GXColor){0xff,0xff,0xff,((ML_Sprite *)sprite)->alpha}, __VA_ARGS__)

/**
* \fn void ML_DrawSpriteColorTextLimit(ML_Sprite *sprite, int x, int y, GXColor color, u8 limit, char *text, ...)
* \brief This function draws some graphic text with arguments and a limit of characters.
* @param sprite Sprite for extra-features like transparency, etc...
* @param x X position
* @param y Y position
* @param color in RGBA
* @param limit Limit of characters
* @param text Text which can have arguments
*/
extern void ML_DrawSpriteColorTextLimit(ML_Sprite *sprite, int x, int y, GXColor color, u8 limit, char *text, ...);

/**
* \fn void ML_DrawSpriteTextLimit(ML_Sprite *sprite, int x, int y, char *text, u8 limit)
* \brief This function draws some graphic text with a limit of characters.
* @param sprite Sprite for extra-features like transparency, etc...
* @param x X position
* @param y Y position
* @param text Text
* @param limit Limit of characters
*/
#define ML_DrawSpriteTextLimit(sprite, x, y, text, limit)	ML_DrawSpriteColorTextLimit(sprite, x, y, (GXColor){0xff,0xff,0xff,((ML_Sprite *)sprite)->alpha}, limit, text)

/**
* \fn void ML_DrawSpriteColorTextBox(ML_Sprite *sprite, int x, int y, int x2, int y2, GXColor color, const char *text, ...)
* \brief This function draws some graphic text within a box.
* @param sprite Sprite for extra-features like transparency, etc...
* @param x X position of the left-upper corner
* @param y Y position of the left-bottom corner
* @param x2 X position of the right-upper corner
* @param y2 Y position of the right-bottom corner
* @param color in RGBA
* @param text Text
*/
extern void ML_DrawSpriteColorTextBox(ML_Sprite *sprite, int x, int y, int x2, int y2, GXColor color, const char *text, ...);

/**
* \fn void ML_DrawSpriteTextBox(ML_Sprite *sprite, int x, int y, int x2, int y2, const char *text, ...)
* \brief This function draws some graphic text within a box.
* @param sprite Sprite for extra-features like transparency, etc...
* @param x X position of the left-upper corner
* @param y Y position of the left-bottom corner
* @param x2 X position of the right-upper corner
* @param y2 Y position of the right-bottom corner
* @param text Text
*/
#define ML_DrawSpriteTextBox(sprite, x, y, x2, y2, ...)	ML_DrawSpriteColorTextBox(sprite, x, y, x2, y2, (GXColor){0xff,0xff,0xff,((ML_Sprite *)sprite)->alpha}, __VA_ARGS__)

/**
* \fn void ML_DrawSpriteColorSimpleText(ML_Sprite *sprite, int x, int y, GXColor color, const char *text)
* \brief This function draws some graphic text, but with no arguments and other funny thing : just faster !
* @param sprite Sprite for extra-features like transparency, etc...
* @param x X position
* @param y Y position
* @param color in RGBA
* @param text Text
*/
extern void ML_DrawSpriteColorSimpleText(ML_Sprite *sprite, int x, int y, GXColor color, const char *text);

/**
* \fn void ML_DrawSpriteSimpleText(ML_Sprite *sprite, int x, int y, const char *text)
* \brief This function draws some graphic text, but with no arguments and other funny thing : just faster !
* @param sprite Sprite for extra-features like transparency, etc...
* @param x X position
* @param y Y position
* @param text Text
*/
#define ML_DrawSpriteSimpleText(sprite, x, y, text)		ML_DrawSpriteColorSimpleText(sprite, x, y, (GXColor){0xff,0xff,0xff,((ML_Sprite *)sprite)->alpha}, text)

/**
* \fn void ML_DrawSpriteTextSetConverter(u16(*hook)(u16))
* \brief This function sets the address of the function that will be called to translate the character of the string \n
into the index of the sprite's Tile before displaying it.
* @param hook Function address
*/
extern void ML_DrawSpriteTextSetConverter(u16(*hook)(u16));

/**
* \fn void ML_CloneSprite(ML_Sprite *sprite1, ML_Sprite *sprite2)
* \brief This function clones two sprites.
* @param sprite1 The original sprite
* @param sprite2 The sprite which will be the same as sprite1
*/
extern void ML_CloneSprite(ML_Sprite *sprite1, ML_Sprite *sprite2);

/**
* \fn bool ML_IsSpriteVisible(ML_Sprite *sprite)
* \brief This function checks if the sprite is visible.
* @param sprite Sprite
* @return 1 if it's visible, 0 else.
*/
extern bool ML_IsSpriteVisible(ML_Sprite *sprite);

/**
* \fn void ML_AnimateSprite(ML_Sprite *sprite, bool enabled, u8 waitForXRefreshBetweenFrames)
* \brief This function animates the sprite which needs to be tiled (and initialized for that).
* @param sprite Sprite
* @param enabled Animation enabled (1) or disabled (0)
* @param waitForXRefreshBetweenFrames This is the last of time between each frames.
*/
extern void ML_AnimateSprite(ML_Sprite *sprite, bool enabled, u8 waitForXSecondsBetweenFrames);

/**
* \fn void ML_AnimateSpriteEx(ML_Sprite *sprite, bool enabled, u8 waitForXRefreshBetweenFrames, u8 from, u8 to)
* \brief This function animates the sprite which needs to be tiled (and initialized for that). \n
It will animate from "from" to "to" in loops.
* @param sprite Sprite
* @param enabled Animation enabled (1) or disabled (0)
* @param waitForXRefreshBetweenFrames This is the last of time between each frames.
* @param from From where the sprite will begin the animation
* @param to To where the sprite will finish the animations
*/
extern void ML_AnimateSpriteEx(ML_Sprite *sprite, bool enabled, u8 waitForXRefreshBetweenFrames, u8 from, u8 to);

/**
* \fn void ML_AnimateSpriteEx2(ML_Sprite *sprite, bool enabled, u8 waitForXRefreshBetweenFrames, u8 from, u8 to, u8 times)
* \brief This function animates the sprite which needs to be tiled (and initialized for that). \n
It will animate from "from" to "to" in "time" loops.
* @param sprite Sprite
* @param enabled Animation enabled (1) or disabled (0)
* @param waitForXRefreshBetweenFrames This is the last of time between each frames.
* @param from From where the sprite will begin the animation
* @param to To where the sprite will finish the animations
* @param times How many times it will be looped. (0 means infinite)
*/
extern void ML_AnimateSpriteEx2(ML_Sprite *sprite, bool enabled, u8 waitForXRefreshBetweenFrames, u8 from, u8 to, u8 times);

/**
* \fn void ML_MoveSpriteWiimotePad(ML_Sprite *sprite, u8 wpad)
* \brief This function moves the sprite with the D-Pad of the Wiimote.
* @param sprite Sprite
* @param wpad Which Wiimote
*/
extern void ML_MoveSpriteWiimotePad(ML_Sprite *sprite, u8 wpad);

/**
* \fn void ML_MoveSpriteWiimoteIR(ML_Sprite *sprite, u8 wpad)
* \brief This function moves the sprite with Wiimote IR.
* @param sprite Sprite
* @param wpad Which Wiimote
*/
extern void ML_MoveSpriteWiimoteIR(ML_Sprite *sprite, u8 wpad);

/**
* \fn bool ML_IsWiimoteInSprite(u8 wpad, const ML_Sprite *sprite)
* \brief This function checks if the Wiimote pointer is in the sprite.
* @param wpad Wiimote number
* @param sprite Sprite
* @return 1 if it's in the sprite, 0 else.
*/
extern bool ML_IsWiimoteInSprite(u8 wpad, const ML_Sprite *sprite);

/**
* \fn bool ML_IsWiimoteInSpriteEx(u8 wpad, const ML_Sprite *sprite)
* \brief Prefer not to use this because it's slower. \n
This function checks if the Wiimote pointer is in the sprite. \n
It's a pixel-detection. 
* \warning Make sure that your sprite is not rotated ! \n
Don't use with tiled sprites.
* @param wpad Wiimote number
* @param sprite Sprite
* @return 1 if it's in the sprite, 0 else.
*/
extern bool ML_IsWiimoteInSpriteEx(u8 wpad, const ML_Sprite *sprite);

/**
* \fn bool ML_IsCollision(const ML_Sprite *sprite, const ML_Sprite *sprite2)
* \brief This function checks if there is a collision between two sprites. \n
It's a box-detection.
* \warning Don't use it if your sprite is a cursor. (use ML_IsWiimoteInSprite(void) instead)
* @param sprite 1st Sprite
* @param sprite2 2nd Sprite
* @return 1 if there is collision, 0 else.
*/
extern bool ML_IsCollision(const ML_Sprite *sprite, const ML_Sprite *sprite2);

/**
* \fn bool ML_IsCollisionEx(const ML_Sprite *sprite, const ML_Sprite *sprite2)
* \brief Prefer not to use this because it's slower. \n
This function checks if there is a collision between two sprites. \n
It's a pixel-detection. 
* \warning Don't use it if your sprite is a cursor. (use ML_IsWiimoteInSprite(void) instead) \n
Also make sure that your sprite is not rotated ! \n
Don't use with tiled sprites.
* @param sprite 1st Sprite
* @param sprite2 2nd Sprite
* @return 1 if there is collision, 0 else.
*/
extern bool ML_IsCollisionEx(const ML_Sprite *sprite, const ML_Sprite *sprite2);

/**
* \fn bool ML_IsCollisionSpriteRect(const ML_Sprite *sprite, int x, int y, int width, int height)
* \brief Detects a collision between a sprite and a rectangle.
* @param sprite Sprite
* @param x X position of the rectangle
* @param y Y position of the rectangle
* @param width Width of the rectangle
* @param height Height of the rectangle
* @return 1 if there is collision, 0 else.
*/
extern bool ML_IsCollisionSpriteRect(const ML_Sprite *sprite, int x, int y, int width, int height);

/**
* \fn bool ML_IsCollisionSpriteCircle(const ML_Sprite *sprite, int centerX, int centerY, int radius)
* \brief Detects a collision between a sprite and a circle.
* @param sprite Sprite
* @param centerX X position of the circle
* @param centerY Y position of the circle
* @param radius Radius of the circle
* @return 1 if there is collision, 0 else.
*/
extern bool ML_IsCollisionSpriteCircle(const ML_Sprite *sprite, int centerX, int centerY, int radius);

/**
* \fn bool ML_IsCollisionRectRect(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
* \brief Detects a collision between two rectangles.
* @param x1 X position of the first rectangle
* @param y1 Y position of the first rectangle
* @param width1 Width of the first rectangle
* @param height1 Height of the first rectangle
* @param x2 X position of the second rectangle
* @param y2 Y position of the second rectangle
* @param width2 Width of the second rectangle
* @param height2 Height of the second rectangle
* @return 1 if there is collision, 0 else.
*/
extern bool ML_IsCollisionRectRect(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);

/**
* \fn bool ML_IsCollisionCircleCircle(int centerX1, int centerY1, int radius1, int centerX2, int centerY2, int radius2)
* \brief Detects a collision between two circles.
* @param centerX1 X position of the first circle
* @param centerY1 Y position of the first circle
* @param radius1 Radius of the first circle
* @param centerX2 X position of the second circle
* @param centerY2 Y position of the second circle
* @param radius2 Radius of the second circle
* @return 1 if there is collision, 0 else.
*/
extern bool ML_IsCollisionCircleCircle(int centerX1, int centerY1, int radius1, int centerX2, int centerY2, int radius2);

/**
* \fn bool ML_IsCollisionRectCircle(int x, int y, int width, int height, int centerX, int centerY, int radius)
* \brief Detects a collision between a rectangle and a circle.
* @param x X position of the rectangle
* @param y Y position of the rectangle
* @param width Width of the rectangle
* @param height Height of the rectangle
* @param centerX X position of the circle
* @param centerY Y position of the circle
* @param radius Radius of the circle
* @return 1 if there is collision, 0 else.
*/
extern bool ML_IsCollisionRectCircle(int x, int y, int width, int height, int centerX, int centerY, int radius);

/**
* \fn void ML_Cursor(ML_Sprite *sprite, u8 wpad)
* \brief This function draws the sprite as a cursor. \n
Wiimote pointer will be in the center of the sprite. \n
X and Y of the cursor will be where the wiimote point to.
* @param sprite Sprite
* @param wpad Which Wiimote
*/
extern void ML_Cursor(ML_Sprite *sprite, u8 wpad);

/**
* \fn void ML_RotateSprite(ML_Sprite *sprite, float angle, u8 autoRotate)
* \brief This function rotates the sprite.
* @param sprite Sprite
* @param angle Angle of rotation (degrees)
* @param autoRotate If TRUE, the sprite will rotate of <angle> degrees each frame. \n
If it's FALSE, the sprite will rotate to the angle indicated.
*/
extern void ML_RotateSprite(ML_Sprite *sprite, float angle, u8 autoRotate);

/**
* \fn void ML_SetSpriteXY(ML_Sprite *sprite, int x, int y)
* \brief This function changes the X and Y positions of the sprite.
* @param sprite Sprite
* @param x New X position
* @param y New Y position
*/
extern void ML_SetSpriteXY(ML_Sprite *sprite, int x, int y);

/**
* \fn void ML_SetSpriteX(ML_Sprite *sprite, int x)
* \brief This function changes the X position of the sprite.
* @param sprite Sprite
* @param x New X position
*/
extern void ML_SetSpriteX(ML_Sprite *sprite, int x);

/**
* \fn void ML_SetSpriteY(ML_Sprite *sprite, int y)
* \brief This function changes the Y position of the sprite.
* @param sprite Sprite
* @param y New Y position
*/
extern void ML_SetSpriteY(ML_Sprite *sprite, int y);

/**
* \fn void ML_SetSpriteScale(ML_Sprite *sprite, float scaleX, float scaleY)
* \brief This function changes the Scale X and Scale Y of the sprite.
* @param sprite Sprite
* @param scaleX New scale for the width of the sprite
* @param scaleY New scale for the height of the sprite
*/
extern void ML_SetSpriteScale(ML_Sprite *sprite, float scaleX, float scaleY);

/**
* \fn void ML_SetSpriteSize(ML_Sprite *sprite, u16 width, u16 height)
* \brief This function changes the size of your sprite.
* @param sprite Sprite
* @param width New width
* @param height New height
*/
extern void ML_SetSpriteSize(ML_Sprite *sprite, u16 width, u16 height);

/**
* \fn void ML_SetSpriteVelocity(ML_Sprite *sprite, int dx, int dy)
* \brief This function sets the velocity members of the sprite.
* @param sprite Sprite
* @param dx New horizontal velocity
* @param dy New vertical velocity
*/
extern void ML_SetSpriteVelocity(ML_Sprite *sprite, int dx, int dy);

/**
* \fn void ML_SetSpriteAlpha(ML_Sprite *sprite, u8 alpha)
* \brief This function sets the transparency of the sprite.
* @param sprite Sprite
* @param alpha Transparency ( 0 -> 255 )
*/
extern void ML_SetSpriteAlpha(ML_Sprite *sprite, u8 alpha);

/**
* \fn void ML_FlipSpriteX(ML_Sprite *sprite, bool flipX)
* \brief This function flips the sprite horizontally if flipX is set to 1.
* @param sprite Sprite
* @param flipX Flipping enabled (1) or disabled (0)
*/
extern void ML_FlipSpriteX(ML_Sprite *sprite, bool flipX);

/**
* \fn void ML_FlipSpriteY(ML_Sprite *sprite, bool flipY)
* \brief This function flips the sprite vertically if flipY is set to 1.
* @param sprite Sprite
* @param flipY Flipping enabled (1) or disabled (0)
*/
extern void ML_FlipSpriteY(ML_Sprite *sprite, bool flipY);

/**
* \fn void ML_FlipSpriteXY(ML_Sprite *sprite, bool flipX, bool flipY)
* \brief This function flips the sprite.
* @param sprite Sprite
* @param flipX Horizontal flipping enabled (1) or disabled (0)
* @param flipY Vertical flipping enabled (1) or disabled (0)
*/
extern void ML_FlipSpriteXY(ML_Sprite *sprite, bool flipX, bool flipY);

#ifdef __cplusplus
   }
#endif /* __cplusplus */

#endif

