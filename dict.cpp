#include "dict.h"

void dict::handleStr(const std::string& str, const int& count)
{
	if (getCount(str) > 0)
	{
		updateCount(str, count);
	} else {
		addElement(str);
	}
}

double dict::calcCL()
{	
	if( checkZeros() )
	{
		std::cerr << "[dict] Word Count is zero" << std::endl;
		exit(-1);
	}

	try{
		double L = _letterCount /( _wordCount )*100;
		double S =  _sentenceCount /( _wordCount )*100;
		return (0.0588*L - 0.296*S - 15.8); 

	} catch (...){
		std::cerr << "[dict] Divison by zero, likely caused by punctuation only file" << std::endl;
		exit(-1);
	}
}

// void dict::printDict()
// {
// 	dict n = *this;
// 	std::string next;
// 	int i = 0;

// 	while ( i < getSize())
// 	{
// 		next = n._counts.begin()->first;

// 		for (auto itr = n._counts.begin(); itr != n._counts.end(); ++itr)
// 		{
// 			if( (itr->first).compare(next) < 0 ){
// 				next = itr -> first;
// 			}
// 		}
// 		std::cout<< next << " " << n._counts.at(next) << std::endl;
// 		n.delElement(next);
// 		i++;
// 	}
// }

// int main()
// {
// 	dict d = dict();
// 	d.handleStr("Hello");
// 	d.handleStr("world", 2);
// 	std::cout << d.getCount("Hello") << std::endl;
// 	std::cout << d.getCount("world") << std::endl;
// 	d.handleStr("world");
// 	d.handleStr("world");
// 	std::cout << d.getCount("world") << std::endl;
// 	d.handleStr("Hello", 2);
// 	std::cout << d.getCount("Hello") << std::endl;
// 	return 0;

// }
