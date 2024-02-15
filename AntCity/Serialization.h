#pragma once

#include "Utils.h"
#include "Ants.h"
#include "File.h"

class Encoder final
{
private:
	AntBase antHandler;						// for getting the DNAs
	strvec fileData;						// the data we will get from prents.txt

	Queen queens;							// queens that we will use
	int queensCount;						// ants count
	strvec queenDnas;						// queens dna

	Worker workers;							// workers that we will use
	int workersCount;						// ants count
	strvec workerDnas;						// workers dna

	strhash children;						// the children from breeding workers and queens
	strque city;							// the city that we will getting it from user
	strque validCity;						// this will be our output

	string ValidStr() const {
		std::stringstream res;

		for (size_t i = 0; i < validCity.Count(); i++)
		{
			res << validCity[i];

			if (i < validCity.Count() - 1)
				res << " ";
		}

		return res.str();
	}

public:
	Encoder() = default;
	~Encoder() = default;

	void Initialize() {
		// reading file
		GatherData(fileData);

		// setting data
		antHandler.GetQueenWorker(fileData, queensCount, workersCount);
		antHandler.InitDNA(fileData, queensCount, queenDnas, workerDnas);

		// setting dna
		queens.SetDNAs(queenDnas);
		workers.SetDNAs(workerDnas);

		// breeding
		children = queens.Breed(workers);
	}

	inline void CityCapacity(int val) { city.SetCapcity(val); }

	void GetCity() {
		string citizen;

		while (std::cin >> citizen && city.Enqueue(citizen));
	}

	void GetCity(strvec const& citizens) {
		city.SetCapcity(citizens.size());
		city.EnqueueVector(citizens);
	}

	void ValidateCity() {
		for (int i = 0; i < city.Count(); i++)
			if (children.contains(city[i]))
				validCity.Enqueue(city[i]);
	}

	inline void SaveToOrder() const { WriteToOrder(ValidStr()); }
};

class Decoder final
{
private:
	strvec OrderFileValues;

	strque ChildrenCity;

public:
	Decoder() = default;
	~Decoder() = default;

	void ReadOrder() {
		OrderFileValues = ReadFromOrder();

		ChildrenCity.EnqueueVector(OrderFileValues);
	}

	inline strvec ValidatedCitizens() const { return OrderFileValues; }

#ifdef DEBUG
	void PrintCity() const {
		std::cout << "City: (From Decoder)\n";

		for (size_t i = 0; i < ChildrenCity.Count(); i++)
			std::cout << ChildrenCity[i] << '\n';

		std::cout << "End OF City\n";
	}
#endif // DEBUG
};