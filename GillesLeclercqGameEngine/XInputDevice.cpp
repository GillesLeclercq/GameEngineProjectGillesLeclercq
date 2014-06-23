#include "XInputDevice.h"

WORD XInputDevice::s_XInputButtonList[14] = {
	XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP, XINPUT_GAMEPAD_DPAD_DOWN, XINPUT_GAMEPAD_DPAD_LEFT, XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START, XINPUT_GAMEPAD_BACK
};

std::map<std::string, int> XInputDevice::s_StrToID;

//----------------------------------------------------------------------
XInputDevice::XInputDevice( int port ): ButtonSet(14), AnalogicSet(2), StickSet(2)
{ 
	if( s_StrToID.empty() )
	{
		s_StrToID["a"] = A;		s_StrToID["b"] = B;			s_StrToID["x"] = X;			s_StrToID["y"] = Y;
		s_StrToID["up"] = UP;	s_StrToID["down"] = DOWN;	s_StrToID["left"] = LEFT;	s_StrToID["right"] = RIGHT;
		s_StrToID["lb"] = LB;	s_StrToID["rb"] = RB;
		s_StrToID["ls"] = LS;	s_StrToID["rb"] = RS;
		s_StrToID["start"] = START;							s_StrToID["back"] = BACK;

		s_StrToID["lt"] = LT;	s_StrToID["rt"] = RT;

		s_StrToID["lstick"] = LEFT_STICK;					s_StrToID["rstick"] = RIGHT_STICK;
		s_StrToID["left_stick"] = LEFT_STICK;				s_StrToID["right_stick"] = RIGHT_STICK;
	}

	m_Port = port;
	m_Connected = false;

	ResetInput();
	Stick_ResetDeadzones();

	Analogic_SetMaxValue( LT, 255.0f );
	Analogic_SetMaxValue( RT, 255.0f );

	Stick_SetMaxValue( LEFT_STICK, 32767.0f );
	Stick_SetMaxValue( RIGHT_STICK, 32767.0f );

	ZeroMemory( &m_State, sizeof( XINPUT_STATE ) );
}

//----------------------------------------------------------------------
// Return true if a controller is plugged on that port.
bool XInputDevice::Initialize() 
{ 
	m_Connected = CheckConnection();
	if( m_Connected ) 
	{
		CalibrateDeadzone();
		Refresh();
	}
	return m_Connected;
}

//----------------------------------------------------------------------
// Check and refresh the state of the controller.
// Return false if the controller is no longer plugged.
bool XInputDevice::Refresh()
{
	if( CheckConnection() )
	{
		Button_ResetKeyPressed();
		WORD ButtonState = m_State.Gamepad.wButtons;

		// Buttons
		for( auto i = 0; i<14; i++ )
		{
			if( ButtonState & s_XInputButtonList[i] )
			{
				if( !Button_IsDown(i) )
				{
					Button_OnKeyDown(i);
				}
			}
			else
			{
				Button_OnKeyUp(i);
			}
		}
	
		// Triggers
		Analogic_SetState( LT, (float)m_State.Gamepad.bLeftTrigger );
		Analogic_SetState( RT, (float)m_State.Gamepad.bRightTrigger );

		// Sticks
		Stick_SetState( LEFT_STICK, (float)m_State.Gamepad.sThumbLX, (float)m_State.Gamepad.sThumbLY );
		Stick_SetState( RIGHT_STICK, (float)m_State.Gamepad.sThumbRX, (float)m_State.Gamepad.sThumbRY );
	}
	else
	{
		m_Connected = false;

		ResetInput();

		// TODO: Warn the InputDeviceManager.
	}

	return m_Connected;
}

//----------------------------------------------------------------------
void XInputDevice::ResetInput()
{
	Button_ResetKeyPressed();
	Button_ResetKeyDown();

	Analogic_Reset();

	Stick_ResetState();
}

//----------------------------------------------------------------------
int XInputDevice::VStringToInputID( std::string& code )
{
	auto findIt = s_StrToID.find( StringUtilities::ToLower(code) );
	if( findIt != s_StrToID.end() )
	{
		return findIt->second;
	}
	return -1;
}

//----------------------------------------------------------------------
// Deduce the deadzone from the state of the controller at ease. 
void XInputDevice::CalibrateDeadzone()
{
	Stick_ResetDeadzones();

	for( auto i = 0; i<50 && m_Connected; i++ )
	{
		if( CheckConnection() )
		{
			Stick_ProvideDeadzoneSample( LEFT_STICK, (float)m_State.Gamepad.sThumbLX, (float)m_State.Gamepad.sThumbLY );
			Stick_ProvideDeadzoneSample( RIGHT_STICK, (float)m_State.Gamepad.sThumbRX, (float)m_State.Gamepad.sThumbRY );
		}
		else
		{
			m_Connected = false;
			ResetInput();
		}
	}
}