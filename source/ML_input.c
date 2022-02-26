#include <MLlib.h>

/**
* \file
* \brief This file contains input functions.
*/

u8 nb_wiimote = 1, nb_pads_gc = 0;
u8 _nunchuk_enabled = 0, _cpad_enabled = 0, _guitar_enabled = 0;

WPads Wiimote[WPAD_MAX_WIIMOTES];
Nunchuks Nunchuk[WPAD_MAX_WIIMOTES];
CPads CPad[WPAD_MAX_WIIMOTES];
GH Guitar[WPAD_MAX_WIIMOTES];
GC_Pads Pad[4];

void ML_InitPad(void)
{
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetVRes(WPAD_CHAN_ALL, _screenWidth, _screenHeight);

	PAD_Init();
}

void ML_GetPads(void)
{
	ML_GetPadsWii();
	ML_GetPadsGC();
}

void ML_SetNumberOfPads(u8 wiimotesNumber, u8 gc_padsNumber)
{
	if(wiimotesNumber <= WPAD_MAX_WIIMOTES)	
		nb_wiimote = wiimotesNumber;
	if(gc_padsNumber <= 4)
		nb_pads_gc = gc_padsNumber;
}

int ML_GetWiimoteExtension(u8 wpad)
{
	WPADData* data = WPAD_Data(wpad);
	return data->exp.type;
}

// ---------------
//       Wii
// ---------------

static void _GetNunchuk(u8 i, WPADData *wd)
{
	Nunchuks *nc = &Nunchuk[i];
	
	// Nunchuk C Button
	nc->Released.C = (wd->btns_u & WPAD_NUNCHUK_BUTTON_C);
	nc->Newpress.C = (wd->btns_d & WPAD_NUNCHUK_BUTTON_C);
	nc->Held.C = (wd->btns_h & WPAD_NUNCHUK_BUTTON_C);

	// Nunchuk Z Button
	nc->Released.Z = (wd->btns_u & WPAD_NUNCHUK_BUTTON_Z);
	nc->Newpress.Z = (wd->btns_d & WPAD_NUNCHUK_BUTTON_Z);
	nc->Held.Z = (wd->btns_h & WPAD_NUNCHUK_BUTTON_Z);

	// Nunchuk Stick
	nc->Stick.Angle = wd->exp.nunchuk.js.ang;    
	nc->Stick.Magnitude = wd->exp.nunchuk.js.mag; 
	nc->GForce.X = wd->exp.nunchuk.gforce.x;
	nc->GForce.Y = wd->exp.nunchuk.gforce.y;
	nc->GForce.Z = wd->exp.nunchuk.gforce.z;
	nc->Orient.Roll = wd->exp.nunchuk.orient.roll;
	nc->Orient.JustRoll = wd->exp.nunchuk.orient.a_roll;
	nc->Orient.Pitch = wd->exp.nunchuk.orient.pitch;
	nc->Orient.JustPitch = wd->exp.nunchuk.orient.a_pitch;
	nc->Orient.Yaw = wd->exp.nunchuk.orient.yaw;
}

