#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#define SAFE_DELETE( ptr )		{ if( ptr != nullptr ) { delete ptr; ptr = nullptr; } }
#define SAFE_RELEASE( ptr )		{ if( ptr != nullptr ) { ptr->Release(); ptr = nullptr; } }

class NumericUtilities
{
private:
	NumericUtilities() {}

public:
	template <typename T>
	static int Signum( T val )
	{
		return (T(0) < val) - (val < T(0));
	}
};

class StringUtilities
{
private:
	StringUtilities() {}

public:
	static std::string GetExtension( const std::string& file )
	{
		unsigned int lastPointPos = file.rfind( '.' );
		if( lastPointPos != std::string::npos )
		{
			return file.substr( lastPointPos + 1 );
		}
		return "";
	}

	static std::string ToLower( std::string& word )
	{
		std::string result(word);
		std::transform(word.begin(), word.end(), result.begin(), tolower);
		return result;
	}

	static std::vector<std::string> Split(const std::string &s, char delim) 
	{
		std::vector<std::string> elems;
		std::stringstream ss( s );
		std::string item;
		while ( std::getline( ss, item, delim ) ) 
		{
			elems.push_back( item );
		}
		return elems;
	}

};