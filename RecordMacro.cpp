#include "RecordMacro.h"

RecordMacro::RecordMacro(string name)
{
	//interface will ask user for the name.
	macro_name = name + ".mcr";
}

vector<int> RecordMacro::recordMacro(int mode)
{
///////////////////////////////////////////////////////////Keyboard/////////////////////////////////////////////////////////////////////	
	if(mode==1)
	{	
		int delay = 0;
		time_t end = 0; 
			while (true)
			{
				for (int key = 8; key <= 255; key++)
				{
					if (GetAsyncKeyState(key) == -32767)
					{		
					time_t start = time(0);
					actions.push_back(key);
					delay = start-end;
					cout << key << " " << delay << endl;
					actions.push_back(delay);
					end = time(0);
					}
				}
			}
	}
	
	else if(mode==2)
	{	
		while (true)
		{
			for(int key=8; key<=255; key++)
			{ 
				if (GetAsyncKeyState(key) == -32767)
				{	
					actions.push_back(key);
					actions.push_back(0);
				}
			}
		}
	}
	
	else
		return 0;
///////////////////////////////////////////////////////////////Mouse/////////////////////////////////////////////////////////////////////
	
	
	
	//NOTE: this code section is to be shared with the EditMacro file
	//loop until scroll lock is hit VK_SCROLL/0x91
	//if mode is 1, delays are recorded
	//if mode is 2, delays are not recorded
	//basically while it's waiting between keys, it will count the milliseconds
	//with a native time function. once a key is pressed, it will record the delay
	//and append it to the vector with push_back along with the new event;
	//if in mode 2, push a 0 between each event into the vector.
}

RecordMacro::saveMacro()
{
	ofstream outputFile;
	outputFile.open("macro_name ");

	for (int i = 0; i < actions.size(); i++)
	{
		outputFile << actions[i] << " " << endl;
	}
	outputFile.close();
	
	//SHARED CODE FROM EDITMACRO
	////open a file named \macros\macro_name in write mode
	//for(int i =0; i < actions.size(); i++)
	//file << actions[i]
	//file << ',' or ' ';
}

RecordMacro::pause()
{
	
}

RecordMacro::resume()
{
	
}

///////////////////////////////////////////////////////////////Initial example/////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

const int MacroMaxLen = 100;

struct Macro
{
	int SleepTime;						//How long to wait 
	int SleepTimeBeforeClick;				//How long to wait before click
	int MacroIndex;						//Position in Array
	POINT CursorPosition[MacroMaxLen];			//Array that holds x,y position of cursor
};

void MouseLeftClick()
{
	INPUT Input = { 0 };					//
	Input.type = INPUT_MOUSE;				//
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;		//
	SendInput(1, &Input, sizeof(INPUT));			//

	ZeroMemory(&Input, sizeof(INPUT));			//
	Input.type = INPUT_MOUSE;				//
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;			//
	SendInput(1, &Input, sizeof(INPUT));			//
}

void IsertNewMacroPos(Macro* macro)
{
	if (macro->MacroIndex + 1 < MacroMaxLen)
		{
		macro->MacroIndex++;
		GetCursorPos(&macro->CursorPosition[macro->MacroIndex]);
		cout << "New Macro Inserted" << endl;
		}
}

void ExecuteMacro(Macro* macro)
{
	for (int i = 0; i < macro->MacroIndex + 1; i++)
	{
		SetCursorPos(macro->CursorPosition[i].x, macro->CursorPosition[i].y);
		Sleep(macro->SleepTimeBeforeClick);	
		MouseLeftClick();
		Sleep(macro->SleepTime);
	}
}

Macro CreateNewMacro(int sleepbeforeclick, int sleep)
{
	Macro macro;
	macro.SleepTime = sleep;
	macro.SleepTimeBeforeClick = sleepbeforeclick;
	macro.MacroIndex = -1;
	return macro;

}


int main()
{
	bool macroInsertDone = true;
	bool macroExecuteDone = true;

	Macro m = CreateNewMacro(50, 50);

	while (true)
	{
		//Set new macro position
		if (GetAsyncKeyState('Z'))
			macroInsertDone = false;
		else if (!GetAsyncKeyState('Z'))
		{
			if (!macroInsertDone)
				IsertNewMacroPos(&m);
			macroInsertDone = true;	
		}
		//Execute macro
		if (GetAsyncKeyState('X'))
			macroExecuteDone = false;
		else if (!GetAsyncKeyState('X'))
		{
			if (!macroExecuteDone)
				ExecuteMacro(&m);
			macroExecuteDone = true;
		}
		Sleep(5);
	}



	return 0;
}
