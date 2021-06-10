#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <sstream>
#include <algorithm>

class TrieNode{
public:
	int parent;
	char key;
	int next_node[5];
	std::vector <int> templates_number;
	bool flag = false;
	int suffix_link = -1;
	int movement[5];
	TrieNode(int, char);
	TrieNode() = default;
	~TrieNode() = default;
};

class Trie{
	std::vector <TrieNode> trie;
	std::vector < std::string > template_strings;
	int GetMovement(int node, int edge);
	int GetSuffixLink(int node);

public:
	Trie();
	~Trie() = default;
	void TrieAddNode(std::map<char, int> alphabet, std::string text);
	void MatchesSearch(std::map<char, int> alphabet, std::string &s, std::vector <int> & additional_array, const std::vector <int> & templates_length);
	void Result(int node, int i, std::vector <int> &additional_array, std::vector <int> templates_length);
	std::vector <int> Templates(std::map<char, int> alphabet, std::stringstream& template_string, char joker);
	void ResultPrint(const std::vector<int>& additional_array, int text_size, int length);
};

Trie::Trie(){
	trie.push_back(TrieNode(0,0));
}

TrieNode::TrieNode(int parent, char symbol){
	for (int i = 0; i < 5; i++){
		next_node[i] = -1;
		movement[i] = -1;
	}
	this->parent = parent;
	this->key = symbol;
	templates_number.resize(0);
}

void Trie::TrieAddNode(std::map<char, int> alphabet, std::string text){
	int new_node = 0;
	int edge = 0;
	for (int i = 0; i < text.length(); i++){
		char symbol = text[i];
		edge = alphabet[symbol];
		if (trie[new_node].next_node[edge] == -1){
			trie.push_back(TrieNode(new_node, edge));
			trie[new_node].next_node[edge] = trie.size() - 1;
		}
		new_node = trie[new_node].next_node[edge];
	}
	trie[new_node].flag = true;
	template_strings.push_back(text);
	trie[new_node].templates_number.push_back(template_strings.size() - 1);

}

int Trie::GetSuffixLink(int node){
	if (trie[node].suffix_link == -1)
		if (node == 0 || trie[node].parent == 0)
			trie[node].suffix_link = 0;
	else
		trie[node].suffix_link = GetMovement(GetSuffixLink(trie[node].parent), trie[node].key);
	return trie[node].suffix_link;
}

int Trie::GetMovement(int node, int edge){
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

void Trie::Result(int node, int i, std::vector <int>& additional_array, std::vector <int> templates_length){
	 for(int u = node; u != 0; u = GetSuffixLink(u))
		if (trie[u].flag){
			for (const auto &j : trie[u].templates_number)
				if ((i - templates_length[j] < additional_array.size()))
					additional_array[i - templates_length[j]]++;
		}
}

std::vector <int> Trie::Templates(std::map<char, int> alphabet, std::stringstream& template_string, char joker){
	std::vector < int > templates_length;
	int length = 0;
	std::string storage;
	while (getline(template_string, storage, joker)){
		if (storage.size() > 0){
			length += storage.size();
			templates_length.push_back(length);
			TrieAddNode(alphabet, storage);
		}
		length++;
	}
	return templates_length;
}

void Trie::ResultPrint(const std::vector<int>& additional_array, int text_size, int length){
	for (int i = 0; i < text_size; i++)
		if ((additional_array[i] == template_strings.size()) && (i + length <= text_size)){
			std::cout << i + 1 << "\n";
		}

}

void Trie::MatchesSearch(std::map<char, int> alphabet, std::string &text, std::vector <int> & additional_array, const std::vector <int> & templates_length){
	int edge;
	int u = 0;
	int lenght = text.length();
	for (int i = 0; i < lenght; i++){
		char symbol = text[i];
		edge = alphabet[symbol];
		u = GetMovement(u, edge);
		Result(u, i + 1, additional_array, templates_length);
	}
}

int main(){
	std::map<char, int> alphabet { {'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}, {'N', 4}};
	Trie trie;
	std::string text, template_string;
	char joker;
	std::cin >> text >> template_string >> joker;
	std::stringstream str_stream(template_string);
	std::vector <int> templates_length = trie.Templates(alphabet, str_stream, joker);
	std::vector <int> additional_array(text.length(), 0);
	trie.MatchesSearch(alphabet, text, additional_array, templates_length);
	trie.ResultPrint(additional_array, text.size(), template_string.length());
}
