#include "porterRules.h"
#include <iostream>

const char VOWEL[5] = {'a','e','i','o','u'};
const std::string DOUBLES[9] = {"bb", "dd", "ff", "gg", "mm", "nn", "pp", "rr","tt"};
const char LI_ENDING[10] = {'c', 'd', 'e', 'g', 'h', 'k', 'm', 'n', 'r', 't'};
const char SHORTS[3] =  {'w','x','y'};
const char ION_ENDING[2] = {'s', 't'};
const std::string LY_ENDING[3] = {"at","bl","iz"};

bool isVowel(const std::string& str, const int& i)
{
	for(unsigned int ii = 0; ii < sizeof(VOWEL)/sizeof(*VOWEL); ii++)
	{
		if(str[i] == VOWEL[ii])
		{
			return true;
		}	
	}

	if (str[i] =='y')
	{
		if( i == 0 or isVowel(str, i-1) )
		{
			return false;
		}else{
			return true;
		}
	}

	return false;
}

bool isIonEnding(const std::string& str)
{
	for(unsigned int i = 0; i < sizeof(ION_ENDING)/sizeof(*ION_ENDING); i++)
	{
		if (str.back() ==ION_ENDING[i])
		{
			return true;
		}
	}
	return false; 
}

bool isLyEnding(const std::string& str)
{
	for(unsigned int i = 0; i < sizeof(LY_ENDING)/sizeof(*LY_ENDING); i++)
	{
		if (containedBy(str, LY_ENDING[i]) )
		{
			return true;
		}
	}
	return false; 
}

std::string returnRegion1(const std::string& str)
{

	// d e f i n i t i o n
	// 0 1 2 3 4 5 6 7 8 9


	bool flag = false;
	for(unsigned int i = 0; i < str.size(); i++)
	{
		if( isVowel(str, i) )
		{
			flag = true;
		}

		if(!isVowel(str,i) and flag)
		{
			return str.substr(i+1,str.size());
		}
	}
	return "";
}

std::string returnRegion2(const std::string& str)
{
	std::string region1 = returnRegion1(str);
	int cutoff = str.size() - region1.size();

	bool flag = false;
	for(unsigned int i = cutoff; i < str.size(); i++)
	{

		if( isVowel(str, i) )
		{
			flag = true;
		}

		if(!isVowel(str,i) and flag)
		{
			return str.substr(i+1,str.size());
		}
	}

	return "";
}

bool isDouble(const std::string& str)
{
	std::string lastTwo;
	for(unsigned int i = 0; i < sizeof(DOUBLES)/sizeof(*DOUBLES); i++)
	{
		lastTwo = str.substr(str.size()-2, str.size());
		if(!lastTwo.compare(DOUBLES[i]))
		{
			return true;
		}
	}
	return false;
}

bool isLiEnding(const std::string& str, const int& i)
{
	for (unsigned int ii = 0; ii < sizeof(LI_ENDING)/sizeof(*LI_ENDING); ii++)
	{
		if(str[i] == LI_ENDING[ii])
		{
			return true;
		}
	}
	return false;
}

