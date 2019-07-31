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

void print(fsu::Matrix<int> score, fsu::String x, size_t m, size_t n);

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
  score.Dump(std::cout, m);
	parent.Dump(std::cout, m);
//	print(score, str1, m, n);
/*	size_t l = m + n;
 	i = m;
 	j = n;
 	fsu::Vector<char> ans1;
 	fsu::Vector<char> ans2;
	fsu::Vector<char> tmp1;
 	fsu::Vector<char> tmp2;
	fsu::Vector<char> signs;
//	ans1.SetSize(l);
	//ans2.SetSize(l);
 	while(i > 1 || j > 1)
 	{
 		if(parent[i][j] == 'U')
 		{
 			ans1.PushBack(str1[i-1]);// = str1[i-1] + ans1;
 			ans2.PushBack('-'); //= '-' + ans2;
 			i--;
 		}
 		else if(parent[i][j] == 'L')
		{
			ans1.PushBack('-');
			ans2.PushBack(str2[j-1]);
 			j--;
 		}
 		else if(parent[i][j] == 'D')
 		{
			ans1.PushBack(str1[i-1]);
			ans2.PushBack(str2[j-1]);
 			j--;
 			i--;
 		}
 	}
	//ans1.Dump(std::cout);
	for(i = ans1.Size()-1; i > 0; i--)
				tmp1.PushBack(ans1[i]);
	for(i = ans2.Size()-1; i > 0; i--)
				tmp2.PushBack(ans2[i]);
	tmp1.PushBack(ans1[0]);
	tmp2.PushBack(ans2[0]);
	tmp1.Dump(std::cout);
	tmp2.Dump(std::cout);*/
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

void print(fsu::Matrix<int> score, fsu::String x, size_t m, size_t n)
{
	std::cout << "in print\n";
	if(score[m][n] == (score[m-1][n-1] + 1) || score[m][n] == (score[m-1][n-1] - 1))
	{
		print(score, x, m-1, n-1);
		std::cout << x[m-1];
	}
	else if (score[m][n] == (score[m-1][n] - 1))
	{
    //	std::cout << '-';
			print(score,x,m-1,n);
  }
  else
		print(score,x,m,n-1);
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
			score[i][j] = 0;
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
			score[i][j] = Max(score[i-1][j] - 1,//delete
						   score[i][j-1] - 1,score[i-1][j-1] + sub);//sub
			/*if(parent[i][j] == 'D')
			{
				if(s[i] == t[j])
						score[i][j] = (1 + score[i-1][j-1]);
				else
						score[i][j] = (score[i-1][j-1] - 2);
			}
		  else if(parent[i][j] == 'L')
				score[i][j] = (score[i-1][j] - 1);
			else if(parent[i][j] == 'U')
				score[i][j] = (score[i][j-1] - 1);*/
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
