#include<iostream>
#include "bitvect.h"
#include "genalg.h"
#include "matrix.h"
#include "xstring.cpp"
#include "bitvect.cpp"
#include "tostring.cpp"

void   ED(fsu::String s, size_t m, fsu::String t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt); 
//void   ED(const char* s, size_t m, const char* t, size_t n,  fsu::BitVector& bvs, fsu::BitVector& bvt);


//namespace fsu

int main(int argc, char*argv[])
{
	if(argc < 2)
	{
		cout << "not enough args\n";
		return;
	}
	fsu::String str1 = argv[1];
	fsu::String str2 = argv[2];
	
	size_t m = str1.size();
	size_t n = str2.size();
	
	fsu::BitVector * bvs = new fsu::BitVector (m);
	fsu::BitVector * bvt = new fsu::BitVector (n);
		
	size_t ed_length = ED(str1, m, str2, n, bvs, bvt);
	cout << "length of ed: " << ed_length << '\n';
	bvs.Dump(std::cout);
	bvt.Dump(std::cout);
	
	return;
}
size_t LCS(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt)
//size_t ED(const char* s, size_t m, const char* t, size_t n,  fsu::BitVector& bvs, fsu::BitVector& bvt)
{
	bvs.Unset();
	bvs.Unset();
	fsu::Matrix<size_t> L (m+1,n+1, 0);
	size_t i;
	size_t j;
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(i == 0)
				L[i, j] = j;
			
			else if(j == 0)
				L[i, j] = i;
			
			else if(s[i-1] == t[j-1])
			{
				bvs.Set(i);
				bvt.Set(j);
				L[i,j] = L[i-1,j-1];
			}
			else
			{
				L[i,j] - fsu::Min(1 + L[i-1, j],
								  1 + L[i, j-1],
								  1 + L[i-1,j-1]);	
			}
		}		
	}
	return L[m][n];
}

	
