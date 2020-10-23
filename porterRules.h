#ifndef PORTERRULES_H_
#define PORTERRULES_H_

#include <string>

std::string returnRegion1(const std::string& str);
std::string returnREgion2(const std::string& str);

bool containedBy(const std::string& str1, const std::string& str2);
bool isShortSyllable(const std::string& str);
bool isVowel(const std::string& str, const int& i);
bool isDouble(const std::string& str);
bool isLiEnding(const std::string& str);
bool isShort(const std::string& str);

void step1(std::string& str);
void step2(std::string& str);
void step3(std::string& str);
void step4(std::string& str);
void step5(std::string& str);
void step6(std::string& str);
void step7(std::string& str);
void step8(std::string& str);


void porter_process(std::string& str);

#endif