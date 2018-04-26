#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include <dinput.h>

using namespace DirectX;


struct GameData
{
	float m_dt;  //time step since last frame

	//input
	unsigned char* m_keyboardState; //current state of the Keyboard
	unsigned char* m_prevKeyboardState; //previous frame's state of the keyboard
	DIMOUSESTATE* m_mouseState; //current state of the mouse

};
#endif