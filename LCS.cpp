#include<iostream>
#include<cstdlib>
#include "bitvect.h"
#include "genalg.h"
#include "matrix.h"
#include "xstring.h"
#include "xstring.cpp"
#include "tostring.h"
#include "string.h"
//#include "tostring.cpp"
#include "bitvect.cpp"


using namespace fsu;
void  ls1(fsu::String s, size_t m, fsu::String t, size_t n, fsu::Matrix<size_t>& L);
//void   LCS(const char* s, size_t m, const char* t, size_t n, fsu::Matrix<size_t>& L);

//size_t LCS(const char* s, size_t m, const char* t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt);
size_t ls2(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt);


int main(int argc, char*argv[])
{
	if(argc < 2)
	{
		std::cout << "not enough args\n";
		return -1;
	}
	fsu::String str1 = argv[1];
	fsu::String str2 = argv[2];

	size_t m = str1.Size();
	size_t n = str2.Size();

	fsu::BitVector  bvs(m); //= new fsu::BitVector (m);
	fsu::BitVector  bvt(n); //= new fsu::BitVector (n);

	size_t lcs_length = ls2(str1, m, str2, n, bvs, bvt);
	std::cout << "length of lcs: " << lcs_length << '\n';
	bvs.Dump(std::cout);
	bvt.Dump(std::cout);

	return 0;
}
//size_t LCS(const char* s, size_t m, const char* t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt)
size_t ls2(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt)
{
	fsu::Matrix<size_t> L (m+1,n+1, 0);
	ls1(s, m, t, n, L);
	bvs.Unset();
	bvt.Unset();
	size_t i = m;
	size_t j = n;
	while(i > 0 && j > 0)
	{
		if(s[i-1] == t[j -1])
		{
			bvs.Set(i-1);
			bvt.Set(j-1);
			--i;
			--j;
		}
		else if(L[i][j] == L[i-1][j])
			--i;
		else
			--j;
	}
	return L[m][n];
}

void   ls1(fsu::String s, size_t m, fsu::String t, size_t n, fsu::Matrix<size_t>& L)
{
	size_t i;
	size_t j;
	for(i = 1; i <= m; ++i)
	{
		for(j = 1; j <=n; ++j)
		{
			if(s[i-1] == t[j-1])
				L[i][j] = 1 + L[i-1][j-1];
			else
				L[i][j] = fsu::Max(L[i-1][j], L[i][j-1]);
		}
	}
}
