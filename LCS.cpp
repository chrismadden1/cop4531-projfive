#include<iostream>
#include<cstdlib>
#include "bitvect.h"
#include "genalg.h"
#include "matrix.h"
#include "xstring.h"
#include "xstring.cpp"
#include "tostring.h"
#include "string.h"
#include "bitvect.cpp"


using namespace fsu;
void  ls1(fsu::String s, size_t m, fsu::String t, size_t n, fsu::Matrix<size_t>& L);

size_t ls2(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs,
		fsu::BitVector& bvt, fsu::Matrix<char>& parent);


int main(int argc, char*argv[])
{
	if(argc < 2)
	{
		std::cout << "Usage: LCS.x string1(required) string2(required)\n";
		std::cout << "returns longest common subsequence\n;
		return -1;
	}
	fsu::String str1 = argv[1];
	fsu::String str2 = argv[2];
	size_t m = str1.Size();
	size_t n = str2.Size();
	fsu::BitVector  bvs(m);
	fsu::BitVector  bvt(n);
	fsu::Matrix<char> parent (m+1,n+1, 0);
	size_t lcs_length = ls2(str1, m, str2, n, bvs, bvt, parent);
	size_t arr1[m];
	size_t arr2[n];
	size_t i, j, k;
	j = 0;
	k = 0;
	for(i = 0; i < m; i++)
	{
		if(bvs.Test(i))
		{
			arr1[j] = i;
			j++;
		}
	}
	for(i = 0; i < n; i++)
	{
		if(bvt.Test(i))
		{
			arr2[k] = i;
			k++;
		}
	}
//	size_t longest = fsu::Max(m, n);

	std::cout << "\n";
	std::cout << "   Length of LCS:  " << lcs_length << '\n';
	std::cout << "   LCS in s: " << "{ ";
	for(i = 0; i < j; i++)
		std::cout << arr1[i] << " ";
	std::cout << "}\n";
	std::cout << "    bitcode: ";
	for(size_t i = 0; i < m; i++)
		std::cout << bvs[i];
	std::cout << "\n";
	std::cout << "\t s = " << str1 << std::endl;
	std::cout << "   LCS in t: " << "{ ";
	for(i = 0; i < k; i++)
		std::cout << arr2[i] << " ";
	std::cout << "}\n";
	std::cout << "    bitcode: ";
	for(size_t i = 0; i < n; i++)
		std::cout << bvt[i];
    std::cout << "\n";
	std::cout << "\t t = " << str2 << std::endl;
	std::cout << "   optimal alignment: " << std::endl;
	size_t l = m + n;
	i = m;
	j = n;
	fsu::String ans1 = "";
	fsu::String ans2 = "";
	size_t xpos = l;
	size_t ypos = l;
	while(i >= 1 || j >= 1)
	{
		if(parent[i][j] == 'U')
		{
			ans1 += str1[i-1];
			ans2 += '-';
			i--;
		}
		else if(parent[i][j] == 'L')
			ans1 += '-';
			ans2 += str2[j-1];
			j--;
		}
		else 
		{
			ans1 += str1[j-1];
			ans2 += str2[j-1];
			j--;
			i--;
		}
	}

	std::cout << "\ts = " << ans1 << std::endl;
	std::cout << "\n";
	std::cout << "\tt = " << ans2 << std::endl;
	return 0;
}
size_t ls2(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs,
		fsu::BitVector& bvt, fsu::Matrix<char>& parent)
{
	///////////////////////////////////////////////////add into code here and pass by reference if doesnot work//////////
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
			parent[i][j] = 'D';//diag == match
			--i;
			--j;
		}
		else if(L[i][j] == L[i-1][j])
		{
				parent[i][j] = 'U';//up
			--i;
		}
		else
		{
			parent[i][j] = 'L';//left
			--j;
		}
	}
	return L[m][n];
}

void   ls1(fsu::String s, size_t m, fsu::String t, size_t n,
		fsu::Matrix<size_t>& L)
{
	size_t i;
	size_t j;
	for(i = 1; i <= m; ++i)
	{
		for(j = 1; j <=n; ++j)
		{
			if(s[i-1] == t[j-1])
			{
				L[i][j] = 1 + L[i-1][j-1];
			}
			else
			{
				L[i][j] = fsu::Max(L[i-1][j], L[i][j-1]);
			}
		}
	}
}