static void _GetCPad(u8 i, WPADData *wd)
{
	CPads *cp = &CPad[i];
	
	// Button A
	cp->Released.A = (wd->btns_u & WPAD_CLASSIC_BUTTON_A);
	cp->Newpress.A = (wd->btns_d & WPAD_CLASSIC_BUTTON_A);
	cp->Held.A = (wd->btns_h & WPAD_CLASSIC_BUTTON_A);
	// Button B
	cp->Released.B = (wd->btns_u & WPAD_CLASSIC_BUTTON_B);
	cp->Newpress.B = (wd->btns_d & WPAD_CLASSIC_BUTTON_B);
	cp->Held.B = (wd->btns_h & WPAD_CLASSIC_BUTTON_B);
	// Button X
	cp->Released.X = (wd->btns_u & WPAD_CLASSIC_BUTTON_X);
	cp->Newpress.X = (wd->btns_d & WPAD_CLASSIC_BUTTON_X);
	cp->Held.X = (wd->btns_h & WPAD_CLASSIC_BUTTON_X);
	// Button Y
	cp->Released.Y = (wd->btns_u & WPAD_CLASSIC_BUTTON_Y);
	cp->Newpress.Y = (wd->btns_d & WPAD_CLASSIC_BUTTON_Y);
	cp->Held.Y = (wd->btns_h & WPAD_CLASSIC_BUTTON_Y);
	// Button Start
	cp->Released.Start = (wd->btns_u & WPAD_CLASSIC_BUTTON_PLUS);
	cp->Newpress.Start = (wd->btns_d & WPAD_CLASSIC_BUTTON_PLUS);
	cp->Held.Start = (wd->btns_h & WPAD_CLASSIC_BUTTON_PLUS);
	// Button Select
	cp->Released.Select = (wd->btns_u & WPAD_CLASSIC_BUTTON_MINUS);
	cp->Newpress.Select = (wd->btns_d & WPAD_CLASSIC_BUTTON_MINUS);
	cp->Held.Select = (wd->btns_h & WPAD_CLASSIC_BUTTON_MINUS);
	// Button Home
	cp->Released.Home = (wd->btns_u & WPAD_CLASSIC_BUTTON_HOME);
	cp->Newpress.Home = (wd->btns_d & WPAD_CLASSIC_BUTTON_HOME);
	cp->Held.Home = (wd->btns_h & WPAD_CLASSIC_BUTTON_HOME);
	// Button Up
	cp->Released.Up = (wd->btns_u & WPAD_CLASSIC_BUTTON_UP);
	cp->Newpress.Up = (wd->btns_d & WPAD_CLASSIC_BUTTON_UP);
	cp->Held.Up = (wd->btns_h & WPAD_CLASSIC_BUTTON_UP);
	// Button Down
	cp->Released.Down = (wd->btns_u & WPAD_CLASSIC_BUTTON_DOWN);
	cp->Newpress.Down = (wd->btns_d & WPAD_CLASSIC_BUTTON_DOWN);
	cp->Held.Down = (wd->btns_h & WPAD_CLASSIC_BUTTON_DOWN);
	// Button Left
	cp->Released.Left = (wd->btns_u & WPAD_CLASSIC_BUTTON_LEFT);
	cp->Newpress.Left = (wd->btns_d & WPAD_CLASSIC_BUTTON_LEFT);
	cp->Held.Left = (wd->btns_h & WPAD_CLASSIC_BUTTON_LEFT);
	// Button Right
	cp->Released.Right = (wd->btns_u & WPAD_CLASSIC_BUTTON_RIGHT);
	cp->Newpress.Right = (wd->btns_d & WPAD_CLASSIC_BUTTON_RIGHT);
	cp->Held.Right = (wd->btns_h & WPAD_CLASSIC_BUTTON_RIGHT);
	// Button L
	cp->Released.L = (wd->btns_u & WPAD_CLASSIC_BUTTON_FULL_L);
	cp->Newpress.L = (wd->btns_d & WPAD_CLASSIC_BUTTON_FULL_L);
	cp->Held.L = (wd->btns_h & WPAD_CLASSIC_BUTTON_FULL_L);
	// Button R
	cp->Released.R = (wd->btns_u & WPAD_CLASSIC_BUTTON_FULL_R);
	cp->Newpress.R = (wd->btns_d & WPAD_CLASSIC_BUTTON_FULL_R);
	cp->Held.R = (wd->btns_h & WPAD_CLASSIC_BUTTON_FULL_R);
	// Button ZL
	cp->Released.ZL = (wd->btns_u & WPAD_CLASSIC_BUTTON_ZL);
	cp->Newpress.ZL = (wd->btns_d & WPAD_CLASSIC_BUTTON_ZL);
	cp->Held.ZL = (wd->btns_h & WPAD_CLASSIC_BUTTON_ZL);
	// Button ZR
	cp->Released.ZR = (wd->btns_u & WPAD_CLASSIC_BUTTON_ZR);
	cp->Newpress.ZR = (wd->btns_d & WPAD_CLASSIC_BUTTON_ZR);
	cp->Held.ZR = (wd->btns_h & WPAD_CLASSIC_BUTTON_ZR);
	
	// Sticks
	cp->LeftStick.Angle = wd->exp.classic.ljs.ang;    
	cp->LeftStick.Magnitude = wd->exp.classic.ljs.mag; 	
	cp->RightStick.Angle = wd->exp.classic.rjs.ang;    
	cp->RightStick.Magnitude = wd->exp.classic.rjs.mag; 
}

