#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft()


void LeafNode::addToRight(int value, int last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()


void LeafNode::addToThis(int value)
{
  int i;

  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()


void LeafNode::addValue(int value, int &last)
{
  int i;

  if(value > values[count - 1])
    last = value;
  else
  {
    last = values[count - 1];

    for(i = count - 2; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];
    // i may end up at -1
    values[i + 1] = value;
  }
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
  if(count > 0)  // should always be the case
    return values[count - 1];
  else
    return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int last;

  if(count < leafSize)
  {
    addToThis(value);
    return NULL;
  } // if room for value

  addValue(value, last);

  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addToLeft(last);
    return NULL;
  }  // if can insert into leftSibling
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
    {
      addToRight(value, last);
      return NULL;
    }  // if can insert into rightSibling
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()

void LeafNode::simpleRemove(int pos)
{
  count--;

  for (int i = pos; i < count; ++i)
    values[i] = values[i + 1];
}//

void LeafNode::borrowFromLeft()
{
  int leftMax = leftSibling->getMaximum();
  leftSibling->remove(leftMax);
  count++;
  for (int i = count - 1; i > 0; --i)
    values[i] = values[i - 1];
  values[0] = leftMax;
  
}//

void LeafNode::mergeToLeft()
{
  for (int i = 0; i < count; ++i)
    leftSibling->insert(values[i]);

  count = 0;
}//

void LeafNode::borrowFromRight()
{
  int rightMin = rightSibling->getMinimum();
  rightSibling->remove(rightMin);
  values[count] = rightMin;
  count++;
}//

void LeafNode::mergeToRight()
{
  for (int i = 0; i < count; ++i)
    rightSibling->insert(values[i]);

  count = 0;
}//

LeafNode* LeafNode::remove(int value)
{   // To be written by students
  int i;

  for (i = 0; i < count && values[i] != value; ++i);

  if (i < count)
    simpleRemove(i);

  if (count >= 0 && count < (leafSize + 1 ) / 2)
  {
    if (leftSibling)
      if (leftSibling->getCount() > (leafSize + 1 ) / 2)
        borrowFromLeft();
      else
      {
        mergeToLeft();
        leftSibling->setRightSibling(rightSibling);
        if (rightSibling)
          rightSibling->setLeftSibling(leftSibling);
        return this;
      }
    else // no leftSibling
      if (rightSibling)
        if (rightSibling->getCount() > (leafSize + 1 ) / 2)
          borrowFromRight();
        else
        {
          mergeToRight();
          rightSibling->setLeftSibling(leftSibling);
          return this;
        }
      else // no left and right siblings, it is root
        ;
  }

  return NULL;  // filler for stub
}  // LeafNode::remove()



LeafNode* LeafNode::split(int value, int last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()

