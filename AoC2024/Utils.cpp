#include "Utils.h"

namespace Utils {
std::string Utils::loadFile(std::string path) {
	std::ifstream file;
	file.open(path, std::ifstream::in);
	std::string result;

	char nextChar;
	while (file.get(nextChar)) {
		result += nextChar;
	}

	file.close();
	return result;
}

std::vector<std::string> Utils::split(std::string str, std::string splitter) {
	std::vector<std::string> result;
	int index = 0;
	int oldIndex = 0;
	while (index != -1) {
		index = str.find(splitter, oldIndex);
		if (index > -1) {
			result.push_back(str.substr(oldIndex, index - oldIndex));
			oldIndex = index + splitter.size();
		}
		else {
			if (oldIndex < str.size()) {
				result.push_back(str.substr(oldIndex, str.size()));
				oldIndex = str.size();
			}
		}
	}
	return result;
}

void Utils::copy(std::string str) {
	HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, str.size() + 1);
	memcpy(GlobalLock(mem), str.c_str(), str.size() + 1);
	GlobalUnlock(mem);
	if (OpenClipboard(NULL) == 0 || EmptyClipboard() == 0 || SetClipboardData(CF_TEXT, mem) == NULL || CloseClipboard() == 0) {
		std::cout << "Failed to copy string \"" << str << "\" to clipboard.\n";
	}
}

Vector2ll::Vector2ll() {
	x = 0;
	y = 0;
}

Vector2ll::Vector2ll(long long x, long long y) {
	this->x = x;
	this->y = y;
}

Vector2ll::~Vector2ll() {

}

Vector2ll Vector2ll::operator+(const Vector2ll& other) const {
	return Vector2ll(x + other.x, y + other.y);
}

Vector2ll Vector2ll::operator-(const Vector2ll& other) const {
	return Vector2ll(x - other.x, y - other.y);
}

Vector2ll Vector2ll::operator*(const long long& other) const {
	return Vector2ll(x * other, y * other);
}

Vector2ll Vector2ll::operator/(const long long& other) const {
	return Vector2ll(x / other, y / other);
}

Vector2ll& Vector2ll::operator=(const Vector2ll& other) {
	x = other.x;
	y = other.y;
	return *this;
}

Vector2ll& Vector2ll::operator+=(const Vector2ll& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2ll& Vector2ll::operator-=(const Vector2ll& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2ll& Vector2ll::operator*=(const long long& other) {
	x *= other;
	y *= other;
	return *this;
}

Vector2ll& Vector2ll::operator/=(const long long& other) {
	x /= other;
	y /= other;
	return *this;
}

bool Vector2ll::operator==(const Vector2ll& other) const {
	return x == other.x && y == other.y;
}

bool Vector2ll::operator!=(const Vector2ll& other) const {
	return x != other.x || y != other.y;
}

bool Vector2ll::operator<(const Vector2ll& other) const {
	if (x != other.x) return x < other.x;
	return y < other.y;
}
}