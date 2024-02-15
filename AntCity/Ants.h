#pragma once

#include "Utils.h"

enum class Atypes {
	queen,
	worker
};

class AntBase {
protected:
	strhash dna;
	inline virtual void SetDNAs(const strvec& data) { /**/ }

public:

	AntBase() = default;

	void GetQueenWorker(strvec& input, int& num1, int& num2) const {
		std::istringstream iss(input[0]);

		if (iss >> num1 >> num2) {
#ifdef DEBUG
			Ok("Got the number of queens and kings");
#endif // DEBUG

			input.erase(input.begin());
		}
		else
		{
#ifdef DEBUG
			Err("Failed to extract numbers from the string");
#endif // DEBUG
		}
	}
	void InitDNA(const strvec& data, int queensCount, strvec& queens, strvec& workers) const {
		queens.insert(queens.end(), data.begin(), data.begin() + queensCount);
		workers.insert(workers.end(), data.begin() + queensCount, data.end());
#ifdef DEBUG
		Ok("Seperated the DNAs");
#endif // DEBUG
	}
};

class Worker final : protected AntBase {
public:
	Worker() = default;
	explicit Worker(strvec const& dnas) {
		this->dna.VecToSet(dnas);
	}

	Atypes type() const {
		return Atypes::worker;
	}

	inline strhash GetDna() const { return dna; }

	inline void SetDNAs(const strvec& data) override { dna.VecToSet(data); }
};

class Queen final : protected AntBase {
private:
	bool KMP(const string& pattern, const string& text) const {
		size_t patternLength = pattern.length();
		size_t textLength = text.length();

		std::vector<int> lps(patternLength);
		LPSArray(pattern, lps);

		int textIndex = 0;
		int patternIndex = 0;

		while ((textLength - textIndex) >= (patternLength - patternIndex)) {
			if (pattern[patternIndex] == text[textIndex]) {
				patternIndex++;
				textIndex++;
			}

			if (patternIndex == patternLength) {
				return true;
			}
			else if (textIndex < textLength && pattern[patternIndex] != text[textIndex]) {
				if (patternIndex != 0)
					patternIndex = lps[patternIndex - 1];
				else
					textIndex = textIndex + 1;
			}
		}
		return false;
	}

	void LPSArray(const string& pattern, std::vector<int>& lps) const {
		int previousLength = 0;
		lps[0] = 0;

		int currentIndex = 1;

		while (currentIndex < pattern.length()) {
			if (pattern[currentIndex] == pattern[previousLength]) {
				previousLength++;
				lps[currentIndex] = previousLength;
				currentIndex++;
			}
			else {
				if (previousLength != 0) {
					previousLength = lps[previousLength - 1];
				}
				else {
					lps[currentIndex] = 0;
					currentIndex++;
				}
			}
		}
	}
public:
	Queen() = default;
	explicit Queen(strvec const& dnas) { this->dna.VecToSet(dnas); }

	Atypes type() const { return Atypes::queen; }

	auto Breed(Worker const& workers) const {
		auto qDna = this->dna.getAllValues();
		auto wDna = workers.GetDna().getAllValues();
		strhash result;

		for (const auto& queen : qDna) {
			for (const auto& worker : wDna) {
				for (size_t len = 1; len <= queen.size(); len++) {
					string queenSubDna = queen.substr(0, len);

					if (KMP(queenSubDna, worker))
						result.insert(queenSubDna);
				}
			}
		}

		return result;
	}

	inline void SetDNAs(const strvec& data) override { dna.VecToSet(data); }
};