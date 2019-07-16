/*
    bitvect.cpp
    08/17/18
    Chris Lacher

    BitVector class implementation - array of unsigned char version

    Copyright 2018, R.C. Lacher
*/

#include <iostream>
#include <bitvect.h>

namespace fsu
{

  //----------------------------------
  //     Global operators
  //----------------------------------

  bool operator== (const BitVector& v1 , const BitVector& v2)
  {
    if (v1.Size() != v2.Size())
      return 0;
    for (size_t i = 0; i < v1.Size(); ++i)
    {
      if (v1.Test(i) && !v2.Test(i))
        return 0;
      if (v2.Test(i) && !v2.Test(i))
        return 0;
    }
    return 1;
  }

  bool operator!= (const BitVector& v1 , const BitVector& v2)
  {
    return !(v1 == v2);
  }

  std::ostream& operator << (std::ostream& os, const BitVector& bv)
  {
    for (size_t i = 0; i < bv.Size(); ++i)
      os << bv[i];
    return os;
  }

  //----------------------------------
  //     class BitVector
  //----------------------------------

  // public methods

  void BitVector::Expand (size_t newsize) // increase number of bits, retaining current values
  {
    if (newsize <= Size()) return; // nothing to do
    size_t newByteArraySize = (newsize + 7)/8;
    uint8_t * newByteArray = new (std::nothrow) uint8_t [newByteArraySize];
    if (newByteArray == nullptr) // handle exception locally
    {
      std::cerr << "** BitVector::Expand error: memory allocation failure -- state unchanged.\n";
      return;
    }
    for (size_t i = 0; i < byteArraySize_; ++i)
    {
      newByteArray[i] = byteArray_[i];
    }
    for (size_t i = byteArraySize_; i < newByteArraySize; ++i)
    {
      newByteArray[i] = 0x00;
    }
    delete [] byteArray_;
    byteArraySize_ = newByteArraySize;
    byteArray_ = newByteArray;
  }

  void BitVector::Dump  (std::ostream& os) const
  {
    os << '\t';
    for (size_t i = 0; i < Size(); ++i)
      os << Test(i);
    os << "\n\t";
    for (size_t i = 0; i < Size(); ++i)
      os << (i % 10);
    os << '\n';
  }

  size_t BitVector::Size() const      
  // return size of bitvector
  {
    return 8 * byteArraySize_;
  }

  void BitVector::Set ()  
  // make all bits = 1
  {
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] = 0xFF;
  }

  void BitVector::Set (size_t index)  
  // make bit = 1: OR with mask
  {
    byteArray_[ByteNumber(index)] |= Mask(index);
  }

  void BitVector::Unset ()  
  // make all bits = 0
  {
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] = 0x00;
  }

  void BitVector::Unset (size_t index)  
  // make bit = 0: AND with inverted mask
  {
    byteArray_[ByteNumber(index)] &= ~ Mask(index);
  }

  void BitVector::Flip ()  
  // change all bit values
  {
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] ^= 0xFF;
  }

  void BitVector::Flip (size_t index)  
  // change bit value: XOR with mask
  {
    byteArray_[ByteNumber(index)] ^= Mask(index);
  }

  bool BitVector::Test  (size_t index) const  
  // return bit value
  {
    return 0 != (byteArray_[ByteNumber(index)] & Mask(index));
  }
   
  // proper type

  BitVector::BitVector () : BitVector(64) // delegate to constructor
  {}

  BitVector::BitVector (size_t numbits) // 1-parameter constructor
  {
    byteArraySize_ = (numbits + 7)/8;
    if (byteArraySize_ == 0) byteArraySize_ = 1;
    byteArray_ = new (std::nothrow) uint8_t [byteArraySize_];
    if (byteArray_ == nullptr) // handle exception locally
    {
      std::cerr << "** BitVector error: memory allocation failure -- terminating program.\n";
      exit (EXIT_FAILURE);
    }
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] = 0x00;
  }

  BitVector::BitVector (const BitVector& bv)  // copy constructor      
  {
    byteArraySize_ = bv.byteArraySize_;
    byteArray_ = new (std::nothrow) uint8_t [byteArraySize_];
    if (byteArray_ == nullptr) // handle exception locally
    {
      std::cerr << "** BitVector error: memory allocation failure -- terminating program.\n";
      exit (EXIT_FAILURE);
    }
    for (size_t i = 0; i < byteArraySize_; ++i)
      byteArray_[i] = bv.byteArray_[i];
  }

  BitVector::~BitVector ()  // destructor
  {
    delete [] byteArray_;
  }

  BitVector& BitVector::operator = (const BitVector& bv)  
  // assignment operator
  {
    if (this != &bv)
    {
      if (byteArraySize_ != bv.byteArraySize_)
      {
	delete [] byteArray_;
	byteArraySize_ = bv.byteArraySize_;
	byteArray_ = new (std::nothrow) uint8_t [byteArraySize_];
	if (byteArray_ == nullptr) // handle exception locally
	{
	  std::cerr << "** BitVector error: memory allocation failure -- terminating program.\n";
	  exit (EXIT_FAILURE);
	}
      }
      for (size_t i = 0; i < byteArraySize_; ++i)
	byteArray_[i] = bv.byteArray_[i];
    }
    return *this;
  }

  // private methods

  size_t BitVector::ByteNumber (size_t index) const
  {
    // return index / 8
    // shift right 3 is equivalent to, and faster than, dividing by 8
    index = index >> 3;
    if (index >= byteArraySize_)
    {
      std::cerr << "** BitVector error: index out of range\n";
      exit (EXIT_FAILURE);
    } 
    return index;
  }

  uint8_t BitVector::Mask (size_t index)
  {
    // return mask for index % 8
    // the low order 3 bits is the remainder when dividing by 8
    size_t shiftamount = index & (size_t)0x07;  // low order 3 bits
    return (uint8_t)0x01 << shiftamount;
  }

} // namespace fsu
