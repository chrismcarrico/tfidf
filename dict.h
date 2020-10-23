#ifndef DICT_H_
#define DICT_H_

#include <string>
#include <unordered_map>
#include <iostream>

class dict
{
	private:

		std::unordered_map<std::string, int> _counts;
		std::unordered_map<std::string, double> _scores;

		double _wordCount;
		double _letterCount;
		double _sentenceCount;

		inline void addElement(const std::string& str) { _counts.insert(std::make_pair(str, 1)); _scores.insert(std::make_pair(str, 0.00)); }
		inline void updateCount(const std::string& str, const int& count) { _counts.at(str) += count; }

	public:
		dict(){ _wordCount = 0; _letterCount = 0; _sentenceCount = 0; }

		bool isEmpty(){return _counts.empty(); }
		bool checkZeros(){ return (_wordCount == 0); }

		int getCount(const std::string& str) { try {return _counts.at(str); } catch (...) { return -1; } }
		double getScore(const std::string& str) { try {return _scores.at(str); } catch (...) { return -1; } }
		int getSize() { return _scores.size(); }

		double getWordCount() {return _wordCount; }
		double getLetterCount() {return _letterCount; }
		double getSentenceCount() {return _sentenceCount; }

		void incWordCount(int c) { _wordCount += c; }
		void incLetterCount(int c) { _letterCount += c; }
		void incSentenceCount(int c) { _sentenceCount += c; }

		double calcCL();

		std::unordered_map<std::string, int> getAllCounts(){ return _counts; };
		std::unordered_map<std::string, double> getAllScores(){ return _scores; };

		void handleStr(const std::string& str, const int& count = 1);
		void delElement(const std::string& str) { _counts.erase(str); _scores.erase(str); };
		void updateScore(const std::string& str, const double& score) { _scores.at(str) = score; }
		void printDict();

};


#endif
