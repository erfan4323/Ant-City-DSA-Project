/*
// non-standard libraries

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "fmt/ranges.h"
#include "fmt/color.h"

// to enabling debug
#define DEBUG

// self includes
#include "Ants.h"
#include "File.h"
#include "Serialization.h"
#include "Utils.h"

using namespace fmt;

TEST_CASE("Testing")
{
	print(fg(color::aqua), "Test logs : \n");

	// initial datas
	AntBase antHandler; // for getting the DNAs
	strvec data;		// the data we will get from prents.txt
	strvec workers;		// workers dna
	strvec queens;		// queens dna
	int queensCount;	// ants count
	int workersCount;	// ants count

	SUBCASE("Ant testing")
	{
		// preparing data
		GatherData(data);

		SUBCASE("Testing types")
		{
			Worker worker;
			Queen queen;

			INFO("testing that we can create ants and check their type");
			CHECK(!(worker.type() == queen.type()));
		}

		SUBCASE("Getting the queens and workers")
		{
			// getting the number of queens and workers
			antHandler.GetQueenWorker(data, queensCount, workersCount);

			CHECK((queensCount == 1));
			CHECK((workersCount == 2));

			strvec expected = { "bcde", "bbb", "abcd" };
			CHECK_EQ(data, expected);
		}

		SUBCASE("Getting queens and workers DNA")
		{
			// preparing data
			antHandler.GetQueenWorker(data, queensCount, workersCount);
			antHandler.InitDNA(data, queensCount, queens, workers);

			strvec expectedQueens = { "bcde" };
			strvec expectedWorkers = { "bbb", "abcd" };
			CHECK_EQ(queens, expectedQueens);
			CHECK_EQ(workers, expectedWorkers);
		}

		SUBCASE("Inserting the dnas and breeding")
		{
			// preparing data
			antHandler.GetQueenWorker(data, queensCount, workersCount);
			antHandler.InitDNA(data, queensCount, queens, workers);

			Queen queenG;
			Worker workerG;

			queenG.SetDNAs(queens);
			workerG.SetDNAs(workers);

			auto resault = queenG.Breed(workerG);
			resault.print();
		}
	}

	SUBCASE("File Testing")
	{
		SUBCASE("Reading from file")
		{
			// getting data from parents.txt
			GatherData(data);

			strvec expected = { "1 2", "bcde", "bbb", "abcd" };
			CHECK_EQ(data, expected);
		}

		SUBCASE("Writing to file") {
			string content = "b bb bc bcd bcde";

			//WriteToOrder(content);
		}

		SUBCASE("Read From Order") {
			strvec res = ReadFromOrder();

			print("res: {}\n", res);
		}
	}

	SUBCASE("Hash Set Testing")
	{
		SUBCASE("base hash set tests")
		{
			strhash hset;

			CHECK(hset.isEmpty() == true);

			hset.insert("ad")
				.insert("rt")
				.insert("re")
				.insert("uy")
				.insert("fg")
				.insert("hk")
				.insert("hk")
				.insert("xc");

			hset.print();

			CHECK(hset.isEmpty() == false);
			CHECK(hset.size() == 7);

			hset.remove("fg");

			CHECK(hset.contains("fg") == false);
		}

		SUBCASE("vector to hash set tests")
		{
			strvec sample = { "bcde", "bbb", "abcd" };
			strhash hset;

			hset.VecToSet(sample);

			hset.print();
		}

		SUBCASE("iterate in hash set")
		{
			HashSet<int> mySet;

			mySet.insert(5);
			mySet.insert(10);
			mySet.insert(15);

			std::vector<int> allValues = mySet.getAllValues();

			for (const auto& value : allValues)
				std::cout << value << " ";

			std::cout << '\n';
		}
	}

	SUBCASE("Queue Testing")
	{
		SUBCASE("initial testing") {
			Queue<int> intQueue(5);

			CHECK(intQueue.Enqueue(1) == true);
			CHECK(intQueue.Enqueue(2) == true);
			CHECK(intQueue.Enqueue(3) == true);

			CHECK(intQueue.Count() == 3);

			CHECK(intQueue.GetFront() == 1);

			CHECK(intQueue.Contains(3) == true);

			intQueue.Dequeue();
			CHECK(intQueue.Count() == 2);

			CHECK(intQueue.Contains(1) == false);

			CHECK(intQueue.Enqueue(4) == true);
			CHECK(intQueue.Enqueue(5) == true);
			CHECK(intQueue.Enqueue(6) == true);

			CHECK(intQueue.Enqueue(6) == false);

			CHECK(intQueue.isEmpty() == false);

			intQueue.Dequeue();
			intQueue.Dequeue();
			intQueue.Dequeue();
			intQueue.Dequeue();
			intQueue.Dequeue();
			CHECK(intQueue.isEmpty() == true);

			intQueue.Dequeue();

			CHECK(intQueue.Count() == 0);
		}

		SUBCASE("iterating") {
			Queue<int> que;

			que.Enqueue(1);
			que.Enqueue(2);
			que.Enqueue(3);
			que.Enqueue(4);
			que.Enqueue(5);

			for (size_t i = 0; i < que.Count(); i++)
			{
				println("index {} is {}", i, que[i]);
			}
		}
	}

	SUBCASE("Testing Serializer")
	{
		SUBCASE("Getting city and validating it and saving it") {
			Encoder encode;
			encode.Initialize();

			int cap = 10;
			fmt::print("set the city capacity : (default is 10) ");
			std::cin >> cap;
			encode.CityCapacity(cap);

			fmt::print("Enter the citizens : (for getting out, press ctl+z and nothing else) \n");
			encode.GetCity();

			// Validated citizens
			encode.ValidateCity();

			encode.SaveToOrder();
		}

		SUBCASE("Reading from order") {
			Decoder decode;

			decode.ReadOrder();

			decode.PrintCity();
		}
	}
}

*/