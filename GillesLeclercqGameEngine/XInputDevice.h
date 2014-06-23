#pragma once

#include <Windows.h>
#include <Xinput.h>
#include <map>
#include <memory>
#include <utility>

#include "ButtonSet.h"
#include "AnalogicSet.h"
#include "StickSet.h"
#include "Utilities.h"

enum XINPUT_BUTTON
{
	A, B, X, Y,
	UP, DOWN, LEFT, RIGHT,
	LB, RB,
	LS, RS,
	START, BACK
};

enum XINPUT_ANALOGIC
{
	LT, RT
};

enum XINPUT_STICK
{
	LEFT_STICK, RIGHT_STICK
};

class XInputDevice : public ButtonSet, public AnalogicSet, public StickSet
{
private:
	XINPUT_STATE m_State;

	int m_Port;
	bool m_Connected;

	static WORD s_XInputButtonList[14];
	static std::map<std::string, int> s_StrToID;

public:
	XInputDevice( int port );
	~XInputDevice() {}

	bool Initialize();
	void CalibrateDeadzone();

	bool CheckConnection() { return XInputGetState( m_Port, &m_State ) == ERROR_SUCCESS; }
	bool Refresh();

	void ResetInput();

	int VStringToInputID( std::string& code ) override;

	// Accessors
	bool IsConnected() const { return m_Connected; }
	int GetPort() const { return m_Port; }
};

typedef std::shared_ptr<XInputDevice> XInputDevicePtr;
typedef std::weak_ptr<XInputDevice> WkXInputDevicePtr;