#include "Utils.h"

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