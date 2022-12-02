// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //in green letters, floating yellow, dict = all english words
    std::set<string> words;
    std::queue<char> yellowQ;
    unsigned int lettersLeft = 0;
    for(unsigned int i = 0; i< in.size(); i++){
      if(in[i]=='-'){
        lettersLeft++;
      }
    }
    for(unsigned int i = 0; i<floating.size(); i++){
      yellowQ.push(floating[i]);
    }
    wordleHelper(in, yellowQ, dict, &words, lettersLeft, 0);
    return words;
}

void wordleHelper(
  const std::string& in,
  const std::queue<char>& floating,
  const std::set<std::string>& dict,
  std::set<std::string>*words,
  unsigned int lettersLeft,
  unsigned int position)
{
  std::queue<char> yellow = floating;
  std::string green = in;

  if(lettersLeft == 0){
      if(dict.find(in) != dict.end()){
        words->insert(in);
        return;
      }
    return;
  }

  if(in[position]=='-'){
    if(lettersLeft == yellow.size()){
      for(unsigned int i = 0; i<yellow.size(); i++){
        green[position] = yellow.front();
        yellow.pop();
        wordleHelper(green, yellow, dict, words, lettersLeft-1, position+1);
        yellow.push(green[position]);
     }
    }
    else{
      bool skip = false;
      for(char letter = 'a'; letter <= 'z'; letter++){
        for(unsigned int j = 0; j<yellow.size(); j++){
          if(yellow.front()==letter){
            skip = true;
            break;
          }
          else{
            yellow.push(yellow.front());
            yellow.pop();
          }
        }
        green[position] = letter;
        if(skip){
          yellow.pop();
          wordleHelper(green, yellow, dict, words, lettersLeft-1, position+1);
          yellow.push(letter);
          skip = false;
        }
        else{
          wordleHelper(green, yellow, dict, words, lettersLeft-1, position+1);
        }
      }
    }
  }
  else{
    wordleHelper(in, floating, dict, words, lettersLeft, position+1);
    return;
  }

}

// Define any helper functions here
