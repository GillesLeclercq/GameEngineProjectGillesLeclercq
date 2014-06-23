#include "ButtonSet.h"

ButtonSet::ButtonSet( int buttonNb )
{
	m_KeyPressed = new bool[buttonNb];
	m_KeyDown = new bool[buttonNb];

	for( int i = 0; i<buttonNb; i++ )
	{
		m_KeyDown[i] = m_KeyPressed[i] = false;
	}

	m_ButtonsNb = buttonNb;
}

ButtonSet::~ButtonSet()
{
	SAFE_DELETE( m_KeyPressed );
	SAFE_DELETE( m_KeyDown );
}