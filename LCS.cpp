#include<iostream>
#include "bitvect.h"
#include "genalg.h"
#include "matrix.h"

//void   LCS(fsu::String s, size_t m, fsu::String t, size_t n, fsu::Matrix<size_t>& L); 
void   LCS(const char* s, size_t m, const char* t, size_t n, fsu::Matrix<size_t>& L); 

size_t LCS(const char* s, size_t m, const char* t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt); 
//size_t LCS(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt);

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
		
	size_t lcs_length = LCS(str1, m, str2, n, bvs, bvt);
	cout << "length of lcs: " << lcs_length << '\n';
	
	return;
}

//size_t LCS(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt)
size_t LCS(const char* s, size_t m, const char* t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt)
{
	fsu::Matrix<size_t> L (m+1,n+1,0);
	LCS(s, m, t, n, L);
	bvs.Unset();
	bvt.Unset();
	size_t i;
	size_t j;
	for(i = m; j = n; i > 0; j > 0)
	{
		if(s[i-1] == t[j -1])
		{
			bvs.Set(i-1); 
			bvt.Set(j-1);
			--i;
			--j;
		}
		else if(L[i,j] == L[i-1,j])
			--i;
		else
			--j;
	}		
	return L[m][n];
}

void   LCS(const char* s, size_t m, const char* t, size_t n, fsu::Matrix<size_t>& L)
{
	size_t i;
	size_t j;
	for(i = 1; i <= m; ++i)
	{
		for(j = 1; j <=n; ++j)
		{
			if(s[i-1] == t[j-1])
				L[i,j] = 1 + L[i-1,j-1];
			else
				L[i,j] = fsu::Max(L[i-1,j], L[i,j-1]);
			
		}	
	}	
}
	
