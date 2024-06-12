#pragma once

#include <iostream>
#include <vector>

class clsString
{
private:
	bool _IsVowel(char letter_to_be_checked)
	{
		letter_to_be_checked = tolower(letter_to_be_checked);

		return ((letter_to_be_checked == 'a') || (letter_to_be_checked == 'e') || (letter_to_be_checked == 'i') ||
			(letter_to_be_checked == 'o') || (letter_to_be_checked == 'u'));
	}

	std::string _string_text;

public:
	clsString()
	{
		_string_text = "";
	}
	clsString(std::string string_text)
	{
		_string_text = string_text;
	}

	void SetStringText(std::string string_text)
	{
		_string_text = string_text;
	}
	std::string GetStringText()
	{
		return _string_text;
	}
	__declspec(property(get = GetStringText, put = SetStringText)) std::string string_text;

	static short CountWords(std::string str_to_be_counted, std::string delimiter = " ")
	{
		short counter = 0;
		short position = 0;

		std::string str_word;

		while ((position = str_to_be_counted.find(delimiter)) != std::string::npos)
		{
			str_word = str_to_be_counted.substr(0, position);

			if (!str_word.empty())
				counter++;

			str_to_be_counted.erase(0, position + delimiter.length());
		}

		if (!str_to_be_counted.empty())
			counter++;

		return counter;
	}
	short CountWords()
	{
		return CountWords(_string_text);
	}

	static short Length(std::string str_to_be_counted)
	{
		return str_to_be_counted.length();
	}
	short Length()
	{
		return Length(_string_text);
	}

	static std::string UpperFirstLetterOfEachWord(std::string str_to_be_modified)
	{
		bool is_first_letter = true;

		for (char& c : str_to_be_modified)
		{
			if (c != ' ' && is_first_letter)
				c = toupper(c);

			is_first_letter = (c == ' ' ? true : false);
		}

		return str_to_be_modified;
	}
	void UpperFirstLetterOfEachWord()
	{
		_string_text = UpperFirstLetterOfEachWord(_string_text);
	}

	static std::string LowerFirstLetterOfEachWord(std::string str_to_be_modified)
	{
		bool is_first_letter = true;

		for (char& c : str_to_be_modified)
		{
			if (c != ' ' && is_first_letter)
				c = tolower(c);

			is_first_letter = (c == ' ' ? true : false);
		}

		return str_to_be_modified;
	}
	void LowerFirstLetterOfEachWord()
	{
		_string_text = LowerFirstLetterOfEachWord(_string_text);
	}

	static std::string UpperAllString(std::string str_to_be_modified)
	{
		for (char& c : str_to_be_modified)
		{
			c = toupper(c);
		}

		return str_to_be_modified;
	}
	void UpperAllString()
	{
		_string_text = UpperAllString(_string_text);
	}

	static std::string LowerAllString(std::string str_to_be_modified)
	{
		for (char& c : str_to_be_modified)
		{
			c = tolower(c);
		}

		return str_to_be_modified;
	}
	void LowerAllString()
	{
		_string_text = LowerAllString(_string_text);
	}

	static std::string InvertAllLetterCase(std::string str_to_be_modified)
	{
		for (char& c : str_to_be_modified)
		{
			isupper(c) ? c = tolower(c) : c = toupper(c);
		}

		return str_to_be_modified;
	}
	void InvertAllLetterCase()
	{
		_string_text = InvertAllLetterCase(_string_text);
	}
	
	static short CountUpperLetters(std::string str_to_be_counted)
	{
		short counter = 0;

		for (char c : str_to_be_counted)
		{
			if (isupper(c))
				counter++;
		}

		return counter;
	}
	short CountUpperLetters()
	{
		return CountUpperLetters(_string_text);
	}

	static short CountLowerLetters(std::string str_to_be_counted)
	{
		short counter = 0;

		for (char c : str_to_be_counted)
		{
			if (islower(c))
				counter++;
		}

		return counter;
	}
	short CountLowerLetters()
	{
		return CountLowerLetters(_string_text);
	}

	static short CountAllLetters(std::string str_to_be_counted)
	{
		return CountUpperLetters(str_to_be_counted) + CountLowerLetters(str_to_be_counted);
	}
	short CountAllLetters()
	{
		return CountAllLetters(_string_text);
	}

