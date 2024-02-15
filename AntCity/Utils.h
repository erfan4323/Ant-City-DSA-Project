#pragma once

// standart includes
#include <sstream>
#include <functional>
#include <chrono>
#include <iostream>

// non-standart includes
#include "fmt/ranges.h"
#include "fmt/color.h"

// self includes
#include "HashSet.h"
#include "Queue.h"

// type aliases
using string = std::string;
using strvec = std::vector<std::string>;
using strhash = HashSet<std::string>;
using strque = Queue<std::string>;

// macros
#define nameof(name) #name

#define Warn(message) \
    fmt::print(fg(fmt::color::light_yellow) | fmt::emphasis::bold, "Wanring: {}\n", message)

#define Err(message) \
    fmt::print(fg(fmt::color::orange_red) | fmt::emphasis::bold, "Error: {}\n", message)

#define Ok(message) \
    fmt::print(fg(fmt::color::light_green) | fmt::emphasis::bold, "Ok: {}\n", message)

// methods

strvec splitString(const string& inputString) {
	strvec result;
	std::istringstream stream(inputString);
	string line;

	while (std::getline(stream, line, '\n'))
		result.push_back(line);

	return result;
}

string joinStrings(const strvec& strings) {
	std::ostringstream result;

	for (size_t i = 0; i < strings.size(); ++i) {
		result << strings[i];

		if (i < strings.size() - 1)
			result << "\n";
	}

	return result.str();
}