#pragma once

#include "Utils.h"

void GatherData(strvec& data, const string& inptPath = "resources/parents.txt") {
	FILE* file = fopen(inptPath.c_str(), "r");
	char datatoread[50];

	if (file == nullptr)
	{
#ifdef DEBUG
		Err("Failed to open. (GatherData)");
#endif // DEBUG
	}

	else
	{
#ifdef DEBUG
		Ok("File opened.");
#endif // DEBUG

		while (fgets(datatoread, 50, file))
		{
			string bufs{ datatoread };
			bufs.erase(std::remove(bufs.begin(), bufs.end(), '\n'), bufs.end());
			data.push_back(bufs);
		}
	}

	if (file != nullptr && fclose(file))
		perror(inptPath.c_str());
}

void WriteToOrder(const string& content, const string& outptPath = "resources/order.txt") {
	FILE* file = fopen(outptPath.c_str(), "w");

	if (file == nullptr) {
#ifdef DEBUG
		Err("Error opening file. (writeToFile)");
#endif // DEBUG
		perror(outptPath.c_str());
	}
	else {
#ifdef DEBUG
		Ok("File opened.");
#endif // DEBUG

		if (ftell(file) != 0) {  // If the file is not empty, add a space before writing
			fprintf(file, " ");
		}

		size_t length = content.length();
		fwrite(content.c_str(), 1, length, file);

		if (fclose(file) != 0) {
#ifdef DEBUG
			Err("Error closing file. (writeToFile)");
#endif // DEBUG
			perror(outptPath.c_str());
		}
		else {
#ifdef DEBUG
			Ok("File closed.");
#endif // DEBUG
		}
	}
}

strvec ReadFromOrder(const string& path = "resources/order.txt")
{
	strvec values;

	FILE* file = fopen(path.c_str(), "r");

	if (file == nullptr) {
#ifdef DEBUG
		Err("Error opening file. (ReadFromOrder)");
#endif // DEBUG
	}
	else
	{
		char line[256];
		while (std::fgets(line, sizeof(line), file) != nullptr) {
			char const* token = std::strtok(line, " \n");
			while (token != nullptr) {
				values.push_back(token);
				token = std::strtok(nullptr, " \n");
			}
		}
	}

	if (fclose(file) != 0) {
#ifdef DEBUG
		Err("Error closing file. (writeToFile)");
#endif // DEBUG
		perror(path.c_str());
	}
	else {
#ifdef DEBUG
		Ok("File closed.");
#endif // DEBUG
	}
	return values;
}
