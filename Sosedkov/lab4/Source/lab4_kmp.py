import time
import sys

def prefix_function(s, max_len=sys.maxsize):
	p = [0]*len(s)
	for i in range(1, len(s)):
		k = p[i-1]
		while k > 0 and s[i] != s[k]:
			k = p[k-1]
		p[i] = k+1 if s[i] == s[k] else k
	return p

def kmp(string, sub_string):
	prefix_function_table = prefix_function(sub_string+'#'+string)
	return [index-len(sub_string)*2 for index, value in enumerate(prefix_function_table) if value==len(sub_string)]



if __name__ == '__main__':
	sub_string = input()
	string = input()

	indices = kmp(string, sub_string)

	if indices:
		print(indices[0], end='', sep='')
		for i in range(1, len(indices)):
			print(',',indices[i], end='', sep='')
		print('\n')
	else:
		print(-1)