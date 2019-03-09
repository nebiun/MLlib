#include <MLlib.h>

int main(int argc, char **argv) 
{	ML_InitConsoleMode();
	ML_EnableCPad(1);
	
	printf("Hello World !\n\n");
	
	while(1)
	{
		if(CPad[0].Held.Home) { printf("Home pressed\n"); ML_ReturnToWii(); }
		if(CPad[0].Held.A) { printf("A pressed\n"); ML_ExitConsoleMode(); }
		if(CPad[0].Held.B) { printf("B pressed\n"); }
		if(CPad[0].Held.X) { printf("X pressed\n"); }
		if(CPad[0].Held.Y) { printf("Y pressed\n"); }
		if(CPad[0].Held.Start) { printf("Start pressed\n"); }
		if(CPad[0].Held.Select) { printf("Select pressed\n"); }
		if(CPad[0].Held.Left) { printf("Left pressed\n"); }
		if(CPad[0].Held.Right) { printf("Right pressed\n"); }
		if(CPad[0].Held.Up) { printf("Up pressed\n"); }
		if(CPad[0].Held.Down) { printf("Down pressed\n"); }
		if(CPad[0].Held.L) { printf("L pressed\n"); }
		if(CPad[0].Held.R) { printf("R pressed\n"); }
		if(CPad[0].Held.ZL) { printf("Z (Left) pressed\n"); }
		if(CPad[0].Held.ZR) { printf("Z (Right) pressed\n"); }		
		
		if(CPad[0].LeftStick.Magnitude > 0.2)
		{
			if(CPad[0].LeftStick.Angle > 80 && CPad[0].LeftStick.Angle < 100) printf("Right (Left Stick)\n");
			else if(CPad[0].LeftStick.Angle > 170 && CPad[0].LeftStick.Angle < 190) printf("Down (Left Stick)\n");
			else if(CPad[0].LeftStick.Angle > 260 && CPad[0].LeftStick.Angle < 280) printf("Left (Left Stick)\n");
			else if(CPad[0].LeftStick.Angle > -10 && CPad[0].LeftStick.Angle < 10) printf("Up (Left Stick)\n");
		}
		else if(CPad[0].RightStick.Magnitude > 0.2)
		{
			if(CPad[0].RightStick.Angle > 80 && CPad[0].RightStick.Angle < 100) printf("Right (Right Stick)\n");
			else if(CPad[0].RightStick.Angle > 170 && CPad[0].RightStick.Angle < 190) printf("Down (Right Stick)\n");
			else if(CPad[0].RightStick.Angle > 260 && CPad[0].RightStick.Angle < 280) printf("Left (Right Stick)\n");
			else if(CPad[0].RightStick.Angle > -10 && CPad[0].RightStick.Angle < 10) printf("Up (Right Stick)\n");
		}
		
		ML_RefreshConsoleMode();
	}
	
	return 0;
}


