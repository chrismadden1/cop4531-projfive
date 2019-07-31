#include<iostream>
#include "bitvect.h"
#include "genalg.h"
#include "matrix.h"
#include "xstring.cpp"
#include "bitvect.cpp"


size_t ED(fsu::String s, size_t m, fsu::String t, size_t n, size_t subCost, 
	  fsu::Matrix<char> &parent, fsu::Matrix<size_t>& L);
size_t Min(size_t a, size_t b, size_t c);
int main(int argc, char*argv[])
{
	size_t subCost = 2;
	if(argc < 2)
	{
		std::cout << "Usage: ED.x string1(required) string2(required)\n";
		std::cout << "argument 3 is optional (substituion cost)\n;
		std::cout << "argument 4 is optional\n;
		std::cout << "returns minimal edit distance to turn string1 into string 2\n;
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

	fsu::Matrix<size_t> L (m+1,n+1, 0);
	fsu::Matrix<char> parent (m+1,n+1, 0);
	fsu::Vector<char> ans1;
	fsu::Vector<char> ans2;
	fsu::Vector<char> tmp1;
	fsu::Vector<char> tmp2;
	fsu::Vector<char> signs;
	size_t ed_length = ED(str1, m, str2, n, parent, L);
	if(subCost != 2){
	std::cout << "\n\tEdit Distance: " << ed_length << " // substitution cost = " <<
		subCost << std::endl;
	}
	else
	{
		std::cout << "\n\tEdit Distance: " << ed_length <<
		" // Levenshtein - substitution cost = " <<	subCost << std::endl;
	}
	size_t i = m;
	size_t j = n;
	while(i > 0 || j > 0)
	{
		if(str1[i-1] == str2[j-1])
		{
			ans1.PushBack('M');
			ans2.PushBack('M');
			signs.PushBack('|');
			i--; j--;
		}
		else if(j > 0 && (L[i][j] == L[i][j-1] + 1))
		{
			ans1.PushBack('I');
			ans2.PushBack('D');
			signs.PushBack(' ');
			j--;
		}
		else if(i > 0 && (L[i][j] == L[i-1][j] + 1))
		{
			ans1.PushBack('D');
			ans2.PushBack('I');
			signs.PushBack(' ');
			i--;
		}
		else if(j > 0 &&  I > 0 && (L[i][j] == L[i-1][j-1] + subCost))
		{
			ans1.PushBack('S');
			ans2.PushBack('S');
			signs.PushBack(' ');
			j--; i--;
		}
		
	}
	std::cout << "\t\ts:  " << str1 << std::endl;
	std::cout << "   s > t transcript: ";
	for(i = ans1.Size()-1; i > 0; i--)
		tmp1.PushBack(ans1[i]);
	std::cout << "\n   t > s transcript: ";
	for(i = ans2.Size()-1; i > 0; i--)
		tmp2.PushBack(ans2[i]);
	for(i = 0; i < ans1.Size(); i++)
		std::cout << tmp1[i];
	for(i = 0; i < ans2.Size(); i++)
		std::cout << tmp2[i];
	std::cout << "\t\tt:  " << str2 << std::endl;
	std::cout << "  optimal alignment: " << std::endl;
	i = 0;
	j = 0;
	while(i < m)
	{
		if(ans1[i] == 'I')
		{
			std::cout << '-';	
		}
		else
		{
			std::cout<< str1[i];
			i++;
		}
	}
	for(size_t k = 0; k < signs.Size(); k++)
		std::cout << signs[k];
	while( j < n)
	{
		if(ans2[j] == 'I')	
		{
			std::cout << '-';	
		}
		else
		{
			std::cout<< str2[j];
			j++;
		}
	}
	return 0;
}
size_t ED(fsu::String s, size_t m, fsu::String t, size_t n, size_t subCost, 
	  fsu::Matrix<char> &parent, fsu::Matrix<size_t>& L)
{
	bool match = false;
	size_t i;
	size_t j, a, b, c;
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
			match = true;
			L[i][j] = L[i-1][j-1];
		}
		else
		{
			a = L[i-1][j-1] + subCost;
			b = L[i-1][j] + 1;//delete
			c = L[i][j-1] + 1;//insert
			L[i][j] = Min(a, b, c)
			if(L[i][j] == b)
			{
				parent[i][j] = 'U';//parent is up
			}
			else if(L[i][j] == c)
			{
				parent[i][j] = 'L';//parent is left
			}
			else
			{	
				parent[i][j] = 'D';//parent is diag.
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
