#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

namespace Utils {
// Loads the given file into a 2D vector of strings vec[line][element]
std::string loadFile(std::string path);
// Splits a string by the given splitter, returning a vector of the new substrings
std::vector<std::string> split(std::string str, std::string splitter);
// Copies the given string to the Windows clipboard
void copy(std::string str);
// Copies the given integer to the Windows clipboard
inline void copy(long long integer) { copy(std::to_string(integer)); }

// Alternative to std::pair<long long, long long> with some vector arithmetic added
class Vector2ll {
public:
	Vector2ll();
	Vector2ll(long long x, long long y);
	~Vector2ll();

	Vector2ll operator+(const Vector2ll& other) const;
	Vector2ll operator-(const Vector2ll& other) const;
	Vector2ll operator*(const long long& other) const;
	Vector2ll operator/(const long long& other) const;

	Vector2ll& operator=(const Vector2ll& other);
	Vector2ll& operator+=(const Vector2ll& other);
	Vector2ll& operator-=(const Vector2ll& other);
	Vector2ll& operator*=(const long long& other);
	Vector2ll& operator/=(const long long& other);

	bool operator==(const Vector2ll& other) const;
	bool operator!=(const Vector2ll& other) const;

	// For std::set, not comparing lengths
	bool operator<(const Vector2ll& other) const;

	long long x;
	long long y;
};
};