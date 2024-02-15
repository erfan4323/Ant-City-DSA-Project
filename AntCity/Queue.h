#pragma once

constexpr auto MAX_QUEUE = 10;

template<typename T>
class Queue {
private:
	uint32_t capacity;		// queue capacity
	uint32_t size;			// current queue size
	uint32_t front;			// index of the first element
	uint32_t rear;			// index of the last element
	T* elements;			// the elements

	Queue(const Queue&);
	Queue& operator=(const Queue&);
public:
	explicit Queue(uint32_t max) : capacity(max), size(0), front(0), rear(-1), elements(new T[max]) {}
	explicit Queue() : capacity(MAX_QUEUE), size(0), front(0), rear(-1), elements(new T[MAX_QUEUE]) {}
	~Queue() { delete[] elements; }

	bool Enqueue(const T& element) {
		if (size == capacity) return false;

		size++;
		rear++;

		if (rear == capacity)
			rear = 0;

		elements[rear] = element;

		return true;
	}

	void EnqueueVector(const std::vector<T>& vec) {
		for (const auto& element : vec)
			Enqueue(element);
	}

	inline void Dequeue() {
		if (size == 0) return;

		size--;
		front++;

		if (front == capacity)
			front = 0;
	}

	bool Contains(const T& value) const {
		for (size_t i = 0; i < size; ++i) {
			uint32_t index = (front + i) % capacity;
			if (elements[index] == value)
				return true;
		}
		return false;
	}

	inline const T& GetFront() const {
		if (size == 0) return -1;
		return elements[front];
	}

	inline bool isEmpty() const { return size == 0; }

	inline uint32_t Count() const { return size; }

	inline uint32_t Capcity() const { return capacity; }

	inline void SetCapcity(uint32_t val) { this->capacity = val; }

	const T& operator[](uint32_t index) const {
		if (index >= size)
			throw std::out_of_range("Index out of bounds");

		uint32_t actualIndex = (front + index) % capacity;
		return elements[actualIndex];
	}
};