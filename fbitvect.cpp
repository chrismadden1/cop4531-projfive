/*
    fbitvect.cpp
    08/17/18
    Chris Lacher

    functionalty test of BitVector

    INTERACTIVE VERSION - command echo commented out

    Copyright 2009 - 2018, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bitvect.h>

// in lieu of a makefile (for command line creation of executable)
#include <bitvect.cpp>

void DisplayMenu (size_t size);
void CopyTest    (const fsu::BitVector& bv1, fsu::BitVector bv2);
void AssignTest  (const fsu::BitVector& bv1);

// typedef alt::BitVector BitVector;
typedef fsu::BitVector BitVector;

int main(int argc, char* argv[])
{
  std::cout << " ***********************************************************\n"
            << " * fbitvect.x command line arguments expected (optional):  *\n"
            << " *  1: size requested in bits [enter 0 for default]        *\n"
            << " *  2: command file for batch processing                   *\n"
            << " ***********************************************************\n";
  size_t size(0);
  if (argc > 1)
  {
    size = atoi(argv[1]);
  }

  std::ifstream ifs;
  std::istream* isptr = &std::cin;
  bool BATCH = 0;  

  if (argc > 2)
  {
    ifs.open(argv[2]);
    if (ifs.fail())
    {
      std::cout << " ** unable to read file \"" << argv[2] << "\"\n"
                << "    try again\n";
      return EXIT_FAILURE;
    }
    isptr = &ifs;
    BATCH = 1;
  }

  BitVector * bvptr;
  if (size == 0)
  {
    bvptr = new BitVector; // default constructor
  }
  else
  {
    bvptr = new BitVector (size); // 1-arg constructor
  }
  char selection;
  size_t index;
  std::cout << "Welcome to fbitvect\n";
  DisplayMenu(size);

  do
  {
    std::cout << "  Enter [op][index] (\'M\' for menu, \'Q\' to quit): ";
    *isptr >> selection;
    if (BATCH)  std::cout << selection; // echo input
    switch(selection)
    {
      case '=':
        if (BATCH)  std::cout << '\n'; // echo input
        CopyTest(*bvptr,*bvptr);
        AssignTest(*bvptr);
        break;
      case 'S':
        if (BATCH)  std::cout << '\n'; // echo input
        bvptr->Set();
        break;
      case 's':
        *isptr >> index;
        if (BATCH)  std::cout << index << '\n'; // echo input
        bvptr->Set(index);
        break;
      case 'U':
        if (BATCH)  std::cout << '\n'; // echo input
        bvptr->Unset();
        break;
      case 'u':
        *isptr >> index;
        if (BATCH)  std::cout << index << '\n'; // echo input
        bvptr->Unset(index);
        break;
      case 'F':
        if (BATCH)  std::cout << '\n'; // echo input
        bvptr->Flip();
        break;
      case 'f':
        *isptr >> index;
        if (BATCH)  std::cout << index << '\n'; // echo input
        bvptr->Flip(index);
        break;
      case 't': case 'T':
        *isptr >> index;
        if (BATCH)  std::cout << index << '\n'; // echo input
        std::cout << "  v.Test(" << index << ") == ";
        if (bvptr->Test(index))
          std::cout << "1\n";
        else
          std::cout << "0\n";
        break;
      case '[':
        *isptr >> index >> selection;
        if (BATCH)  std::cout << index << selection << '\n'; // echo input
        std::cout << "  v[" << index << "] == "
                  << (size_t)bvptr->operator[](index)
                  << '\n';
        break;
      case 'e': case 'E':
        *isptr >> index;
        if (BATCH)  std::cout << index << '\n'; // echo input
        std::cout << " v.Expand(" << index << ")\n";
        bvptr->Expand(index);
        break;
      case 'd': case 'D':
        if (BATCH)  std::cout << '\n'; // echo input
        std::cout << " v.Size(): " << bvptr -> Size() << " ; v.Dump(std::cout):\n";
        bvptr->Dump(std::cout);
        break;
      case 'o': case 'O':
        if (BATCH)  std::cout << '\n'; // echo input
        std::cout << " std::cout << v: " << *bvptr << '\n';
        break;
      case 'm': case 'M':
        if (BATCH)  std::cout << '\n'; // echo input
        DisplayMenu(size);
        break;
      case 'x': case 'X':
        if (BATCH)
        {
          std::cout << '\n'; // echo input
          isptr = &std::cin;
          ifs.close();
          BATCH = 0;
          std::cout << " ** switched to interactive mode\n";
        }
        else
        {
          std::cout << " ** already in interactive mode\n";
        }
        break;
      case 'q': case 'Q': 
        if (BATCH)  std::cout << '\n'; // echo input
        selection = 'Q';
        if (BATCH)
          ifs.close();
        break;
      default:
        if (BATCH)  std::cout << '\n'; // echo input
        std::cout << "  command not found\n";
    }
  }
  while (selection != 'Q');
  delete bvptr;
  std::cout << "Thank you for testing BitVector\n";
  return 0;
}

void DisplayMenu(size_t size)
{
  if (size == 0)
    std::cout << "     BitVector () v;\n";
  else
    std::cout << "     BitVector (" << size << ") v;\n";
  std::cout << "     operation                                entry\n"
            << "     ---------                                -----\n"
            << "     v.Set      ()  ............................  S\n"
            << "     v.Set      (i) ............................  s i\n"
            << "     v.Unset    ()  ............................  U\n"
            << "     v.Unset    (i) ............................  u i\n"
            << "     v.Flip     ()  ............................  F\n"
            << "     v.Flip     (i) ............................  f i\n"
            << "     v.Test     (i) ............................  t i\n"
            << "     v.Expand   (newsize)  .....................  e newsize\n"
            << "     v.Dump     (std::cout)  ...................  d\n"
            << "     v[i]       ................................  [i]\n"
            << "     std::cout << v  ...........................  o\n"
            << "     copy, assign tests  .......................  =\n"
            << "     display this Menu  ........................  m\n"
            << "     switch to interactive mode  ...............  x\n"
            << "     Quit program  .............................  q\n";
}

void CopyTest(const fsu::BitVector& bv1, fsu::BitVector bv2)
{
  // bv1 = original, bv2 = copy
  std::cout << "  CopyTest:";
  if (bv1 == bv2)
  {
    std::cout << " objects are equal\n";
  }
  else
  {
    std::cout << " objects are NOT equal:\n";
    std::cout << "    original object size: " << bv1.Size() << '\n'
              << "                    Dump:\n";
    bv1.Dump(std::cout);
    std::cout << '\n';
    std::cout << "    copy of object  size: " << bv2.Size() << '\n'
              << "                    Dump:\n";
    bv2.Dump(std::cout);
    std::cout << '\n';
  }
}

void AssignTest(const fsu::BitVector& bv1)
{
  // bv1 = original, bv2 = copy
  fsu::BitVector bv2(0);
  bv2  = bv1;
  std::cout << "  AssignTest:";
  if (bv1 == bv2)
  {
    std::cout << " objects are equal\n";
  }
  else
  {
    std::cout << " objects are NOT equal:\n";
    std::cout << "    original object size: " << bv1.Size() << '\n'
              << "                    Dump:\n";
    bv1.Dump(std::cout);
    std::cout << '\n';
    std::cout << "    assignee object size: " << bv2.Size() << '\n'
              << "                    Dump:\n";
    bv2.Dump(std::cout);
    std::cout << '\n';
  }
}
