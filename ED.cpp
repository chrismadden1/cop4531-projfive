#include<iostream>
#include "bitvect.h"
#include "genalg.h"
#include "matrix.h"
#include "xstring.cpp"
#include "bitvect.cpp"


size_t ED(fsu::String s, size_t m, fsu::String t, size_t n, fsu::BitVector& bvs,
	 fsu::BitVector& bvt, size_t subCost, fsu::Matrix<char> &parent);
size_t Min(size_t a, size_t b, size_t c);
int main(int argc, char*argv[])
{
	size_t subCost = 2;
	if(argc < 2)
	{
		std::cout << "not enough args\n";
		return -1;
	}
	fsu::String str1 = argv[1];
	fsu::String str2 = argv[2];
	if(argc > 3)
	{
		fsu::String sub = argv[3];
		if(sub == "0")
				subCost = 0;
		if(sub == "1")
				subCost = 1;
		if(sub == "2")
				subCost = 2;
	}
	size_t m = str1.Size();
	size_t n = str2.Size();

	fsu::BitVector bvs(m);
	fsu::BitVector bvt(n);
	fsu::Matrix<size_t> Parent (m+1,n+1, 0);
	size_t ed_length = ED(str1, m, str2, n, bvs, bvt, subCost);
	if(subCost != 2){
	std::cout << "\n\tEdit Distance: " << ed_length << " // substitution cost = " <<
		subCost << std::endl;
	}
	else
	{
		std::cout << "\n\tEdit Distance: " << ed_length <<
		" // Levenshtein - substitution cost = " <<	subCost << std::endl;
	}
	std::cout << "\t\ts:  " << str1 << std::endl;
	std::cout << "   s > t transcript: " << std::endl;
	std::cout << "   t > s transcript: " << std::endl;
	std::cout << "\t\tt:  " << str2 << std::endl;
	std::cout << "  optimal alignment: " << std::endl;
	parent.Dump(std::cout, m);

	return 0;
}
size_t ED(fsu::String s, size_t m, fsu::String t, size_t n, fsu::BitVector& bvs,
	 fsu::BitVector& bvt, size_t subCost, fsu::Matrix<char> &parent)
{
	bvs.Unset();
	bvs.Unset();
	fsu::Matrix<size_t> L (m+1,n+1, 0);
	size_t i;
	size_t j;
	L[0][0] = 0;
	for(i = 0; i <= m; i++)
	{
	for(j = 0; j <= n; j++)
	    if(i == 0)
					L[i][j] = j;
			else if(j == 0)
					L[i][j] = i;
			else if(s[i-1] == t[j-1])
			{
				L[i][j] = L[i-1][j-1];
				bvs.Set(i);
				bvt.Set(j);
			}
			else
			{
				L[i][j] = Min(1 + L[i-1][j],//delete
						   1 + L[i][j-1],//insert
						   subCost + L[i-1][j-1]);//sub
				if(L[i][j] == 1 + L[i-1][j])
					parent[i][j] = 'U';//parent is up
				else if(L[i][j] == 1 + L[i][j-1])
					parent[i][j] = 'L';//parent is left
				else
					parent[i][j] = 'D';//parent is diag.
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
