#pragma once
#include <cassert>
#include <iostream>

class String;

int strLen(const char* str);

std::ostream& operator << (std::ostream& streamP, const String& string);

class String
{
	char* str;
	int memorySize;
	int strSize;

public:

	String()
	{
		memorySize = 1;
		strSize = 1;
		str = new char[memorySize];
		str[0] = '\0';
	}

	String(const char* strc)
	{
		assert(strc);
		strSize = strLen(strc) + 1;
		memorySize = 2 * strSize;
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = strc[i];
	}

	String(const char* strc, const int memorySizeP)
	{
		assert(strc);
		strSize = strLen(strc) + 1;
		assert(strSize < memorySizeP);
		memorySize = memorySizeP;
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = strc[i];
	}

	String(const String& string)
	{
		strSize = string.strSize;
		memorySize = 2 * strSize;
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = string.str[i];

		//std::cout << "constr1" << '\n';
	}

	String(const String& string, const int memorySizeP)
	{
		memorySize = memorySizeP;
		strSize = string.strSize;
		assert(strSize < memorySize);
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = string.str[i];

		//std::cout << "constr2" << '\n';
	}

	String(const int len)
	{
		strSize = len + 1;
		memorySize = 2 * strSize;
		str = new char[memorySize];
		str[len] = '\0';
	}

	String(const char ch)
	{
		strSize = 2;
		memorySize = 4;
		str = str = new char[memorySize];
		str[0] = ch;
		str[1] = '\0';
	}

	~String()
	{
		//std::cout << this->str  << '\n';

		delete[] str;

		//std::cout << "destr" << '\n';
	}

	const char operator [] (const int index) const
	{
		assert(index < this->len());        
		return str[index];
	}

	char& operator [] (const int index) 
	{
		assert(index < this->len());
		return str[index];
	}

	bool operator == (String string)
	{
		if (strSize != string.strSize)
		{
			return false;
		}
		for (int i = 0; i < this->len(); i++)
			if (str[i] != string[i])
				return false;
		return true;
	}

	bool operator != (String string)
	{
		if (*this == string)
			return false;
		return true;
	}

	String& operator = (const String& string)
	{
		//std::cout << "=" << '\n';

		int size = string.strSize;
		if (size > memorySize)
		{
			delete[] str;
			str = new char[2 * size];
			memorySize = 2 * size;
		}
		strSize = size;
		for (int i = 0; i < size - 1; i++)
		{
			str[i] = string[i];
		}
		str[size - 1] = '\0';
		return *this;
	}

	int len() const
	{
		return strSize - 1;
	}

	int countChar(char c) const
	{
		int i = 0;
		int count = 0;
		for (int i = 0; i < strSize; ++i)
			if (str[i] == c)
				count++;
		return count;
	}

	int findFirstOf(char c) const
	{
		int i = 0;
		while (str[i] != c)
			i++;
		return i;
	}

	String split(int index)
	{
		String string = String(strSize - index - 2);
		int n = index;
		for (int i = 0; i < strSize - n; ++i)
		{
			string.str[i] = str[i + n];
		}
		strSize = index + 1;
		str[index] = '\0';
		return string;
	}

	String operator + (const String& string) const
	{
		int size = strSize + string.len();
		String retStr (size);
		for (int i = 0; i < strSize - 1; ++i)
			retStr.str[i] = str[i];
		int n = strSize - 1;
		for (int i = 0; i < string.strSize; ++i)
			retStr.str[i + n] = string.str[i];
		return retStr;
	}

	void operator += (const String& string)     //????????
	{
		int size = strSize + string.len();
		if (size > memorySize)
		{
			char* newstr = new char[2 * size];
			memorySize = 2 * size;
			for (int i = 0; i < strSize - 1; ++i)
				newstr[i] = str[i];
			int n = strSize - 1;
			for (int i = 0; i < string.strSize; ++i)
				newstr[i + n] = string.str[i];
			delete[] str;
			str = newstr;
			strSize = size;
		}
		else
		{
			int n = strSize - 1;
			for (int i = 0; i < string.strSize; ++i)
				str[i + n] = string.str[i];
			strSize = size;
		}
	}

	

	char* c_str()                 // ???????????
	{
		return str;
	}


	bool foundStr(const char* strc)
	{
		assert(strc);

		int len_strc = strLen(strc);
		int* arr = new int[strSize];
		if (str[0] == strc[0])
			arr[0] = 1;
		else
			arr[0] = 0;
		for (int i = 1; i < strSize; ++i)
		{
			if (arr[i - 1] != len_strc)
			{

				if (str[i] == strc[arr[i - 1]])
				{
					arr[i] = arr[i - 1] + 1;
					continue;
				}
				if (str[i] == strc[0])
				{
					arr[i] = 1;
					continue;
				}
				else
				{
					arr[i] = 0;
					continue;
				}
			}
			delete[] arr;
			return true; //?????????????????????
		}
		for (int i = 0; i < strSize; ++i)
		{
			std::cout << str[i] << ' ' << arr[i] << std::endl;
		}
		if (arr[strSize - 2] == len_strc)
		{
			delete[] arr;
			return true;
		}
		delete[] arr;
		return false;
	}

	String copyPart(int begin, int end)
	{
		assert(end > begin);
		assert(end <= strSize);

		String name(end - begin - 1);

		for (int i = 0; i < (end - begin - 1); i++)
		{
			name[i] = (*this)[i + begin];
		}

		str[end - begin - 1] = '\0';

		return name;
	}
};

int strCount(char* str, char n);

String arrCharMerge(char* str1, char* str2);

