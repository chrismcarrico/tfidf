#include "dict.h"
#include "langRules.h"
#include "porterRules.h"
#include "eTable.h"
#include <unordered_map>
#include <math.h>
	
std::vector<dict> dicts;
eTable expTable = eTable();
std::unordered_map<std::string, double> freqTable;

void updateFreq(dict& d, const std::string str)
{
	try{
		if(d.getCount(str) == -1)
		{
			
			freqTable.at(str) += 1;
		}
	} catch (std::out_of_range){
			
		freqTable.insert(std::make_pair(str, 1));
	}
}

void process(dict& d, std::string& cur, std::string& prev, std::vector<std::string>& capStrings)
{	
	if ( !isPunctuationString(cur) )
	{
		d.incWordCount(1);
		d.incLetterCount( cur.size() );
	}

	if ( isSentenceEndingPunc(cur) )
	{
		d.incSentenceCount(1);
	}


	if( handleCaps(cur, prev) )
	{
		prev = cur;
		capStrings.push_back(cur);
	} else {

		if(isPorterEligible(cur)) 
		{ 
			if(expTable.check(cur))
			{
				prev = cur;
				cur = expTable.get(cur);
				updateFreq(d, cur);
				d.handleStr(cur); 
			} else { 
				prev = cur;
				porter_process(cur);
				updateFreq(d, cur);
				d.handleStr(cur); 
			}
		} else { 
			prev = cur;
			updateFreq(d, cur);
			d.handleStr(cur); 
		}
	}

	//std::cout << cur << " " << cur.size() << std::endl;



}

void processCaps(dict& d, std::string& cur)
{
	if(isPorterEligible(cur)) 
	{ 
		if(expTable.check(cur))
		{
			cur = expTable.get(cur);
			updateFreq(d, cur);
			d.handleStr(cur,1);
		} else { 
			porter_process(cur);
			updateFreq(d, cur);
			d.handleStr(cur,1); 
		}
	} else { 
		updateFreq(d, cur);
		d.handleStr(cur); 
	}
}

void condenseCaps(dict& d, std::vector<std::string>& capStrings)
{
	std::string str;
	for(unsigned int i = 0; i < capStrings.size(); i ++)
	{	
		str = capStrings.at(i);
		

		if( d.getCount(str) > 0)
		{	
			processCaps(d, str);
		}else{
			str[0] = tolower(str[0]);
			processCaps(d, str);
		}
	}
}

std::string readUntilSwitch(const std::string& str, unsigned int& i, bool& punc)
{
	std::string ret = "";
	ret += str[i];
	i++;

	if(punc)
	{
		while(i < str.size() ){
			if(isalnum(str[i]) or isLegalPunctuation(str, i))
			{
				punc = false;
				return ret;

			} else {
				ret += str[i];
				i += 1;
			}
		}

	}else{

		while(i < str.size())
		{
			if( !(isalnum(str[i]) or isLegalPunctuation(str, i)) )
			{
				punc = true;
				return ret;

			} else {
				ret += str[i];
				i += 1;
			}
		}
	}
	
	return ret;
}

void counter(dict&  d, std::string filename)
{

	std::ifstream file;
	file.open(filename);

  	if(!file.is_open()) // File doesn't open
	{
		std::cerr << "[main][counter] Invalid filename: " << filename << std::endl;
		exit(-1);
	}

	std::vector<std::string> capVec;

	std::string str;

	std::string cur;
	std::string prev = "";

	unsigned int i;
	bool punc;


	while (file >> str)
	{
		i = 0;
		punc = !(isalnum(str[i]) or isLegalPunctuation(str, i));

		while( i < str.size() )
		{
			cur = readUntilSwitch(str, i, punc);
			process(d, cur, prev, capVec);
		}

	}

	if(d.isEmpty())
	{
		std::cerr << "[main][counter] Empty File " << filename << std::endl;
		exit(-1);	
	}

	condenseCaps(d, capVec);

}

