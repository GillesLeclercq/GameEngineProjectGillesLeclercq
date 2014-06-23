#pragma once
#include <string>

class IGameOption
{
private:

	int			m_Width;
	int			m_Length;
	bool		m_Fullscreen;

public:

	virtual ~IGameOption() {};

	const int GetWidth() const {return m_Width; } ;
	const int GetLength() const {return m_Length; } ;
	const bool GetFullScreen() const {return m_Fullscreen; } ;

	void SetWidth(int Width) {m_Width = Width;};
	void SetLength(int Length) {m_Length = Length;};
	void SetFullscreen(bool Fullscreen) {m_Fullscreen = Fullscreen;};

	virtual bool LoadOptions(std::string) = 0;

};