static void _GetGuitar(u8 i, WPADData *wd)
{
	GH *gt = &Guitar[i];

	// Button +
	gt->Released.Plus = (wd->btns_u & WPAD_GUITAR_HERO_3_BUTTON_PLUS);
	gt->Newpress.Plus = (wd->btns_d & WPAD_GUITAR_HERO_3_BUTTON_PLUS);
	gt->Held.Plus = (wd->btns_h & WPAD_GUITAR_HERO_3_BUTTON_PLUS);
	// Button -
	gt->Released.Minus = (wd->btns_u & WPAD_GUITAR_HERO_3_BUTTON_MINUS);
	gt->Newpress.Minus = (wd->btns_d & WPAD_GUITAR_HERO_3_BUTTON_MINUS);
	gt->Held.Minus = (wd->btns_h & WPAD_GUITAR_HERO_3_BUTTON_MINUS);
	// Button Red
	gt->Released.Red = (wd->btns_u & WPAD_GUITAR_HERO_3_BUTTON_RED);
	gt->Newpress.Red = (wd->btns_d & WPAD_GUITAR_HERO_3_BUTTON_RED);
	gt->Held.Red = (wd->btns_h & WPAD_GUITAR_HERO_3_BUTTON_RED);
	// Button Yellow
	gt->Released.Yellow = (wd->btns_u & WPAD_GUITAR_HERO_3_BUTTON_YELLOW);
	gt->Newpress.Yellow = (wd->btns_d & WPAD_GUITAR_HERO_3_BUTTON_YELLOW);
	gt->Held.Yellow = (wd->btns_h & WPAD_GUITAR_HERO_3_BUTTON_YELLOW);
	// Button Green
	gt->Released.Green = (wd->btns_u & WPAD_GUITAR_HERO_3_BUTTON_GREEN);
	gt->Newpress.Green = (wd->btns_d & WPAD_GUITAR_HERO_3_BUTTON_GREEN);
	gt->Held.Green = (wd->btns_h & WPAD_GUITAR_HERO_3_BUTTON_GREEN);
	// Button Orange
	gt->Released.Orange = (wd->btns_u & WPAD_GUITAR_HERO_3_BUTTON_ORANGE);
	gt->Newpress.Orange = (wd->btns_d & WPAD_GUITAR_HERO_3_BUTTON_ORANGE);
	gt->Held.Orange = (wd->btns_h & WPAD_GUITAR_HERO_3_BUTTON_ORANGE);
	// Button Blue
	gt->Released.Blue = (wd->btns_u & WPAD_GUITAR_HERO_3_BUTTON_BLUE);
	gt->Newpress.Blue = (wd->btns_d & WPAD_GUITAR_HERO_3_BUTTON_BLUE);
	gt->Held.Blue = (wd->btns_h & WPAD_GUITAR_HERO_3_BUTTON_BLUE);
	// Button Strum Up
	gt->Released.StrumUp = (wd->btns_u & WPAD_GUITAR_HERO_3_BUTTON_STRUM_UP);
	gt->Newpress.StrumUp = (wd->btns_d & WPAD_GUITAR_HERO_3_BUTTON_STRUM_UP);
	gt->Held.StrumUp = (wd->btns_h & WPAD_GUITAR_HERO_3_BUTTON_STRUM_UP);
	// Button Strum Down
	gt->Released.StrumDown = (wd->btns_u & WPAD_GUITAR_HERO_3_BUTTON_STRUM_DOWN);
	gt->Newpress.StrumDown = (wd->btns_d & WPAD_GUITAR_HERO_3_BUTTON_STRUM_DOWN);
	gt->Held.StrumDown = (wd->btns_h & WPAD_GUITAR_HERO_3_BUTTON_STRUM_DOWN);
	
	// Stick
	gt->Stick.Angle = wd->exp.gh3.js.ang;    
	gt->Stick.Magnitude = wd->exp.gh3.js.mag; 	
}