bool isShortSyllable(const std::string& str)
{

	if(str.size() <= 2)
	{
		if( isVowel(str,0) and !isVowel(str,1) )
		{
			return true;
		}
	} else {
		//std::cout << "1: " << str[str.size()-3]<< " 2: " << str[str.size()-2] << " 3: " << str[str.size()-1] << std::endl;
		if(!isVowel(str,str.size()-3) and isVowel(str,str.size()-2) and !isVowel(str,str.size()-1))
		{
			for(unsigned int i = 0; i < sizeof(SHORTS)/sizeof(*SHORTS); i++)
			{
				if(str.back() == SHORTS[i])
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool isShort(const std::string& str)
{
	std::string region1 = returnRegion1(str);
	if( isShortSyllable(str) and (!region1.compare("")) )
	{
		return true;
	} else {
		return false;
	}
}

bool containsVowelBeforeLastChar(const std::string& str)
{
	for (unsigned int i = 0; i < str.size() - 1; i++)
	{
		if( isVowel(str, i) )
		{
			return true;
		}
	}
	return false;
}

bool containsVowel(const std::string& str)
{
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if( isVowel(str, i) )
		{
			return true;
		}
	}
	return false;
}

bool containedBy(const std::string& str1, const std::string& str2)
{
	if(str1.size() == str2.size()){
		if(str1.compare(str2) == 0){
			return true;
		}
	}

	int cutoff = str1.size() - str2.size();
	if (cutoff > 0 )
	{
		return !str2.compare(str1.substr(cutoff, str1.size()));
	}else{
		return false;
	}
}

void stepOne(std::string& str)
{
	const std::string suffixes[3] = {"\'s\'","\'s","\'"};
	const std::string replacements[3] = {"","",""};
	
	std::string preceder;
	std::string suffix;

	unsigned int cutoff;

	if (str[0] == '\'')
	{
		str = str.substr(1,str.size());
	}

	for(unsigned int i = 0; i < sizeof(suffixes)/sizeof(*suffixes); i++)
	{
		cutoff = str.size() - suffixes[i].size();

		if (cutoff < str.size())
		{
			suffix = str.substr(cutoff, str.size());
			preceder = str.substr(0, cutoff);

			if ( !suffix.compare(suffixes[i]) )
			{
				str.replace(cutoff ,str.size(), replacements[i]);
				break;
			}
		}
	}
}
void stepTwo(std::string& str)
{
	const std::string suffixes[6] = 	{"sses",	"ied",	"ies",	"us",	"ss",	"s"};
	const std::string replacements[9] = {"ss",		"i",	"i",	"us",	"ss",	""};

	std::string preceder;
	std::string suffix;

	int cutoff;

	for(unsigned int i = 0; i < sizeof(suffixes)/sizeof(*suffixes); i++)
	{
		if( containedBy(str, suffixes[i]) )
		{
			cutoff = str.size() - suffixes[i].size();
			suffix = str.substr(cutoff, str.size());
			preceder = str.substr(0, cutoff);

			if (i == 1 or i == 2)
			{
				if( preceder.size() > 1)
				{
					str.replace(cutoff ,str.size(), replacements[i] );
					break;
				}else{
					str.replace(cutoff ,str.size(), "ie");
					break;
				}
			}else if (i == 5){
				
				if(containsVowelBeforeLastChar(preceder))
				{
					str.replace(cutoff ,str.size(), replacements[i]);
					break;
				} else {
					break;
				}
			}else{
				str.replace(cutoff ,str.size(), replacements[i]);
				break;
			}
		}
	}
}

void stepThree(std::string& str)
{
	//std::cout << str << std::endl;
	const std::string suffixes[6] = 	{"eedly",	"ingly",	"edly",	"eed",	"ing",	"ed"};
	const std::string replacements[6] = {"ee",		"",			"",		"ee",	"",		""};

	std::string preceder;
	std::string suffix;

	std::string region1 = returnRegion1(str);

	bool flag = false;
	int cutoff;
	for(unsigned int i = 0; i < sizeof(suffixes)/sizeof(*suffixes); i++)
	{

		if (containedBy(str, suffixes[i])){

			cutoff = str.size() - suffixes[i].size();
			suffix = str.substr(cutoff,str.size());
			preceder = str.substr(0,cutoff);

			if( i == 0 )
			{
				if(containedBy(region1, suffix))
				{
					str.replace(cutoff ,str.size(), replacements[i]);
					break;
				}else{
					break;
				}
			}

			if ( i == 3)
			{
				if(containedBy(region1, suffix))
				{
					str.replace(cutoff ,str.size(), replacements[i]);
					break;
				}else{
					break;
				}
			}

			if(containsVowel(preceder))
			{
				str.replace(cutoff ,str.size(), replacements[i]);
				flag = true;
				break;	
			}else{
				break;
			}

		}
	}

	if(flag)
	{
		//std::cout << "isShort? " << isShort(preceder) << std::endl;
		if(isLyEnding(preceder))
		{
			str = str + "e";
		}

		if(isDouble(preceder))
		{
			str = str.substr(0,str.size()-1);
		}
		if(isShort(preceder))
		{
			str = str + "e";
		}
	}
}

void stepFour(std::string& str)
{

	const std::string suffixes[1] = {"y"};
	const std::string replacements[1] = {"i"};
	std::string preceder;
	std::string suffix;
	int cutoff;

	for(unsigned int i = 0; i < sizeof(suffixes)/sizeof(*suffixes); i++)
	{

		if (containedBy(str, suffixes[i])){
			cutoff = str.size() - suffixes[0].size();
			suffix = str.substr(cutoff,str.size());
			preceder = str.substr(0,cutoff);

			if (!isVowel(preceder,preceder.size()-1) and preceder.size() > 1 )
			{
				str.replace(cutoff ,str.size(), replacements[i]);
				break;
			}
		}
	}
}

void stepFive(std::string& str)
{
	const std::string suffixes[24] = {"ational"	, "ousness"	, "iveness"	, "ization"	, "fulness"	, "tional"	, "biliti"	, "lessli"	, "alism"	,"ousli"	,"iviti"	,"fulli"	,"entli"	,"ation"	,"aliti"	,"enci"		,"anci"		,"abli"	,"izer"	,"ator"	,"alli"	,"bli"	,"ogi"	,"li"};
	const std::string replacements[24] = {"ate"		, "ous"		, "ive"		, "ize"		, "ful"		, "tion"	, "ble"		, "less"	, "al"		,"ous"		,"ive"		,"ful"		, "ent"		, "ate"		,"al"		,"ence"		,"ance"		,"able"	,"ize"	,"ate"	,"al"	,"ble"	,"og"	,""};
	std::string preceder;
	std::string suffix;
	int cutoff;
	
	for(unsigned int i = 0; i < sizeof(suffixes)/sizeof(*suffixes); i++)
	{

		if (containedBy(str, suffixes[i]))
		{
			cutoff = str.size() - suffixes[i].size();
			suffix = str.substr(cutoff, str.size());
			preceder = str.substr(0, cutoff);

			if(i == 22){
				if(preceder.back() == 'l')
				{
					str.replace(cutoff ,str.size(), replacements[i]);
					break;
				}

			}else if (i == 23){
				if(isLiEnding(preceder, preceder.size()-1))
				{
					str.replace(cutoff ,str.size(), replacements[i]);
					break;
				}

			}else{
				str.replace(cutoff ,str.size(), replacements[i]);
				break;
			}
			
		}
	}
}

void stepSix(std::string& str)
{
	const std::string suffixes[9] = 	{"ational", "tional", 	"alize", 	"icate", 	"iciti", 	"ative", 	"ical",		"ness",		"ful"};
	const std::string replacements[9] = {"ate", 	"tion", 	"al", 		"ic", 		"ic", 		"", 		"ic",			"",			""};
	std::string preceder;
	std::string suffix;
	std::string region1 = returnRegion1(str);
	std::string region2 = returnRegion2(str);
	int cutoff;


	for(unsigned int i = 0; i < sizeof(suffixes)/sizeof(*suffixes); i++)
	{
		if ( containedBy(str, suffixes[i]) )
		{
			cutoff = str.size() - suffixes[i].size();
			suffix = str.substr(cutoff, str.size());
			preceder = str.substr(0, cutoff);

			if (i != 5)
			{
				if( containedBy(region1, suffixes[i]) ){
					str.replace(cutoff ,str.size(), replacements[i]);
					break;
				}else{
					break;
				}
			}
		

			if ( i == 5 )
			{
				if( containedBy(region2, suffixes[i]) ){
					str.replace(cutoff ,str.size(), replacements[i]);
					break;
				}else{
					break;
				}
			}
		}

	}
}

void stepSeven(std::string& str)
{

	const std::string suffixes[18] = {"ement", "ment", "ance", "ence", "able", "ible", "ant", "ent", "ism", "ate", "iti", "ous", "ive", "ize" ,"ion", "al", "er", "ic"};
	const std::string replacements[18] = {"","","","","","","","","","","","","","","","","",""};
	std::string preceder;
	std::string suffix;

	std::string region1 = returnRegion1(str);
	std::string region2 = returnRegion2(str);

	int cutoff;

	for(unsigned int i = 0; i < sizeof(suffixes)/sizeof(*suffixes); i++)
	{
		if ( containedBy(str, suffixes[i]))
		{
			if (containedBy(region2, suffixes[i]) )
			{
				cutoff = str.size() - suffixes[i].size();
				suffix = str.substr(cutoff, str.size());
				preceder = str.substr(0, cutoff);

				if( i != 14)
				{
					str.replace(cutoff, str.size(), replacements[i]);
					break;
				}

				if (i == 14 and isIonEnding(preceder) )
				{
					str.replace(cutoff, str.size(), replacements[i]);
					break;
				}
			} else {
				break;
			}
		}
	} 
}

void stepEight(std::string& str)
{
	
	const std::string suffixes[2] = {"e", "l"};
	const std::string replacements[2] = {"",""};
	std::string preceder;
	std::string suffix;

	std::string region1 = returnRegion1(str);
	std::string region2 = returnRegion2(str);

	int cutoff;

	for(unsigned int i = 0; i < sizeof(suffixes)/sizeof(*suffixes); i++)
	{

		if (containedBy(str, suffixes[i]))
		{
			cutoff = str.size() - suffixes[i].size();
			preceder = str.substr(0, cutoff);
			suffix = str.substr(cutoff, str.size());
		

			if ( i == 0 and ( containedBy(region2, suffixes[i])  or ( containedBy(region1, suffixes[i]) and !isShortSyllable(preceder) ) ) ) {
				str.replace(cutoff, str.size(), replacements[i]);
				break;
			}

			if (i == 1 and containedBy(region2, suffixes[i]) and preceder.back() == 'l')
			{
				str.replace(cutoff, str.size(), replacements[i]);
				break;
			}
		}	
	}
}

void porter_process(std::string& str)
{
	stepOne(str);
	stepTwo(str);
	stepThree(str);
	stepFour(str);
	stepFive(str);
	stepSix(str);
	stepSeven(str);
	stepEight(str);
}

// int main(int argc, char **argv){
// 	std::string str = argv[1];
// 	std::cout << "isShortSyllable: " << isShortSyllable("quit") <<  std::endl;
// 	std::cout << "isContainedBy: " << containedBy("e","e") <<  std::endl;
// 	std:: cout << "Region 1: " << returnRegion1(str) << std::endl;
// 	std:: cout << "Region 2: " << returnRegion2(str) << std::endl;
	
// 	stepOne(str);
// 	std::cout << str << std::endl;

// 	stepTwo(str);
// 	std::cout << str << std::endl;

// 	stepThree(str);
// 	std::cout << str << std::endl;

// 	stepFour(str);
// 	std::cout << str << std::endl;

// 	stepFive(str);
// 	std::cout << str << std::endl;

// 	stepSix(str);
// 	std::cout << str << std::endl;

// 	stepSeven(str);
// 	std::cout << str << std::endl;

// 	stepEight(str);
// 	std::cout << str << std::endl;
// }