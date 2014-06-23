#pragma once

#include <memory>

#include "IInputSet.h"
#include "Utilities.h"

class ButtonSet : virtual public IInputSet
{
private:
	bool* m_KeyPressed;
	bool* m_KeyDown;

	int m_ButtonsNb;

public:
	ButtonSet( int buttonNb );
	~ButtonSet();

	bool Button_IsPressed( int ButtonID ) const { return ( ButtonID < m_ButtonsNb ? m_KeyPressed[ButtonID] : false ); }
	bool Button_IsDown( int ButtonID ) const { return ( ButtonID < m_ButtonsNb ? m_KeyDown[ButtonID] : false ); }

	void Button_OnKeyDown( int ButtonID ) { if( ButtonID<m_ButtonsNb ) { m_KeyPressed[ButtonID] = m_KeyDown[ButtonID] = true; } }
	void Button_OnKeyUp( int ButtonID ) { if( ButtonID<m_ButtonsNb ) { m_KeyDown[ButtonID] = false; } }

	void Button_ResetKeyPressed() { for( auto i = 0; i<m_ButtonsNb; i++ ) { m_KeyPressed[i] = false; } }
	void Button_ResetKeyDown() { for( auto i = 0; i<m_ButtonsNb; i++ ) { m_KeyDown[i] = false; } }
};

typedef std::shared_ptr<ButtonSet> ButtonSetPtr;
typedef std::weak_ptr<ButtonSet> WkButtonSetPtr;