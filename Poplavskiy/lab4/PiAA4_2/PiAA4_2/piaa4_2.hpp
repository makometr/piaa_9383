#include <iostream>
#include <string>
#include <vector>
#include <cmath>


std::vector <int> prefix(std::string& arr) {
	std::vector <int> p(arr.size());
	size_t j = 0;
	size_t i = 1;
	p[0] = 0;
	while (i < arr.length()) {
		if (arr[i] == arr[j]) {
			p[i] = j + 1;
			i++;
			j++;
		}
		else if (j == 0) {
			p[i] = 0;
			i++;
		}
		else {
			j = p[j - 1];
		}
	}
	return p;
}

int CYCLE_KMP(std::string& s1, std::string& s2) {
	size_t i = 0;
	size_t j = 0;
	if (s1.length() != s2.length()) {
		return -1;
	}
	else if (s1 == s2) {
		return 0;
	}
	else {
		s2 += " " + s1 + s1;
		std::vector<int> p = prefix(s2);
		int res = -1;
		for (int k = s1.length() + 1; k < s2.length(); k++)
		{
			if (p[k] == s1.length())
			{
				res = k - 2 * s1.length();
				break;
			}
		}
		return res;
	}
}