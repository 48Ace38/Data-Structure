#include <iostream>
using namespace std;

class Node {
public: 
	int key;
	Node* left;
	Node* right;
	int height;

	Node(int val) {
		key = val;
		left = right = nullptr;
		height = 1;
	}
};

class AVL {
private:
	Node* root;

	int get_height(Node* n) {
		return n ? n->height : 0;
	}

	int get_balance(Node* n) {
		if (!n) return 0;
		return get_height(n->right) - get_height(n->left);
	}

	Node* right_rotation(Node* y) {
		Node* x = y->left;
		Node* temp = x->right;

		x->right = y;
		y->left = temp;

		y->height = 1 + max(get_height(y->left), get_height(y->right));
		x->height = 1 + max(get_height(x->left), get_height(x->right));

		return x;
	}

	Node* left_rotation(Node* x) {
		Node* y = x->right;
		Node* temp = y->left;

		y->left = x;
		x->right = temp;

		x->height = 1 + max(get_height(x->left), get_height(x->right));
		y->height = 1 + max(get_height(y->left), get_height(y->right));

		return y;
	}

	Node* min_value(Node* node) {
		Node* current = node;
		while (current->left != nullptr)
			current = current->left;
		return current;
	}

	Node* max_value(Node* node) {
		Node* current = node;
		while (current->right != nullptr)
			current = current->right;
		return current;
	}

	Node* find_successor(Node* node) {
		if (!node || !node->right) return nullptr;
		return min_value(node->right);
	}

	Node* find_predecessor(Node* node) {
		if (!node || !node->left) return nullptr;
		return max_value(node->left);
	}

	Node* insert(Node* node, int key) {
		if (!node) return new Node(key);

		if (key < node->key)
			node->left = insert(node->left, key);
		else if (key > node->key)
			node->right = insert(node->right, key);
		else
			return node;

		node->height = 1 + max(get_height(node->left), get_height(node->right));
		int balance = get_balance(node);

		if (balance > 1) {
			if (key > node->right->key) {
				return left_rotation(node);
			}
			else {
				node->right = right_rotation(node->right);
				return left_rotation(node);
			}
		}
		if (balance < -1) {
			if (key < node->left->key) {
				return right_rotation(node);
			}
			else {
				node->left = left_rotation(node->left);
				return right_rotation(node);
			}
		}
		return node;
	}

	Node* remove(Node* node, int key) {
		if (!node) return node;

		if (key < node->key)
			node->left = remove(node->left, key);
		else if (key > node->key)
			node->right = remove(node->right, key);
		else {
			if (!node->left || !node->right) {
				Node* temp = node->left ? node->left : node->right;
				if (!temp) {
					temp = node;
					node = nullptr;
				}
				else {
					*node = *temp;
				}
				delete temp;
			}
			else {
				Node* temp = find_successor(node);
				node->key = temp->key;
				node->right = remove(node->right, temp->key);
			}
		}
		if (!node) return node;

		node->height = 1 + max(get_height(node->left), get_height(node->right));
		int balance = get_balance(node);

		if (balance > 1) {
			if (get_balance(node->right) >= 0) {
				return left_rotation(node);
			}
			else {
				node->right = right_rotation(node->right);
				return left_rotation(node);
			}
		}
		if (balance < -1) {
			if (get_balance(node->left) <= 0) {
				return right_rotation(node);
			}
			else {
				node->left = left_rotation(node->left);
				return right_rotation(node);
			}
		}
		return node;
	}

	void inorder(Node* node) {
		if (!node) return;
		inorder(node->left);
		cout << node->key << " ";
		inorder(node->right);
	}

	public:
		AVL() {
			root = nullptr;
		}

		void insert(int key) {
			root = insert(root, key);
		}

		void remove(int key) {
			root = remove(root, key);
		}

		void print_inorder() {
			inorder(root);
			cout << endl;
		}

		Node* get_root() {
			return root;
		}

		int get_successor(int key) {
			Node* node = root;
			Node* succ = nullptr;
			while (node) {
				if (key < node->key) { 
					succ = node;
					node = node->left; }
				else node = node->right;
			}
			return succ ? succ->key : -1;
		}

		int get_predecessor(int key) {
			Node* node = root;
			Node* pred = nullptr;
			while (node) {
				if (key > node->key) { 
					pred = node;
					node = node->right; }
				else node = node->left;
			}
			return pred ? pred->key : -1;
		}
};

int main() {
	AVL tree;
	tree.insert(10);
	tree.insert(20);
	tree.insert(40);
	tree.insert(30);
	tree.insert(50);
	tree.insert(25);

	cout << "Inorder of AVL: ";
	tree.print_inorder();

	tree.remove(40);
	cout << "After removing 40: ";
	tree.print_inorder();

	tree.remove(30);
	cout << "After removing 30: ";
	tree.print_inorder();

	cout << "Successor of 25: " << tree.get_successor(25) << endl;
	cout << "Predecessor of 25: " << tree.get_predecessor(25) << endl;

	return 0;
}