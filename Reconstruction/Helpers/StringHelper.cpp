#include "stdafx.h"
#include "StringHelper.h"

namespace Helpers {

	StringHelper::StringHelper()
	{

	}
	
	StringHelper::~StringHelper()
	{
	}

	vector<string> StringHelper::Split(const string& str, const char& splitter)
	{
		string buffer("");
		vector<string> result;

		for (char n:str)
		{
			if (n != splitter) 
				buffer += n; 
			else
				if (n == splitter && buffer != "") {
					result.push_back(buffer);
					buffer = "";
				}
		}

		if (buffer != "")
			result.push_back(buffer);

		return result;
	}

	void StringHelper::Append(string & str, string newString)
	{
		str += newString;
	}	

	char StringHelper::ToUppercase(char str)
	{
		return str - ('a' - 'A');
	}

	char StringHelper::ToLowercase(char str)
	{
		return str + ('a' - 'A');
	}
}