#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>

template <class T>
class Input
{

public:
	T clearNums(const std::string& str) {
		std::string res= str;
		for (int i = 0; i < res.length(); i++)
		{
			if (res[i] > 47 && res[i] < 59) {
				res.erase(i, 1);
				i--;
			};
		}
		return res;
	}
	int AskNum() {
		int num;
		while (!(std::cin >> num) || (std::cin.peek() != '\n'))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			//std::cout << "Error!" << '\n';
		}
		return num;
	}
	T clearChars(const std::string& str) {
		std::string res = str;
		for (int i = 0; i < res.length(); i++)
		{
			if (res[i] >= 65 && res[i] <= 90|| res[i] >= 97 && res[i] <= 122) {
				res.erase(i, 1);
				i--;
			};

		}
		return res;
	}
	bool checkStrings(const std::string& str) {
		if (str.length() <= 1) {
			return false;
		}
		for (int i = 0; i < str.length(); i++) {
			if (!isdigit(str[i])) {
				return false;
			}
		}
		return true;
	}
	

	bool checkFileFolder(const std::string& filename) {
	std::fstream file;
	std::string filenameMain = "../users/" + filename + ".txt";
		if (fopen(filenameMain.c_str(), "r") == NULL)return false;
		else { return true; }
	}
};

