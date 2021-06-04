import time
import sys

def prefix_function(s):
	p = [0]*len(s)
	for i in range(1, len(s)):
		k = p[i-1]
		while k > 0 and s[i] != s[k]:
			k = p[k-1]
		p[i] = k+1 if s[i] == s[k] else k
	return p


def kmp(string, sub_string):
	prefix_function_table = prefix_function(string)
	sub_string_index = 0
	string_index = 0

	while(sub_string_index < len(sub_string)):
		if sub_string[sub_string_index] != string[string_index]:
			if string_index == 0:
				sub_string_index += 1
			string_index = prefix_function_table[string_index - 1]
		elif string_index == len(string) - 1:
			return sub_string_index - len(string) + 1
		else:
			sub_string_index += 1
			string_index += 1
	return -1


b = input()
a = input()

if(len(a) == len(b)):
    index = kmp(a, b+b)
    print(index)
else:
	print(-1)