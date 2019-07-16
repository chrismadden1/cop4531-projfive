/*
    bitvect.h
    08/17/18
    Chris Lacher

    BitVector class - based on array of 8-bit words

    Copyright 2018, R.C. Lacher
*/

#ifndef _BITVECT_H
#define _BITVECT_H

#include <cstdlib>
#include <iostream>

namespace fsu
{

  //----------------------------------
  //     BitVector
  //----------------------------------

  class BitVector;

  std::ostream& operator << (std::ostream&, const BitVector&);
  bool operator== (const BitVector& v1 , const BitVector& v2);
  bool operator!= (const BitVector& v1 , const BitVector& v2);
  
  class BitVector
  {
  public:
             BitVector  ();                 // construct a BitVector with default size
    explicit BitVector  (size_t size);      // construct a BitVector with specified size
             BitVector  (const BitVector&); // copy constructor      
             ~BitVector ();                 // destructor

    BitVector& operator = (const BitVector& a);  // assignment operator

    void   Set    ();                     // make all bits = 1
    void   Set    (size_t index);         // make bit at index = 1
    void   Unset  ();                     // make all bits = 0
    void   Unset  (size_t index);         // make bit at index = 0
    void   Flip   ();                     // change all bits 
    void   Flip   (size_t index);         // change bit at index
    bool   Test   (size_t index) const;   // return bit value at index as bool

    size_t Size   () const;               // return size of bitvector
    void   Expand (size_t newsize);       // increase number of bits, retaining current values
    void   Dump   (std::ostream& os) const;
   
    // syntactic sugar
    bool   operator[] (size_t i) const { return Test(i); }

  private:
    // data
    uint8_t *  byteArray_;
    size_t     byteArraySize_;

    // methods
    size_t          ByteNumber (size_t index) const;
    static uint8_t  Mask       (size_t index);

  } ; // class BitVector

}   // namespace fsu

#endif