void ML_GetPadsWii(void)
{
	u8 i;

	WPAD_ReadPending(WPAD_CHAN_ALL, NULL);
	
	for(i = 0; i < nb_wiimote; i++)
	{
		u32 type;
		WPads *wp = &Wiimote[i];
		WPADData *wd = WPAD_Data(i);
		
		// Is enabled
		if((WPAD_Probe(i, &type)) != WPAD_ERR_NONE) 
			wp->Enabled = 0;
		else {
			float theta;
			
			wp->Enabled = 1;

			// Button A
			wp->Released.A = (wd->btns_u & WPAD_BUTTON_A);
			wp->Newpress.A = (wd->btns_d & WPAD_BUTTON_A);
			wp->Held.A = (wd->btns_h & WPAD_BUTTON_A);
			// Button B
			wp->Released.B = (wd->btns_u & WPAD_BUTTON_B);
			wp->Newpress.B = (wd->btns_d & WPAD_BUTTON_B);
			wp->Held.B = (wd->btns_h & WPAD_BUTTON_B);
			// Button +
			wp->Released.Plus = (wd->btns_u & WPAD_BUTTON_PLUS);
			wp->Newpress.Plus = (wd->btns_d & WPAD_BUTTON_PLUS);
			wp->Held.Plus = (wd->btns_h & WPAD_BUTTON_PLUS);
			// Button -
			wp->Released.Minus = (wd->btns_u & WPAD_BUTTON_MINUS);
			wp->Newpress.Minus = (wd->btns_d & WPAD_BUTTON_MINUS);
			wp->Held.Minus = (wd->btns_h & WPAD_BUTTON_MINUS);
			// Button Home
			wp->Released.Home = (wd->btns_u & WPAD_BUTTON_HOME);
			wp->Newpress.Home = (wd->btns_d & WPAD_BUTTON_HOME);
			wp->Held.Home = (wd->btns_h & WPAD_BUTTON_HOME);
			// Button 1
			wp->Released.One = (wd->btns_u & WPAD_BUTTON_1);
			wp->Newpress.One = (wd->btns_d & WPAD_BUTTON_1);
			wp->Held.One = (wd->btns_h & WPAD_BUTTON_1);
			// Button 2
			wp->Released.Two = (wd->btns_u & WPAD_BUTTON_2);
			wp->Newpress.Two = (wd->btns_d & WPAD_BUTTON_2);
			wp->Held.Two = (wd->btns_h & WPAD_BUTTON_2);
			// Button Up
			wp->Released.Up = (wd->btns_u & WPAD_BUTTON_UP);
			wp->Newpress.Up = (wd->btns_d & WPAD_BUTTON_UP);
			wp->Held.Up = (wd->btns_h & WPAD_BUTTON_UP);
			// Button Down
			wp->Released.Down = (wd->btns_u & WPAD_BUTTON_DOWN);
			wp->Newpress.Down = (wd->btns_d & WPAD_BUTTON_DOWN);
			wp->Held.Down = (wd->btns_h & WPAD_BUTTON_DOWN);
			// Button Left
			wp->Released.Left = (wd->btns_u & WPAD_BUTTON_LEFT);
			wp->Newpress.Left = (wd->btns_d & WPAD_BUTTON_LEFT);
			wp->Held.Left = (wd->btns_h & WPAD_BUTTON_LEFT);
			// Button Right
			wp->Released.Right = (wd->btns_u & WPAD_BUTTON_RIGHT);
			wp->Newpress.Right = (wd->btns_d & WPAD_BUTTON_RIGHT);
			wp->Held.Right = (wd->btns_h & WPAD_BUTTON_RIGHT);

			// IR
			wp->IR.Valid = wd->ir.valid;
			if(wd->ir.valid)
			{
				wp->IR.JustX = wd->ir.x;
				wp->IR.JustY = wd->ir.y;
				wp->IR.Angle = wd->ir.angle;
	
				theta = wp->IR.Angle / 180.0 * M_PI;
				wp->IR.X = wd->ir.x + 10*sinf(theta);
				wp->IR.Y = wd->ir.y - 10*cosf(theta);
			}
			if(wd->ir.smooth_valid)
			{
				wp->IR.SmoothX = wd->ir.sx;
				wp->IR.SmoothY = wd->ir.sy;
			}
			if(wd->ir.raw_valid) 
				wp->IR.Z = wd->ir.z;

			// Orientation
			wp->Orient.Roll = wd->orient.roll;
			wp->Orient.Pitch = wd->orient.pitch;
			wp->Orient.JustRoll = wd->orient.a_roll;
			wp->Orient.JustPitch = wd->orient.a_pitch;
			wp->Orient.Yaw = wd->orient.yaw;

			// Gravity Force
			wp->GForce.X = wd->gforce.x;
			wp->GForce.Y = wd->gforce.y;
			wp->GForce.Z = wd->gforce.z;
			
			if(_nunchuk_enabled) 
				_GetNunchuk(i, wd);
			if(_cpad_enabled) 
				_GetCPad(i, wd);
			if(_guitar_enabled) 
				_GetGuitar(i, wd);
		}
	}
}

