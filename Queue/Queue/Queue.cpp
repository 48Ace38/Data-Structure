#include <iostream>
using namespace std;

class Queue {
private:
	struct Node {
		string data;
		Node* next;

		Node(const string& d, Node* n=nullptr)
			: data(d), next(n){ }
	};

	Node* front_;
	Node* rear_;
	int count;

public:
	Queue() : front_(nullptr), rear_(nullptr), count(0){}

	void enqueue(const string& value) {
		Node* newNode = new Node(value);
		if (!rear_) {
			front_ = rear_ = newNode;
		}
		else {
			rear_->next = newNode;
			rear_ = newNode;
		}
		count++;
	}

	void dequeue() {
		if (!front_) return;
		Node* old = front_;
		front_ = front_->next;
		if (!front_)
			rear_ = nullptr;
		delete old;
		count--;
	}

	string& front() {
		if (!front_) throw runtime_error("Queue is empty");
		return front_->data;
	}

	const string& front() const {
		if (!front_) throw runtime_error("Queue is empty");
		return front_->data;
	}

	bool empty() const {
		return front_ == nullptr;
	}

	int size() const {
		return count;
	}

	void clear() {
		while (front_) {
			dequeue();
		}
	}
};