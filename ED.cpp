#include<iostream>
#include "bitvect.h"
#include "genalg.h"
#include "matrix.h"
#include "xstring.cpp"
#include "bitvect.cpp"
#include "tostring.cpp"

void   ED(fsu::String s, size_t m, fsu::String t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt); 
size_t Min(size_t a, size_t b, size_t c);
int main(int argc, char*argv[])
{
	if(argc < 2)
	{
		std::cout << "not enough args\n";
		return;
	}
	fsu::String str1 = argv[1];
	fsu::String str2 = argv[2];
	
	size_t m = str1.size();
	size_t n = str2.size();
	
	fsu::BitVector bvs(m);
	fsu::BitVector bvt(n);
		
	size_t ed_length = ED(str1, m, str2, n, bvs, bvt);
	std::cout << "length of ed: " << ed_length << '\n';
	bvs.Dump(std::cout);
	bvt.Dump(std::cout);
	
	return;
}
size_t ED(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt)
{
	bvs.Unset();
	bvs.Unset();
	fsu::Matrix<size_t> L (m+1,n+1, 0);
	size_t i;
	size_t j;
	/*if(m == 0)
		return n;
	if(n == 0)
		return m;*/
	for(i = 0; i <= m; i++)
		L[i][0] = i;
	for(j = 0; j <= m; j++)
		L[0][j] = j;
	
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{
			if(s[i-1] == t[j-1])//current characters match for each string.
			{
				bvs.Set(i);
				bvt.Set(j);
				L[i][j] = L[i-1][j-1];
			}
			else
			{
				L[i][j] = Min(1 + L[i-1][j],//delete
						   1 + L[i][j-1],//insert
						   1 + L[i-1][j-1]);//sub
			}
		}		
	}
	return L[m][n];
}

size_t Min(size_t a, size_t b, size_t c)
{
	size_t val = a;
	if(b < val)
		val = b;
	if(c < val)
		val = c;
	return val;	
}
	