	static short CountSpecificLetter(char letter_to_be_counted, std::string str_to_be_counted,
		bool must_be_match_case = true)
	{
		short counter = 0;

		if (!must_be_match_case)
		{
			str_to_be_counted = LowerAllString(str_to_be_counted);
			letter_to_be_counted = tolower(letter_to_be_counted);
		}

		for (char c : str_to_be_counted)
		{
			if (c == letter_to_be_counted)
				counter++;
		}

		return counter;
	}
	short CountSpecificLetter(char letter_to_be_counted, bool must_be_match_case = true)
	{
		return CountSpecificLetter(letter_to_be_counted, _string_text, must_be_match_case);
	}
	
	static short CountVowels(std::string str_to_be_counted)
	{
		clsString cls_string;
		short counter = 0;

		for (char c : str_to_be_counted)
		{
			if (cls_string._IsVowel(c))
				counter++;
		}

		return counter;
	}
	short CountVowels()
	{
		return CountVowels(_string_text);
	}

	static std::vector <std::string> Split(std::string str_to_be_splitted, std::string delimiter = " ")
	{

		std::vector <std::string> v_string;

		short position = 0;

		std::string str_word;

		while ((position = str_to_be_splitted.find(delimiter)) != std::string::npos)
		{
			str_word = str_to_be_splitted.substr(0, position);

			if (!str_word.empty())
				v_string.push_back(str_word);

			str_to_be_splitted.erase(0, position + delimiter.length());
		}

		if (!str_to_be_splitted.empty())
			v_string.push_back(str_to_be_splitted);

		return v_string;
	}
	std::vector <std::string> Split()
	{
		return Split(_string_text);
	}

	static std::string TrimLeft(std::string& string_to_be_trimmed, char delimiter = ' ')
	{
		for (short i = 0; i < string_to_be_trimmed.length(); i++)
		{
			if (string_to_be_trimmed[i] != delimiter)
			{
				return string_to_be_trimmed.substr(i, string_to_be_trimmed.length() - i);
			}
		}
	}
	void TrimLeft()
	{
		_string_text = TrimLeft(_string_text);
	}

	static std::string TrimRight(std::string string_to_be_trimmed, char delimiter = ' ')
	{
		for (short i = string_to_be_trimmed.length() - 1; i >= 0; i--)
		{
			if (string_to_be_trimmed[i] != delimiter)
			{
				return string_to_be_trimmed.substr(0, i + 1);
			}
		}
	}
	void TrimRight()
	{
		_string_text = TrimRight(_string_text);
	}

	static std::string Trim(std::string string_to_be_trimmed, char delimiter = ' ')
	{
		return TrimRight(TrimLeft(string_to_be_trimmed));
	}
	void Trim()
	{
		_string_text = Trim(_string_text);
	}

	std::string JoinString(std::vector <std::string> v_string, std::string delimiter = " ")
	{
		std::string joined_string = "";
		
		for (std::string s : v_string)
		{
			joined_string += s + delimiter;
		}

		return joined_string;
	}

	static std::string ReverseWordsInString(std::string string_to_be_reversed)
	{

		std::vector <std::string> v_string;
		std::string str_reversed = "";

		v_string = Split(string_to_be_reversed);

		std::vector <std::string>::iterator iter = v_string.end();

		while (iter != v_string.begin())
		{

			--iter;

			str_reversed += *iter + " ";

		}

		str_reversed = str_reversed.substr(0, str_reversed.length() - 1);

		return str_reversed;
	}
	void ReverseWordsInString()
	{
		_string_text = ReverseWordsInString(_string_text);
	}

	static std::string ReplaceWord(std::string string_to_be_modified, std::string string_to_be_replaced,
		std::string replace_to, bool must_be_match_case = true)
	{
		clsString cls_string;

		std::vector <std::string> v_string = Split(string_to_be_modified);

		for (std::string& s : v_string)
		{
			if (!must_be_match_case)
			{
				if (LowerAllString(s) == LowerAllString(string_to_be_replaced))
					s = replace_to;
			}
			else
			{
				if (s == string_to_be_replaced)
					s = replace_to;
			}
		}

		return cls_string.JoinString(v_string);
	}
	void ReplaceWord(std::string str_to_be_replaced, std::string replace_to, bool must_be_match_case = true)
	{
		_string_text = ReplaceWord(_string_text, str_to_be_replaced, replace_to, must_be_match_case);
	}

	static std::string RemovePunctuations(std::string string_to_be_modified)
	{
		std::string string_modified = "";

		for (char& c : string_to_be_modified)
		{
			if (!ispunct(c))
				string_modified += c;
		}

		return string_modified;
	}
	void RemovePunctuations()
	{
		_string_text = RemovePunctuations(_string_text);
	}
};

