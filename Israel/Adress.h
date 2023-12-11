#pragma once
#include <string>
#include <iostream>
#include <stdio.h>

class Adress {
protected:
	
	std::string cities[5] = { "Kiev", "Cherkasy", "Kharkow", "Lvov", "Dnepr" };

	std::string streets[10] = {
		"Khreshchatyk", "Velyka Vasylkivska",
		"Metalurhiv Avenue", "Tsentralna",
		"Sumska", "Pushkinska",
		"Prospect Svobody", "Doroshenka",
		"Naberezhna Pobedy", "Kirova"
	};
	std::string street;
	std::string city;

public:

	Adress() {
		this->city = "";
		this->street = "";
	}
	virtual void PrintData() = 0;
	std::string getAdress() {
		return this->street;
	}
	std::string getCity() {
		return this->city;
	}
	bool checkCity(const std::string& cityInp) {
		for (const auto& city : this->cities) {
			if (city == cityInp) {
				this->setCity(city);
				return true;
			}
		}
		return false;
	}
	bool CheckStreet(const std::string& streetInp) {
		for (const auto& street : this->streets) {
			if (street == streetInp) {
				this->setStreet(street);
				return true;
			}
		}
		return false;
	}
	Adress& setCity(const std::string& city) {
		this->city = city;
		return *this;
	}
	Adress& setStreet(const std::string& street) {
		this->street = street;
		return *this;
	}
	void displayCities() {
		for (const auto& city : cities) {
			std::cout << city << "\n";
		}
	}
	void displaystreets() {
		for (const auto& street : streets) {
			std::cout << street << "\n";
		}
	}
};