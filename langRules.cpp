#include "langRules.h"
#include <iostream>

const char END_OF_SENTENCE[3] =  {'.','!','?'};

bool isLegalPunctuation(const std::string& str, const int& i)
{
	return ( (isProperPeriod(str, i)) or (isProperComma(str, i)) or (isProperApostrophe(str, i)) ); 
}

bool isPorterEligible(const std::string& str) 
{ 
	return ( !(str[0] == '+') and !lessThanTwoLetters(str) and !containsCapitals(str) and !containsNums(str) ); 
}

bool isAcronym(const std::string& str)
{
	for(unsigned int i = 1; i < str.size(); i++){
		if(isupper(str[i]))
		{
			return true;
		}
	}
	return false;
}

bool containsNums(const std::string& str)
{
	for(unsigned int i = 0; i < str.size(); i++)
	{
		if(isdigit(str[i])){
			return true;
		}
	}
	return false;
}

bool containsCapitals(const std::string& str)
{
	for(unsigned int i = 0; i < str.size(); i++){
		if(isupper(str[i]))
		{
			return true;
		}
	}
	return false;
}

bool isStartofSentence(const std::string& prev, const std::string& cur)
{
	for(unsigned int i = 0; i < cur.size(); i++) // if cur is punctuation its not the start of sentence
	{
		if ( !isalnum(cur[i]) )
		{
			return false;	
		}
	}

	if (prev == "") //if start of file its the start of sentence
	{
		return true;
	}

	return isSentenceEndingPunc(prev);
}

bool isSentenceEndingPunc(const std::string& prev)
{
	bool flag = false;
	for(unsigned int i = 0; i < prev.size(); i++) //if last word had punctuation
	{
		for(unsigned int j = 0; j < sizeof(END_OF_SENTENCE)/sizeof(*END_OF_SENTENCE); j++)
		{
			if(isalnum(prev[i])){
				return false;
			}

			if (prev[i] == END_OF_SENTENCE[j])
			{
				flag = true;
			}
		}
	}

	return flag;
}

bool isProperComma(const std::string& str, const int& i)
{
	try
	{

		if(str[i] != ',')
		{
			return false;
		}
		

		if ( isdigit(str[i-1]) and isdigit(str[i+1]) )
		{
			return true; //there is a number before and after
		}
	

		return false;
	
	} catch (std::out_of_range){
		return false; //The string ends after or before the comma
	}
	return false;
}

bool isProperPeriod(const std::string& str, const int& i)
{
	try{
		if (str[i] != '.'){
			return false;
		}

		if ((i == 0) and (isdigit(str[i+1]))){
			return true;	// [whitespace].[num]
		}

		if (isdigit(str[i-1]) and isdigit(str[i+1])){
				return true; //[num].[num]
		}

		return false; 
	} catch (std::out_of_range) { 
		return false; //either start of file or end of file
	}
	return false;
}

bool isPunctuationString(const std::string& str)
{
	for(unsigned int i = 0; i < str.size(); i++)
	{
		if ( (isalnum(str[i]) or (str[i] == '\'') ) ){
			return false;
		}
	}
	return true;
}

bool handleCaps(std::string& cur, const std::string& prev)
{
	
	if ( isupper(cur[0]) and !isAcronym(cur) and !containsNums(cur) )
	{
		
		 if ( isStartofSentence(prev, cur) )
		 	return true;
		// {
		// 	cur = "+" + cur;
		// }
		
	}	
	return false;
}
