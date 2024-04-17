// main() program to test your schedule function.
// Feel free to modify though it will be easiest to
// simply pass in different command line arguments to test
// various cases of words and letters.
// This file will not be graded. 
#include <iostream>
#include <set>
#include <string>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

int main(int argc, char* argv[])
{
   
    const std::set<std::string>& dict = readDictWords("dict-eng.txt");    
    string in(argv[1]);
    string floatingChars;
   
    if(argc > 2){
        floatingChars = argv[2];
    }
    
  	std::set<std::string> expected = {};

	for(char c = 'a'; c <= 'z'; c++)
	{
		for(char d = 'a'; d <= 'z'; d++) 
		{
			string temp;
			temp += c;
			temp += d;
			if(dict.find(temp) != dict.end())
			{
				expected.insert(temp);
			}
		}
	}

     cout << "Expected Set Contents:" << endl;
    for(const auto& word : expected) {
        cout << word << endl;
    }
  
    std::set<std::string> actual = wordle("--", "", dict);


    return 0;



}