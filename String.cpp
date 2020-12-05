#pragma once
#include "String.h"

std::ostream& operator << (std::ostream& streamP, const String& string)
{
	for (int i = 0; i < string.len(); i++)
		streamP << string[i];
	return streamP;
}

int strCount(char* str, char n)
{
	int i = 0;
	int count = 0;
	while (true)
	{
		if (str[i] == '\0')
			return count;
		i++;
		if (str[i] == n)
		{
			count++;
		}
	}
}

String arrCharMerge(char* str1, char* str2)
{
	int len = strLen(str1) + strLen(str2) + 1;
	String string(len);
	for (int i = 0; i < strLen(str1); ++i)
	{
		string[i] = str1[i];
	}
	for (int i = 0; i < strLen(str2) + 1; ++i)
	{
		string[i + strLen(str1)] = str2[i];
	}
	return string;
}

int strLen(const char* str)
{
	int i = 0;
	while (true)
	{
		if (str[i] == '\0')
			return i;
		i++;
	}
}