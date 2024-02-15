#pragma once

template<class T>
class HashSet {
private:
	// const size
	static const int initialSize = 1000;

	// the table
	std::vector<std::list<T>> table;

	size_t elemCount;

	inline size_t Hash(T key, size_t tableSize) const { return std::hash<T>{}(key) % tableSize; }

public:
	HashSet() : table(initialSize), elemCount(0) {}

	explicit HashSet(const std::vector<T>& arr) : table(initialSize), elemCount(0) {
		for (const auto& val : arr)
			insert(val);
	}

	HashSet& insert(T key, bool rep = false) {
		if (!rep && contains(key)) return *this;

		size_t index = Hash(key, table.size());
		table[index].push_back(key);
		++elemCount;

		return *this;
	}

	HashSet& remove(T key) {
		size_t index = Hash(key, table.size());
		table[index].remove(key);
		--elemCount;

		return *this;
	}

	bool contains(T key) const {
		size_t index = Hash(key, table.size());

		for (const auto& val : table[index])
			if (val == key) return true;

		return false;
	}

	void VecToSet(const std::vector<T>& arr) {
		for (const auto& val : arr)
			insert(val);
	}

	std::vector<T> getAllValues() const {
		std::vector<T> values;

		for (const auto& bucket : table)
			for (const T& value : bucket)
				values.push_back(value);

		return values;
	}

	inline bool isEmpty() const { return elemCount == 0; }

	inline size_t size() const { return elemCount; }

#ifdef DEBUG
	void print() const {
		using namespace fmt;

		for (size_t i = 0; i < table.size(); ++i) {
			if (!table[i].empty()) {
				fmt::print(fg(color::dark_khaki), "Bucket {} \t", i);
				for (const T& key : table[i])
					fmt::print(fg(color::fire_brick), "{} \t", key);

				std::cout << '\n';
			}
		}
	}
#endif // DEBUG
};
