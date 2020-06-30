#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<set>
#include<fstream>

using namespace std;

class Parser {
	public:
		Parser();
		multiset<string> fileContents(ifstream&);
		~Parser();
	private:		
		multiset<string> contents;
	
};

#include "parser.cpp"

#endif