void calcTFIDF(dict& d, double N)
{	
	double score;
	double invFreq;
	std::string str;

	std::unordered_map<std::string, double> scores = d.getAllScores();
	std::unordered_map<std::string, double>::iterator itr = scores.begin();
 
// Iterate over the map using iterator
	while (itr != scores.end())
	{
		
		str = itr->first;
		
		if ( !isPunctuationString(str) )
		{
			
			invFreq = (double) N / ( freqTable.at(str) );
			score = (double) ( d.getCount(str) * (log10( invFreq ) ) );
		}else{
			score = 0;
		}

			
			d.updateScore(str, score);
			itr++;
		
	}
}

double calcSim(dict& d1, dict& d2)
{
	
	double scoreI, scoreII, sum;
	scoreI = scoreII = sum = 0;
	std::string key;

	if(d1.getSize() > d2.getSize())
	{
		std::unordered_map<std::string, double> scores = d1.getAllScores();
		std::unordered_map<std::string, double>::iterator itr = scores.begin();

		while( itr != scores.end() )
		{
			key = itr->first;
			scoreI = d1.getScore(key);

			if ( (scoreII = d2.getScore(key)) < 0)
				scoreII = 0;

			sum += scoreI*scoreII;

			itr++;
		}

	} else {

		std::unordered_map<std::string, double> scores = d2.getAllScores();
		std::unordered_map<std::string, double>::iterator itr = scores.begin();

		while( itr != scores.end() )
		{
			key = itr->first;
			scoreI = d2.getScore(key);

			if ( (scoreII = d1.getScore(key)) < 0)
				scoreII = 0;

			sum += scoreI*scoreII;

			itr++;
		}
	}

	return sum;
}

void printSim(int N)
{
	std::cout << std::fixed;
	std::cout.precision(2);
	 
	for(int i = 0; i < N; i++)
	{
		for(int ii = 0; ii < N; ii++)
		{
			std::cout << calcSim(dicts.at(i),dicts.at(ii))<< " ";
		}
		std::cout << std::endl;
	}
}


int main(int argc, char **argv)
{
	// ./PA8 [input file] [corpus] [double bottom] [double top]
	if(argc < 5)
	{
		std::cerr << "[main] Invalid number of arguments" << std::endl;
		return -1;
	}

	//Declare Variabls
	double low, high, max, score, sim;
	int index;
	std::vector<std::string> bgFiles;
	std::string input, filenames, filename;
	bool flag;

	//Initialize Variables
	low = atof(argv[3]);
	high = atof(argv[4]);

	if(low > high)
	{
		std::cerr << "[main] argv: " << argv[3] << " cannot be greater than argv: " << argv[4] << std::endl;
		exit(-1);
	}

	filenames = argv[2];
	input = argv[1];

	//Initialize dicts
	dict bigD = dict();
	counter(bigD, input);

	std::ifstream file;
	file.open(filenames);

  	if(!file.is_open()) // File doesn't open
	{
		std::cerr << "[main] Invalid filename: " << filename << std::endl;
		exit(-1);
	}

	file >> filename;
	expTable.initializeTable(filename);

	while (file >> filename)
	{	
		bgFiles.push_back(filename);
		dict d = dict();
		counter(d, filename);
		dicts.push_back(d);
	}

	calcTFIDF(bigD, bgFiles.size()+1 );

	index = max = 0;

	flag = false;
	for(unsigned int i = 0; i < dicts.size(); i++)
	{
		score = dicts.at(i).calcCL();
		//std::cout<< bgFiles.at(i) << " " << score << " " << (score > low and score < high)<< std::endl;
		if(score > low and score < high)
		{
			flag = true;
			calcTFIDF(dicts.at(i), bgFiles.size()+1);
			sim = calcSim(bigD, dicts.at(i));
			//std::cout << bgFiles.at(i) << " " << sim << " vs " << max << std::endl;

			if(sim > max)
			{
				max = sim;
				index = i;
			}
		}
	}

	if(!flag)
	{
		std::cerr << "[main] No documents in reading range" << std::endl;
		exit(-1);
	}

	std::cout << bgFiles.at(index) << std::endl; 
	return 0;
}
