#include <iostream>
using namespace std;

class Stack {
private:
	struct Node {
		string data;
		Node* next;
		
		Node(const string& d, Node* n = nullptr)
			: data(d), next(n){ }

	};

	Node* top_;
	int count;
	
public:
	Stack() : top_(nullptr), count(0){}

	void Push(const string& value) {
		top_ = new Node(value, top_);
		count++;
	}

	void pop() {
		if (!top_) return;
		Node* old = top_;
		top_ = top_->next;
		delete old;
		count--;
	}

	string& top() {
		if (!top_) throw runtime_error("Stack is empty");
		return top_->data;
	}
	const string& top() const {
		if (!top_) throw runtime_error("Stack is empty");
		return top_->data;
	}

	int size() const {
		return count;
	}

	bool empty() const {
		return top_ == nullptr;
	}

	void clear() {
		while (top_) {
			pop();
		}
	}
};