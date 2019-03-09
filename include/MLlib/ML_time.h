#ifndef DEF_ML_TIME_H
#define DEF_ML_TIME_H

/**
* \file
* \brief This file contains time and random headers.
*/

#ifdef __cplusplus
   extern "C" {
#endif /* __cplusplus */

/**
* \fn time_t ML_GetTime(void)
* \brief This function gets RTC time.
* @return Return time in a time_t struct.
*/
extern time_t ML_GetTime(void);

/**
* \fn char* ML_GetTimeChar(void)
* \brief This function gets RTC time in char.
* @return Return time in char.
*/
extern char* ML_GetTimeChar(void);

/**
* \fn int ML_InitRand(void)
* \brief This function initializes the random system. Call this once.
*/
extern void ML_InitRand(void);

/**
* \fn int ML_Rand(int min, int max)
* \brief This function returns a random number between "min" and "max". Call this function after ML_InitRand(void).
* @param min Minimum number
* @param max Maximum number
* @return Return the random number.
*/
extern int ML_Rand(int min, int max);

/**
* \fn int ML_GetFPS(void)
* \brief This function returns the FPS.
* @return Return the FPS.
*/
extern int ML_GetFPS(void);

/**
* \fn void ML_Wait(u32 ms)
* \brief This function waits.
* @param ms Time to wait in milliseconds
*/
extern void ML_Wait(u32 ms);

/**
* \fn u32 ML_ElapsedTime(void)
* \brief This function returns the time elapsed in milliseconds.
* @return Time elapsed in ms.
*/
extern u32 ML_ElapsedTime(void);

#ifdef __cplusplus
   }
#endif /* __cplusplus */

#endif
