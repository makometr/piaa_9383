#pragma once
#include <iostream>
#include <string>
#include <vector>

std::vector <int> prefix(std::string arr) {
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

std::vector <int> KMP(std::string form, std::string line) {
	std::vector <int> res;
	std::vector <int> p = prefix(form);
	size_t i = 0;
	size_t j = 0;
	while (i < line.length()) {
		if (line[i] == form[j]) {
			i++;
			j++;
			if (j == form.length()) {
				res.push_back(i - form.length());
			}
		}
		else if (j != 0) {
			j = p[j - 1];
		}
		else {
			i++;
		}
	}
	return res;
}