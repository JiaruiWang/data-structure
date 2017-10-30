#include <iostream>
#include <fstream>
#include <string>

#include "CPUTimer.h"
#include "dsexceptions.h"
#include "LinkedList.h"
#include "StackAr.h"
#include "CursorList.h"
#include "QueueAr.h"
#include "StackLi.h"
#include "vector.h"
#include "SkipList.h"

using namespace std;

const static int MAX = 500001;
vector<CursorNode<int> > cursorSpace(MAX);

void RunList(string &s)
{
  List<int> list;
  char op, space;
  int num;
  string info;
  ifstream inf(s);
  getline(inf, info);

  while (inf >> op >> num)
  {
    if (op == 'i')
      list.insert(num, list.zeroth());
    else
      list.remove(num);
  }//

  inf.close();
}//

void RunCursorList(string &s)
{
  CursorList<int> list(cursorSpace);
  char op, space;
  int num;
  string info;
  ifstream inf(s);
  getline(inf, info);

  while (inf >> op >> num)
  {
    if (op == 'i')
      list.insert(num, list.zeroth());
    else
      list.remove(num);
  }//

  inf.close();
} //

void RunStackAr(string &s)
{
  StackAr<int> stack(MAX);
  char op, space;
  int num;
  string info;
  ifstream inf(s);
  getline(inf, info);

  while (inf >> op >> num)
  {
    if (op == 'i')
      stack.push(num);
    else
      stack.pop();
  }//

  inf.close();
}//

void RunStackLi(string &s)
{
  StackLi<int> stack;
  char op, space;
  int num;
  string info;
  ifstream inf(s);
  getline(inf, info);

  while (inf >> op >> num)
  {
    if (op == 'i')
      stack.push(num);
    else
      stack.pop();
  }//

  inf.close();
}//

void RunQueueAr(string &s)
{
  Queue<int> queue(MAX);
  char op, space;
  int num;
  string info;
  ifstream inf(s);
  getline(inf, info);

  while (inf >> op >> num)
  {
    if (op == 'i')
      queue.enqueue(num);
    else
      queue.dequeue();
  }//

  inf.close();
}//

void RunSkipList(string &s)
{
  SkipList<int> list(0, MAX);
  char op, space;
  int num;
  string info;
  ifstream inf(s);
  getline(inf, info);

  while (inf >> op >> num)
  {
    if (op == 'i')
      list.insert(num);
    else
      list.deleteNode(num);
  }//

  inf.close();  
}//

int getChoice()
{
  cout << "\n      ADT Menu\n0. Quit\n1. LinkedList\n";
  cout << "2. CursorList\n3. StackAr\n4. StackLi\n";
  cout << "5. QueueAr\n6. SkipList\nYour choice >> ";

  int choice;
  cin >> choice;
  return choice;
}

int main(int argc, char const *argv[])
{ 
  int choice;
  CPUTimer ct;
  string filename;
  cout << "Filename >> ";
  getline(cin, filename);

  do
  {
    choice = getChoice();
    ct.reset();
    switch (choice)
    {
      case 1: RunList(filename); break;
      case 2: RunCursorList(filename); break;
      case 3: RunStackAr(filename); break;
      case 4: RunStackLi(filename); break;
      case 5: RunQueueAr(filename); break;
      case 6: RunSkipList(filename); break;
    } //

    cout << "CPU time: " << ct.cur_CPUTime() << endl;
  } while(choice > 0);

  return 0;
}