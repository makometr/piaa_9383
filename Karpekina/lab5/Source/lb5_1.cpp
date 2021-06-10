#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

std::vector <std::pair<int, int>> output;

class TrieNode
{
public:
	int parent;
	char key;
	int next_node[5];
	int templates_number = 0;
	bool flag = false;
	int suffix_link = -1;
	int movement[5];
	TrieNode(int, char);
	TrieNode() = default;
	~TrieNode() = default;
};

class Trie
{
	std::vector <TrieNode> trie;
	int GetMovement(int node, int edge);
	int GetSuffixLink(int node);
	void Result(std::vector <std::string>& templates, int node, int symbol_number, std::string text);

public:
	Trie();
	~Trie() = default;
	void TrieAddNode(std::map<char, int> alphabet, int index, std::string text);
	void MatchesSearch(std::vector <std::string> templates, std::string text, std::map<char, int> alphabet);

};

Trie::Trie()
{
	trie.push_back(TrieNode(0,0));
}

TrieNode::TrieNode(int parent, char symbol)
{
	for (int i = 0; i < 5; i++)
	{
		next_node[i] = -1;
		movement[i] = -1;
	}
	this->parent = parent;
	this->key = symbol;
}

void Trie::TrieAddNode(std::map<char, int> alphabet, int index, std::string text)
{
	int n = 0;
	int edge = 0;
	for (int i = 0; i < text.length(); i++){
		char symbol = text[i];
		edge = alphabet[symbol];
		if (trie[n].next_node[edge] == -1)
		{
			trie.push_back(TrieNode(n, edge));
			trie[n].next_node[edge] = trie.size() - 1;
		}
		n = trie[n].next_node[edge];
	}
	trie[n].flag = true;
	trie[n].templates_number = index;
}

int Trie::GetSuffixLink(int node)
{
	if (trie[node].suffix_link == -1)
		if (node == 0 || trie[node].parent == 0)
			trie[node].suffix_link = 0;
	else
		trie[node].suffix_link = GetMovement(GetSuffixLink(trie[node].parent), trie[node].key);
	return trie[node].suffix_link;
}

int Trie::GetMovement(int node, int edge)
{
	if (trie[node].movement[edge] == -1)
		if (trie[node].next_node[edge] != -1)
			trie[node].movement[edge] = trie[node].next_node[edge];
		else
			if (node == 0)
				trie[node].movement[edge] = 0;
			else
				trie[node].movement[edge] = GetMovement(GetSuffixLink(node), edge);
	return trie[node].movement[edge];
}

void Trie::Result(std::vector <std::string>& templates, int node, int symbol_number, std::string text)
{
	for(int i = node; i != 0; i = GetSuffixLink(i))
		if (trie[i].flag)
			output.push_back(std::make_pair(symbol_number - templates[trie[i].templates_number].length() + 1, trie[i].templates_number + 1));
}

void Trie::MatchesSearch(std::vector <std::string> templates, std::string text, std::map<char, int> alphabet)
{
    int symbol_number = 0;
	int edge;
	for (int i = 0; i < text.length(); i++)
	{
		char symbol = text[i];
		edge = alphabet[symbol];
		symbol_number = GetMovement(symbol_number, edge);
		Result(templates, symbol_number, i + 1, text);
	}
}

int main()
{
	std::map<char, int> alphabet { {'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}, {'N', 4}};
	Trie trie;
	std::vector <std::string> templates;
	std::string text;
	int templates_quantity;
	std::string template_string;
	std::cin >> text >> templates_quantity;
	for (int templates_number = 0; templates_number < templates_quantity; templates_number++)
	{
		std::cin >> template_string;
		trie.TrieAddNode(alphabet, templates_number, template_string);
		templates.push_back(template_string);
	}
	trie.MatchesSearch(templates, text, alphabet);
	sort(output.begin(), output.end());
	for (std::vector <std::pair<int, int>>::iterator iter = output.begin(); iter!=output.end(); ++iter)
		if (true)
			std::cout<< (*iter).first << ' ' << (*iter).second << "\n";
	return 0;
}
