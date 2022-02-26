#ifndef DEF_ML_GLOBALS_H
#define DEF_ML_GLOBALS_H

#ifdef __cplusplus
   extern "C" {
#endif /* __cplusplus */

extern bool _asnd_enabled; // Sound enabled
extern bool bPowerOff;	// Poweroff flag.
extern bool bReset;	// Reset flag.
extern bool _ttf_enabled; // Font system enabled
extern bool _aa_enabled; // Anti-aliasing for textures enabled
extern u32 _startTime; // time elapsed since Wii started at the beginning the the app

extern void setAsnd(bool value);
extern bool getAsnd(void);
extern void setAesnd(bool value);
extern bool getAesnd(void);
extern void setPowerOff(bool value);
extern void setReset(bool value);
extern void setTTF(bool value);
extern bool getTTF(void);
extern void setAA(bool value);
extern bool getAA(void);
extern void setStartTime(u32 value);
extern u32 getStartTime(void);

#ifdef __cplusplus
   }
#endif /* __cplusplus */

#endif

