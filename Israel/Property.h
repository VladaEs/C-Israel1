#pragma once
#include "Adress.h";
#include <string>
class Property :public Adress {
	
	short floor, rooms, houseNum;
	bool isRent;
	double price;
	std::string propType;
	std::string userName;
public:
	Property() {
		
		this->floor, this->rooms, this->houseNum, this->price = 0;
		this->isRent = false; // false = продается тру - аренда
		this->propType = "";
		this->userName = "";
	}
	// Геттеры
	std::string getPropType() {
		return this->propType;
	}
	std::string getPropType(short num) {
		std::string propTypes[3] = { "Стандартная квартира", "Квартира-пентхаус", "Частный дом" };
		return propTypes[num-1];
	}
	std::string getUserName() {
		return this->userName;
	}
	short getFloor() {

		return this->floor;
	}
	short getRooms() {
		return this->rooms;
	}
	short getHouseNum() {
		return this->houseNum;
	}
	bool getIsRent() {
		return this->isRent;
	}
	double getPrice() {
		return this->price;
	}
	// Сеттеры
	Property& setUserName(std::string name) {
		this->userName = name;
		return *this;
	}
	bool checkPropType(short num) {
		if (num >= 1 && num <= 3) {
			return true;
		}
		else return false;
	}
	Property& setPropType(short num) {
		std::string propTypes[3] = { "Стандартная квартира", "Квартира-пентхаус", "Частный дом" };
		if (this->checkPropType(num)) {
			this->propType = propTypes[num - 1];
		}
		return *this;
	}
	void showPropType() {
		std::string propTypes[3] = { "Стандартная квартира", "Квартира-пентхаус", "Частный дом" };
		for (int i = 0; i < 3; i++) {
			std::cout<< i + 1 <<". " << propTypes[i]<<"\n";
		}
	}
	Property& setRooms(short newRooms) {
		if (newRooms >= 1) {
			this->rooms = newRooms;
		}
		return *this;
	}

	Property& setHouseNum(short newHouseNum) {
		this->houseNum = newHouseNum;
		return *this;
	}

	Property& setIsRent(bool newIsRent) {
		this->isRent = newIsRent;
		return *this;
	}

	Property& setPrice(double newPrice) {
		if (newPrice >= 1) {
			this->price = newPrice;
		}
		return *this;
	}
	Property& setFloor(short num) {
		this->floor = num;
		return *this;
	}
	virtual void PrintData() override {
		std::cout << "city:" << this->getCity() << "\nstreet:" << this->getAdress() << "\nfloor:" << this->getFloor() << "\nrooms:" << this->getRooms() << "\nhouse Number:" << this->getHouseNum()
			<< "\nType:" << (this->getIsRent() ? "Аренда": "Купівля") << "\nprice:" << this->getPrice() << "\npropType:" << this->getPropType().c_str();
	}


};

