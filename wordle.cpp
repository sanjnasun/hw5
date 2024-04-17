#ifndef RECCHECK
//  debugging
#include <iostream>
//  std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> finalString;
    std::string current = in;

    if (in.length() == 1 && in[0] != '-') { //one item fill
        finalString.insert(in);
        return finalString;
    }
    
    int dashCount = 0; //keep teh count of the dashes.
    int j = 0;
    while(j < in.size())
    {
      if(in[j] == '-')
      dashCount++;
      j++;
    }

    newCombo(current, in, dict, 0, floating, finalString, dashCount);
    
    return finalString;

}

//helps traverse and add the floating 
// void traverseInsert()

void newCombo(const std::string& current, const std::string& input, const std::set<std::string>& dict, size_t i, const std::string& floating, std::set<std::string>& finalString, int dashCount)
{

  if (i == input.size())
  {
      if (validWord(current, dict))
      {
          finalString.insert(current);
      }
      // std::cout << "Base case" << std::endl;
      return;
  }

  
  if (input[i] != '-') 
  {
    newCombo(current, input, dict, i + 1, floating, finalString, dashCount);
  }

  else {
    // std::cout << "Blank space" << std::endl;
    int floatingCount = floating.size();
    if (dashCount == floatingCount) 
    {
        for (size_t j = 0; j < floating.size(); j++) 
          {
              std::string newCurrent = current; 
              newCurrent[i] = floating[j];
              std::string newFloating = floating; 
              newFloating.erase(j, 1); 
              dashCount--;
              newCombo(newCurrent, input, dict, i + 1, newFloating, finalString, dashCount);
              dashCount++; 
          }
    } 

    else {
      for (char c = 'a'; c <= 'z'; ++c) {
          //bool foundInFloating = false;
          
            std::string newFloating = floating;
              if(floating.find(c)!=string::npos) 
              { 
                  // std::string newCurrent = current; 
                  // newCurrent[i] = floating[c];
                  size_t index = newFloating.find(c); 
                  newFloating.erase(index, 1);
              }


              std::string newCurrent = current;
              newCurrent[i] = c;
              newCombo(newCurrent, input, dict, i + 1, newFloating, finalString, dashCount - 1);
              //   break;


          // else {
          //     std::string newCurrent = current;
          //     newCurrent[i] = floating[c];
          //     newCombo(current, input, dict, i + 1, floating, finalString, dashCount-1);
          // }

        

      }

      // std::string newCurrent = current;
      // newCurrent[i] = '-';
    }
  }
}





// Define any helper functions here
bool validWord(const std::string& input, const std::set<std::string>& dict)
{
  //std::set<std::string>::iterator it;
  if(dict.find(input)!=dict.end()){
    return true;
  }

  return false;
}




