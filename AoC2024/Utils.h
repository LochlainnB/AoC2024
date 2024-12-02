#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

class Utils {
public:
	// Loads the given file into a 2D vector of strings vec[line][element]
	static std::string loadFile(std::string path);
	// Splits a string by the given splitter, returning a vector of the new substrings
	static std::vector<std::string> split(std::string str, std::string splitter);
	// Copies the given string to the Windows clipboard
	static void copy(std::string str);
	// Copies the given integer to the Windows clipboard
	static inline void copy(long long integer) { copy(std::to_string(integer)); }
};