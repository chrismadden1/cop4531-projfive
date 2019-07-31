/*
    LCS.cpp
    Chris Madden
    07/20/19

		algorithm for longest common subsequence
		 along with optimal alignment.

*/

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


void  ls1(fsu::String s, size_t m, fsu::String t, size_t n, fsu::Matrix<size_t>& L,
		fsu::Matrix<char>& parent, fsu::Matrix<int>& score);

size_t ls2(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs,
		fsu::BitVector& bvt, fsu::Matrix<char>& parent, fsu::Matrix<int>& score);

void align(fsu::Matrix<int> &score, fsu::String s, size_t m,
			fsu::String t, size_t n, fsu::Matrix<size_t> L, fsu::Matrix<char> parent);

void print(fsu::Matrix<int> score, fsu::String x, size_t m, fsu::String y, size_t n,
	  fsu::Vector<char> &ans1, fsu::Vector<char> &ans2);

size_t Max(int a, int b, int c);


int main(int argc, char*argv[])
{
	if(argc < 2)
	{
		std::cout << "Usage: LCS.x string1(required) string2(required)\n";
		std::cout << "returns longest common subsequence\n";
		return -1;
	}
	fsu::String str1 = argv[1];
	fsu::String str2 = argv[2];
	size_t m = str1.Size();
	size_t n = str2.Size();
	fsu::BitVector  bvs(m);
	fsu::BitVector  bvt(n);
	fsu::Matrix<char> parent (m+1,n+1, 0);
	fsu::Matrix<int> score (m+1,n+1, 0);
	size_t lcs_length = ls2(str1, m, str2, n, bvs, bvt, parent, score);
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
	print(score, str1, m, n, ans1, ans2);
	//size_t l = m + n;
 	//i = m;
 	//j = n;
 	fsu::Vector<char> ans1;
 	fsu::Vector<char> ans2;
	//fsu::Vector<char> tmp1;
 	//fsu::Vector<char> tmp2;
	//fsu::Vector<char> signs;
	print(score, str1, m, n, ans1, ans2);
	return 0;
}
size_t ls2(fsu::String s, size_t m,fsu::String t, size_t n, fsu::BitVector& bvs,
		fsu::BitVector& bvt, fsu::Matrix<char>& parent, fsu::Matrix<int>& score)
{
	fsu::Matrix<size_t> L (m+1,n+1, 0);
	ls1(s, m, t, n, L, parent, score);
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
		//parent[i][j] = 'D';//diag == match
			--i;
			--j;
		}
		else if(L[i][j] == L[i-1][j])
		{
			//	parent[i][j] = 'U';//up
			--i;
		}
		else
		{
		//	parent[i][j] = 'L';//left
			--j;
		}
	}
	return L[m][n];
}

void   ls1(fsu::String s, size_t m, fsu::String t, size_t n,
		fsu::Matrix<size_t>& L, fsu::Matrix<char>& parent, fsu::Matrix<int>& score)
{
	size_t i;
	size_t j;

	for(i = 1; i <= m; ++i)
	{
		for(j = 1; j <=n; ++j)
		{
			if(s[i-1] == t[j-1])
			{
			//	score[i][j] = 1 + score[i-1][j-1];
				parent[i][j] = 'D';//diag == match
				L[i][j] = 1 + L[i-1][j-1];
			}
			else if(L[i-1][j] >= L[i][j-1])
			{
				parent[i][j] = 'U';//diag == match
				L[i][j] = L[i-1][j];
			}
			else
			{
				parent[i][j] = 'L';//diag == match
				L[i][j] = L[i][j-1];
			}

		}
	}
	align(score,s, m,t, n, L, parent);
}

void print(fsu::Matrix<int> score, fsu::String x, size_t m, fsu::String y, size_t n,
	  fsu::Vector<char> &ans1, fsu::Vector<char> &ans2)
{
	//std::cout << "in print\n";
	if(i > 0 && (score[m][n] == score[m-1][n] + 1))
	{
		print(score, x, m-1, y, n, ans1, ans2);
		ans1.PushBack(x[m-1]);
		ans2.PushBack('-');
	}
	else if (i > 0 && j > 0 && (score[m][n] == score[m-1][n-1] - 1 || score[m][n] == score[m-1][n-1] + 1 ))
	{
    		print(score, x, m-1, y, n-1, ans1, ans2);
		ans1.PushBack(x[m-1]);
		ans2.PushBack(y[n-1]);			
 	}
  	else
 	 {
		print(score, x, m, y, n-1, ans1, ans2);
	  	ans1.PushBack('-');
		ans2.PushBack(y[n-1]);
  	 }
}

void align(fsu::Matrix<int> &score, fsu::String s, size_t m,
	fsu::String t, size_t n, fsu::Matrix<size_t> L, fsu::Matrix<char> parent)
{
	size_t i;
	size_t j;
	int sub;
	for(i = 0; i < m; i++)
	{
	for(j = 0; j < n; j++)
	{
		score[i][j] = 0;
		
	}
	}
	for(i = 1; i <= m; i++)
			score[i][0] = i * -1;
	for(j = 1; j <= n; j++)
			score[0][j] = j * -1;
	for(i = 1; i <= m; ++i)
	{
		for(j = 1; j <= n; ++j)
		{
			if(s[i-1] == t[j-1])
				sub = 1;
			else
				sub = -1;
			int a = score[i-1][j] + 1;
			int b = score[i-1][j-1] + sub;
			int c = score[i][j-1] + 1;
			score[i][j] = Max(a, b, c);
		}
	}
}
size_t Max(int a, int b, int c)
{
	size_t val = a;
	if(b > val)
		val = b;
	if(c > val)
		val = c;
	return val;
}