bool ML_EnableNunchuk(u8 enabled) 
{ 
	if(enabled == 0 || enabled == 1) { 
		_nunchuk_enabled = enabled; 
	} 
	return _nunchuk_enabled; 
}

bool ML_EnableCPad(u8 enabled) 
{ 
	if(enabled == 0 || enabled == 1) { 
		_cpad_enabled = enabled; 
	} 
	return _cpad_enabled; 
}

bool ML_EnableGuitar(u8 enabled) 
{ 
	if(enabled == 0 || enabled == 1) { 
		_guitar_enabled = enabled;
	} 
	return _guitar_enabled; 
}

void ML_RumbleWiimote(s32 wpad, int enabled)
{
	WPAD_Rumble(wpad, enabled);
}

// ---------------
//       GC
// ---------------
typedef struct {
	u32 down;
	u32 held;
	u32 up;
} control_t;

void ML_GetPadsGC(void)
{
	u8 i;

	PAD_ScanPads();

	for(i = 0; i < nb_pads_gc; i++)
	{
		GC_Pads *gcp;
		control_t nbtn;
		control_t *btn = &nbtn;
		
		btn->held = PAD_ButtonsHeld(i);
		btn->up = PAD_ButtonsUp(i);
		btn->down = PAD_ButtonsDown(i);
		gcp = &Pad[i];

		// Button Start
		gcp->Released.Start = (btn->up & PAD_BUTTON_START);
		gcp->Newpress.Start = (btn->held & PAD_BUTTON_START) && (!gcp->Held.Start);
		gcp->Held.Start = (btn->held & PAD_BUTTON_START);
		// Button A
		gcp->Released.A = (btn->up & PAD_BUTTON_A);
		gcp->Newpress.A = (btn->held & PAD_BUTTON_A) && (!gcp->Held.A);
		gcp->Held.A = (btn->held & PAD_BUTTON_A);
		// Button B
		gcp->Released.B = (btn->up & PAD_BUTTON_B);
		gcp->Newpress.B = (btn->held & PAD_BUTTON_B) && (!gcp->Held.B);
		gcp->Held.B = (btn->held & PAD_BUTTON_B);
		// Button X
		gcp->Released.X = (btn->up & PAD_BUTTON_X);
		gcp->Newpress.X = (btn->held & PAD_BUTTON_X) && (!gcp->Held.X);
		gcp->Held.X = (btn->held & PAD_BUTTON_X);
		// Button Y
		gcp->Released.Y = (btn->up & PAD_BUTTON_Y);
		gcp->Newpress.Y = (btn->held & PAD_BUTTON_Y) && (!gcp->Held.Y);
		gcp->Held.Y = (btn->held & PAD_BUTTON_Y);

		// Button Up
		gcp->Released.Up = (btn->up & PAD_BUTTON_UP);
		gcp->Newpress.Up = (btn->held & PAD_BUTTON_UP) && (!gcp->Held.Up);
		gcp->Held.Up = (btn->held & PAD_BUTTON_UP);
		// Button Down
		gcp->Released.Down = (btn->up & PAD_BUTTON_DOWN);
		gcp->Newpress.Down = (btn->held & PAD_BUTTON_DOWN) && (!gcp->Held.Down);
		gcp->Held.Down = (btn->held & PAD_BUTTON_DOWN);
		// Button Left
		gcp->Released.Left = (btn->up &  PAD_BUTTON_LEFT);
		gcp->Newpress.Left = (btn->held & PAD_BUTTON_LEFT) && (!gcp->Held.Left);
		gcp->Held.Left = (btn->held & PAD_BUTTON_LEFT);
		// Button Right
		gcp->Released.Right = (btn->up & PAD_BUTTON_RIGHT);
		gcp->Newpress.Right = (btn->held & PAD_BUTTON_RIGHT) && (!gcp->Held.Right);
		gcp->Held.Right = (btn->held & PAD_BUTTON_RIGHT);

		// Trigger L
		gcp->Released.L = (btn->up & PAD_TRIGGER_L);
		gcp->Newpress.L = (btn->held & PAD_TRIGGER_L) && (!gcp->Held.L);
		gcp->Held.L = (btn->held & PAD_TRIGGER_L);
		// Trigger R
		gcp->Released.R = (btn->up & PAD_TRIGGER_R);
		gcp->Newpress.R = (btn->held & PAD_TRIGGER_R) && (!gcp->Held.R);
		gcp->Held.R = (btn->held & PAD_TRIGGER_R);
		// Trigger Z
		gcp->Released.Z = (btn->up & PAD_TRIGGER_Z);
		gcp->Newpress.Z = (btn->held & PAD_TRIGGER_Z) && (!gcp->Held.Z);
		gcp->Held.Z = (btn->held & PAD_TRIGGER_Z);

		// Stick X
		gcp->Stick.X = PAD_StickX(i);
		// Stick Y
		gcp->Stick.Y = PAD_StickY(i);

		// Stick Up
		gcp->Stick.Released.Up = (!(gcp->Stick.Y > 65) && (gcp->Stick.Held.Up));
		gcp->Stick.Newpress.Up = ((gcp->Stick.Y > 65) && (!gcp->Stick.Held.Up));
		gcp->Stick.Held.Up = (gcp->Stick.Y > 65);
		// Stick Down
		gcp->Stick.Released.Down = (!(gcp->Stick.Y < -65) && (gcp->Stick.Held.Down));
		gcp->Stick.Newpress.Down = ((gcp->Stick.Y < -65) && (!gcp->Stick.Held.Down));
		gcp->Stick.Held.Down = (gcp->Stick.Y < -65);
		// Stick Left
		gcp->Stick.Released.Left = (!(gcp->Stick.X < -65) && (gcp->Stick.Held.Left));
		gcp->Stick.Newpress.Left = ((gcp->Stick.X < -65) && (!gcp->Stick.Held.Left));
		gcp->Stick.Held.Left = (gcp->Stick.X < -65);
		// Stick Right
		gcp->Stick.Released.Right = (!(gcp->Stick.X > 65) && (gcp->Stick.Held.Right));
		gcp->Stick.Newpress.Right = ((gcp->Stick.X > 65) && (!gcp->Stick.Held.Right));
		gcp->Stick.Held.Right = (gcp->Stick.X > 65);
	}
}

// #### Thanks Botskiz for these lines ! :)  ####
//====================================================================
//	Reset callback function.
//====================================================================
void _doSystemReset(u32 irq, void *ctx)
{
	bReset = true;
}

//====================================================================
//	PowerOff callback function.
//====================================================================
void _doPowerOff(void)
{
	bPowerOff = true;
}

//====================================================================
//	PowerOff callback function for the Wii Remote power button.
//====================================================================
void _doPadPowerOff(s32 chan)
{
	if(chan == WPAD_CHAN_0)
		bPowerOff = true;
}


