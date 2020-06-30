#include "parser.h"
#define LEN 1024

Parser::Parser(){
	
}

multiset<string> Parser::fileContents(ifstream &file){
	char buffer[LEN];
	while(1){
		file.getline(buffer, LEN);
		if(file.eof()) break;
		string s(buffer);
		contents.insert(s);
	}
	
	return contents;
}

Parser::~Parser(){

}
