#include <iostream>
#include <fstream>
#include <set>
#include <iomanip>
#include "parser.h"
using namespace std;

typedef multiset<string>::iterator mit;
typedef set<string>::iterator it;

int main(){

	ifstream file("input.txt");
	Parser *parser = new Parser();
	multiset<string> contents = parser->fileContents(file);
	set<string> s;
	for(mit i = contents.begin(); i != contents.end(); i++){
		s.insert(*i);
	}
	
	for(it i = s.begin(); i != s.end(); i++){
		double percentage = (double) contents.count(*i) / contents.size() * 100;
		cout << fixed;
		cout << setprecision(4);
		cout << *i << "\t\t" << percentage << "%" << endl;
	}
	
	
	delete parser;
	file.close();
	return 0;
}
