#include <iostream>
#include <unordered_map>
using namespace std;

class Trie_node {
public:
	bool is_valid;
	unordered_map<char, Trie_node*> children;

	Trie_node() {
		is_valid = false;
	}
};

class Trie {
private:
	Trie_node* root;

public:
	Trie() {
		root = new Trie_node();
	}

	void insert(const string& word) {
		Trie_node* node = root;
		for (char ch : word) {
			if (node->children.find(ch) == node->children.end()) {
				node->children[ch] = new Trie_node();
			}
			node = node->children[ch];
		}
		node->is_valid = true;
	}

	bool search(const string& word) {
		Trie_node* node = root;
		for (char ch : word) {
			if (node->children.find(ch) == node->children.end()) {
				return false;
			}
			node = node->children[ch];
		}
		return node->is_valid;
	}

	bool starts_with(const string& prefix) {
		Trie_node* node = root;
		for (char ch : prefix) {
			if (node->children.find(ch) == node->children.end()) {
				return false;
			}
			node = node->children[ch];
		}
		return true;
	}
};

int main() {
	Trie trie;

	trie.insert("hello");
	trie.insert("helium");
	trie.insert("help");

	cout << boolalpha;
	cout << "Search hello: " << trie.search("hello") << endl;
	cout << "search hell: " << trie.search("hell") << endl;
	cout << "Search hell: " << trie.search("hell") << endl;
	cout << "Starts with hel: " << trie.starts_with("hel") << endl;
	cout << "Startswith hero: " << trie.starts_with("hero") << endl;

	return 0;
}
