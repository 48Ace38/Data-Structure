#include<iostream>
using namespace std;

class max_heap {
private:
	int* heap;
	int capacity;
	int current_size;

	int parent(int i) {
		return (i - 1) / 2;
	}
	int left(int i) {
		return 2 * i + 1;
	}
	int right(int i) {
		return 2 * i + 2;
	}

	void down_heapify(int i) {
		int largest = i;
		int l = left(i);
		int r = right(i);

		if (l < current_size && heap[l] > heap[largest])
			largest = l;
		if (r < current_size && heap[r] > heap[largest])
			largest = r;

		if (largest != i) {
			swap(heap[i], heap[largest]);
			down_heapify(largest);
		}
	}
	void up_heapify(int i) {
		while (i > 0 && heap[parent(i)] < heap[i]) {
			swap(heap[i], heap[parent(i)]);
			i = parent(i);
		}
	}

public:
	max_heap(int cap) {
		capacity = cap;
		current_size = 0;
		heap = new int[capacity];
	}

	~max_heap() {
		delete[] heap;
	}

	void insert(int key) {
		if (current_size == capacity) {
			cout << "Heap overflow" << endl;
			return;
		}
		heap[current_size] = key;
		up_heapify(current_size);
		current_size++;
	}

	int extract_max() {
		if (current_size <= 0) {
			throw runtime_error("Heap is empty");
		}
		int max_value = heap[0];
		heap[0] = heap[current_size - 1];
		current_size--;
		down_heapify(0);
		return max_value;
	}

	int get_max() {
		if (current_size <= 0) {
			throw runtime_error("Heap is empty");
		}
		return heap[0];
	}

	void print_heap() {
		for (int i = 0; i < current_size; i++) {
			cout << heap[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	max_heap h(20);

	h.insert(10);
	h.insert(12);
	h.insert(27);
	h.insert(8);

	cout << "Heap elements: ";
	h.print_heap();

	cout << "Max element: " << h.get_max() << endl;
	cout << "Extracted max: " << h.extract_max() << endl;
	cout << "Heap after extraction: ";
	h.print_heap();

	return 0;
}