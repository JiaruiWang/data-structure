// Author: Sean Davis 
// Created on October 21, 2015, 5:54 AM

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <iomanip>

using namespace std;
#include "AvlTree.h"
class WordCount
{
  public:
    char *word;
    int *lines;
    int count;
    int size;
    bool operator<(const WordCount &rhs) const {return strcmp(word, rhs.word) < 0;}
    bool operator!= (const WordCount &rhs) const {return strcmp(word, rhs.word) != 0;}
    WordCount():lines(NULL), count(0), size(0) {word = new char[1]; word[0] = '\0';}
    WordCount(const WordCount &wc) : count(wc.count), size(wc.size)
    {
      word = new char[strlen(wc.word) + 1];
      strcpy(word, wc.word);
      lines = new int[size];

      for(int i = 0; i < count; i++)
        lines[i] = wc.lines[i];
    } // WordCount copy constructor

    friend ostream& operator<< (ostream &os, const WordCount &rhs);
   /* 
    WordCount& operator= (const WordCount &rhs)
    {
      if(this == &rhs)
        return *this;
      
      delete[] word;
      word = new char[strlen(rhs.word) + 1];
      strcpy(word, rhs.word);
      delete[] lines;
      lines = new int[rhs.size];
      for(int i = 0; i < rhs.count; i++)
        lines[i] = rhs.lines[i];
        
      count = rhs.count;
      size = rhs.size;
      
      return *this;
    }  // operator=
   */ 
    ~WordCount() 
    { 
      if(lines)
        delete[] lines;
      
      if(word)
        delete[] word;
  
    } // ~WordCount()
};

ostream& operator<< (ostream &os, const WordCount &rhs)
{
  os << setw(18) << left << rhs.word << rhs.count << "   ";
  for(int i = 0; i < rhs.count - 1; i++)
    os << rhs.lines[i] << ',';
  
  os << rhs.lines[rhs.count - 1];
  return os;
}


void readFile(const char *filename, AvlTree <WordCount> &tree)
{
  int lineCount = 1;
  char *ptr, *ptr2, line[10000];
  WordCount word, word2;
  delete [] word2.word;
  word2.word = new char[10000];
  delete [] word.word;
  word.word = new char[10000];
  word.lines = new int[10];
  ifstream inf(filename);
  
  while(inf.getline(line, 10000))
  {
    for(ptr = line; *ptr && !isalpha(*ptr); ptr++);
    
    while(*ptr)
    {
      
      for(ptr2 = ptr; isalpha(*ptr2); ptr2++)
        *ptr2 = tolower(*ptr2);
      
      char temp = *ptr2;
      *ptr2 = '\0';
      
      if(strlen(ptr) > 0)
      {
        strcpy(word2.word, ptr);
        WordCount &tempWord = tree.find(word2);
        
        if(tempWord.word[0] != '\0')
        {
          if(tempWord.count == tempWord.size)
          {
            int *tempLine = new int[tempWord.size * 2];
            
            for(int i = 0; i < tempWord.count; i++)
              tempLine[i] = tempWord.lines[i];
            
            delete [] tempWord.lines;
            tempWord.lines = tempLine;
            tempWord.size *= 2;
          }  // if we need to resize the lines
          
          tempWord.lines[tempWord.count++] =  lineCount;
        }
        else  // word not in tree
        {
          strcpy(word.word, ptr);
          word.count = 1;
          word.size = 10;
          word.lines[0] = lineCount;
          tree.insert(word);
        }
        
      }  // if a real word
        
      *ptr2 = temp;  
      for(ptr = ptr2; *ptr && !isalpha(*ptr); ptr++);
      
    }  // while more in line
    
    lineCount++;
  }  // while more lines

}  // readFile()


int main(int argc, char** argv) 
{
  WordCount word;
  AvlTree <WordCount> tree(word);
  readFile(argv[1], tree);
  tree.printTree();
  return 0;
} // main())

