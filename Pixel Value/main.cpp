#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
using namespace std;
int tracker;
void printValue(COLORREF& p)
{
	printf("---------------------------------------\n");
	printf("R: %d\n",GetRValue(p));
	printf("G: %d\n",GetGValue(p));
	printf("B: %d\n",GetBValue(p));
}

void printHTMLValue(COLORREF& p, char* result)
{
	printf("---------------------------------------\n");
	printf("HTML color value: #");
	strcpy(result,"#");
	if (GetRValue(p) < 16)
	{
		strcat(result,"0");
		printf("0");
	}
	char tmp[3];

	itoa(GetRValue(p),tmp,16);
	strcat(result,tmp);
	printf("%x",GetRValue(p));
	if (GetGValue(p) < 16)
	{
		strcat(result,"0");
		printf("0");
	}

	itoa(GetGValue(p),tmp,16);
	strcat(result,tmp);
	printf("%x",GetGValue(p));
	if (GetBValue(p) < 16)
	{
		strcat(result,"0");
		printf("0");
	}

	itoa(GetBValue(p),tmp,16);
	strcat(result,tmp);
	printf("%x\n",GetBValue(p));

	printf("---------------------------------------\n");
	printf("\n");
}
void printHTMLValueNODEBUG(COLORREF& p, char* result)
{
	strcpy(result,"#");
	if (GetRValue(p) < 16)
		strcat(result,"0");
	char tmp[3];

	itoa(GetRValue(p),tmp,16);
	strcat(result,tmp);
	if (GetGValue(p) < 16)
		strcat(result,"0");

	itoa(GetGValue(p),tmp,16);
	strcat(result,tmp);
	if (GetBValue(p) < 16)
		strcat(result,"0");

	itoa(GetBValue(p),tmp,16);
	strcat(result,tmp);
}
int main () 
{
	ofstream outputFile;
	outputFile.open("output.html",ios::out);
	POINT pos;
	pos.x = 0; pos.y = 0;
	printf("\n");
	int i=1;
	char result [8];
	outputFile<<"<html><head></head><body><table border=\"1\"><tr><td WIDTH=\"40\"><center>No.</center></td><td WIDTH=\"200\"><center>Colour</center></td><td WIDTH=\"220\"><center>RGB values and HTML code</center></td></tr>";
	int flag = 0;
	int debug_mode = 0;
	int something_done = 0;
	printf("-=== [ Pixel Value  v. 1.0 ] ===-\n");
	printf("by Georgi Sabev\n");
	printf("--------------------------------------------------------------------------\n");
	printf("INSTRUCTIONS\n");
	printf("1. Press Shift to start mouse click tracking\n");
	printf("2. Click anywhere to capture the colour under the mouse cursor\n");
	printf("3. Press Ctrl to stop mouse click tracking\n");
	printf("4. Press the middle mouse button to close the console and display\n");
	printf("   the colours and their codes in a table, using your default web browser.\n");
	printf("\n");
	printf("To see debugging information (such as cursor position, RGB value of colour\n");
	printf("under the cursor) in the console at runtime, enable Debug Mode\n");
	printf("To enable Debug Mode, press Alt.\n");
	printf("P.S. The dots represent mouse clicks :]\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	
	while (true)
	{
		if (GetAsyncKeyState(VK_MENU) && debug_mode == 1)
		{
			debug_mode = 0;
			printf("\nDebug mode disabled, press Alt to enable again.\n");
			something_done = 1;
			Sleep(200);
		}
		if (GetAsyncKeyState(VK_MENU) && debug_mode == 0)
		{
			debug_mode = 1;
			printf("\nDebug mode enabled, press Alt to disable.\n");
			something_done = 1;
			Sleep(200);
		}
		if (GetAsyncKeyState(VK_SHIFT))
		{
			flag = 1;
			printf("\nMouse click tracking started, press Ctrl to stop, or Middle Mouse Button\n");
			printf("to exit this console and display the colours in a table.\n");
			something_done = 1;
			Sleep(200);
		}
		if (GetAsyncKeyState(VK_CONTROL))
		{
			flag = 0;
			printf("\nMouse click tracking stopped, press Shift to start again, or Middle Mouse Button\n");
			printf("to exit this console and display the colours in a table.\n");
			something_done = 1;
			Sleep(200);
		}
		switch (debug_mode)
		{
		case 1:
			if (GetAsyncKeyState(VK_LBUTTON) && flag)
			{
				HDC hdc = GetDC( NULL );
				GetCursorPos(&pos);
				COLORREF pixel = GetPixel( hdc, pos.x, pos.y );
				printf("Cursor position: %i - %i\n", pos.x, pos.y);
				printValue(pixel);
				printHTMLValue(pixel,result);
				outputFile<<"\n"<<"<tr><td WIDTH=\"40\"><center><b>"<<i<<".</b></center></td><td WIDTH=\"200\" HEIGHT=\"125\" bgcolor="<<"\""<<result<<"\"></td><td WIDTH=\"220\">Cursor position: "<<pos.x<<","<<pos.y<<"<BR>"<<"R: "<<(int)GetRValue(pixel)<<"<BR>"<<"G: "<<(int)GetGValue(pixel)<<"<BR>"<<"B: "<<(int)GetBValue(pixel)<<"<BR>"<<result<<"</td></tr>\n";
				i++;
				something_done = 1;
				Sleep(200);			
			}
			break;
		case 0:
			if (GetAsyncKeyState(VK_LBUTTON) && flag)
			{
				printf(".");
				HDC hdc = GetDC( NULL );
				GetCursorPos(&pos);
				COLORREF pixel = GetPixel( hdc, pos.x, pos.y );
				printHTMLValueNODEBUG(pixel,result);
				outputFile<<"\n"<<"<tr><td WIDTH=\"40\"><center><b>"<<i<<".</b></center></td><td WIDTH=\"200\" HEIGHT=\"125\" bgcolor="<<"\""<<result<<"\"></td><td WIDTH=\"220\">Cursor position: "<<pos.x<<","<<pos.y<<"<BR>"<<"R: "<<(int)GetRValue(pixel)<<"<BR>"<<"G: "<<(int)GetGValue(pixel)<<"<BR>"<<"B: "<<(int)GetBValue(pixel)<<"<BR>"<<result<<"</td></tr>\n";
				something_done = 1;
				i++;
				Sleep(200);
			}
			break;
		}				
		if (GetAsyncKeyState(VK_MBUTTON)) {break;}
	}
	outputFile<<"</table></body></html>";
	outputFile.close();
	if (something_done)
		ShellExecute(NULL, "open", "output.html", NULL, NULL, SW_SHOWNORMAL);
	return 0;
}