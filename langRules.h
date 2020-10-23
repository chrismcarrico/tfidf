#ifndef LANGRULES_H_
#define LANGRULES_H_

#include <string>
#include <stdexcept>


bool isAcronym(const std::string& str);
bool containsCapitals(const std::string& str);
bool containsNums(const std::string& str);
bool isPorterEligible(const std::string& str);
bool isStartOfSentence( std::string str);
bool isProperComma(const std::string& str, const int& i);
bool isProperPeriod(const std::string& str, const int& i);
inline bool lessThanTwoLetters(const std::string& str){ return (str.size() <= 2); }
inline bool isProperApostrophe(const std::string& str, const int& i) { return ( str[i] == '\'' ); }
bool isLegalPunctuation(const std::string& str, const int& i);
bool isPunctuationString(const std::string& str);
bool isSentenceEndingPunc(const std::string& prev);

bool handleCaps(std::string& cur, const std::string& prev);

#endif
