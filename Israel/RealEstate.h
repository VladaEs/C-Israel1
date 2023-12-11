#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include "User.h"
#include "Input.h"
#include "Property.h"

class RealEstate{
	std::vector<Property> properties;
	std::vector<User> users;
	Input<std::string> inp;
	short currentUser;
	bool isLogedIn = false;
public:
	RealEstate() {
		Property propTemp1;
		propTemp1.setCity("Lvov").setStreet("Street 1");
		propTemp1.setPropType(1).setFloor(2).setRooms(4).setHouseNum(15).setIsRent(false).setPrice(2333).setUserName("Jack");
		this->AddEndProp(propTemp1);
		Property propTemp2;
		propTemp2.setCity("Kiev").setStreet("Street 2");
		propTemp2.setPropType(2).setFloor(4).setRooms(12).setHouseNum(20).setIsRent(true).setPrice(5000).setUserName("Josh");
		this->AddEndProp(propTemp2);
		this->GetDataUsers();
	}
	void createUser() {
		std::cout << "�� �������� � ���� ��� ��������� �����������!\n\n";
		std::cout << "������ ��'� �����������:";
		std::string name = "";
		std::cin >> name;
		while (inp.checkFileFolder(name)) {
			std::cout << "������ ���� ��'�, �� ��� �������\n";
			std::cin >> name;
		}
		std::cout << "\n��'� ������������ ���������\n\n";
		std::cout << "������, ������:\n";
		std::string pass = "";
		std::cin >> pass;
		while (pass.length() <= 4) {
			std::cout << "������ ������� ���� ������ �� 4 �������\n";
			std::cin >> pass;
		}
		std::cout << "\n������ ������������ ���������\n\n";
		std::cout << "������, ����� ��������:\n";
		std::string phone;
		while (phone.length() !=10) {
			std::cin >> phone;
			phone = inp.clearChars(phone);
		}
		std::cout << "\n������� ������������ ���������\n\n";
		std::cout << "\n�� ������ �������� �� ��������� ������������? 0-��������� 1-������ \n\n";
		short brok = 0;
		std::cin >> brok;
		while (brok != 0 && brok != 1) {
			std::cout << "������ ���������!!!\n";
			std::cout << "\n�� ������ �������� �� ��������� ������������? 0-��������� 1-������ \n\n";
			std::cin >> brok;
		}
		User user;
		user.setName(name);
		user.setPassword(pass);
		user.setPhoneNum(phone);
		user.setBroker(bool(brok));
		this->storeData(user, user.getName()).AddEnd(user);
	}
	//registration end==============================================

	//createProperty start==============================================
	void createProperty() {
		if (users[currentUser].getBroker() == 0 && users[currentUser].getAmount() >2) {
			std::cout << "\n � ��� ���� ������ ���������";
			_getch();
			return;
		}
		if (users[currentUser].getBroker() == 1 && users[currentUser].getAmount() >9) {
			std::cout << "\n � ��� ���� ������ ���������";
			_getch();
			return;
		}
		Property prop;
		std::cout << "�� �������� � ���� ��� ��������� ���������!\n\n";
		std::cout << "������ ����� ���� �� ��������������:\n\n";
		prop.displayCities();
		std::cout << "\n\n";
		std::string city;
		while (!inp.checkStrings(city) && !prop.checkCity(city)) {
			std::cout << "̳���: ";
			std::cin >> city;
		}
		std::cout << "��� ����";
		std::cout << "\n������ ����� ������ �� ��������������:\n\n";
		prop.displaystreets();
		std::cout << "\n\n";
		std::string street;
		while (!inp.checkStrings(street) && !prop.CheckStreet(street)) {
			std::cout << "������:";
			std::cin >> street;
		}
		std::cout << "��� ����\n";
		std::cout << "���� ��� �������� � ��� (������ �����):\n";
		prop.showPropType();
		int propType=10;
		std::cin >> propType;
		while (!prop.checkPropType(propType)) {
			std::cout << "������\n";
			std::cin >> propType;
		}
		std::cout << "\n��� ����\n";
		std::cout << "\n������ �������� � ���: ";
		int floors = 0;
		std::cin >> floors;
		std::cout << "\n������ ����� � ���: ";
		int rooms = 0;
		std::cin >> rooms;

		std::cout << "\n���� ����� ����: ";
		int HouseNum= 0;
		std::cin >> HouseNum;
		int rent;
		std::cout << "\n�� �� ������ ������� ���������� �� ���������(������� �����) : ";
		std::cout << "\n1. �������\n";
		std::cout << "2. ���������\n";
		std::cin >> rent;
		while (rent != 1 && rent != 2) {
			std::cout << "������";
			std::cin >> rent;
		}
		if (rent == 1) rent = true;
		if (rent == 2) rent = false;

		std::cout << "\n��� ����: ";
		double price = 0;
		std::cin >> price;
		users[currentUser].addAmount();
		prop.setCity(city).setStreet(street);
		prop.setPropType(propType).setFloor(floors).setRooms(rooms).setHouseNum(HouseNum).setIsRent(rent).setPrice(price).setUserName(this->users[currentUser].getName());
		this->AddEndProp(prop);
		
	}
	//createProperty end=================================================
	std::vector<User> clearUsers(){
		std::vector<User> result = this->users;
		this->users.clear();  // Clear the original vector
		return result;
	}

	void ShowAllProperties() {
		for (int i = 0; i < this->getAllProperties().size(); i++) {
			std::cout << i+1 << ". ";
			this->getAllProperties()[i].PrintData();
			std::cout << "\n\n";
		}
		_getch();
	}
	bool deleteProp() {
		short counter = 0;
		if (this->isLogedIn) {
			
			for (int i = 0;  i < this->getAllProperties().size(); i++) {
				if (properties[i].getUserName() == users[currentUser].getName()) {
					counter++;
				}
			}
			if (counter == 0) {
				std::cout << "�e���� �������\n";
				return false;
			}
			int propNum = 0;
			std::cout << "����� ��������� �� ������ �������? �������� ����� �� �������:";
			std::cin >> propNum;
			while (propNum > this->getAllProperties().size() || propNum <= 0) {
				std::cout << "error\n";
				std::cin >> propNum;
			}
			auto propIter = properties.begin();
			for (; propIter != properties.end(); ++propIter) {
				if (propIter->getUserName() == users[currentUser].getName()) {
					if (--counter == 0) {
						// Decrease counter and check if it matches propNum
						propIter = properties.erase(propIter);
						return true;
					}
				}
			}
			users[currentUser].removeAmount();
			return true;
		}
	}
	void filterProp() {
		std::cout << "�� ������ ������ ��������� ������� ������� ��� ���������?\n 1.������� \n 2.���������\n";
		short numRent= 0;
		bool rent = false;
		while(numRent!= 1&& numRent!= 2){
			std::cin >> numRent;
			if (numRent == 1) {
				rent = true;
			}
			if (numRent == 2) {
				rent = false;
			}
		}
		std::cout << "����� ��� ��������� ��� �����:";
		properties[0].showPropType();
		short propType = 0;
		while (propType != 1 && propType != 2 && propType != 3) {
			std::cout << "������� �����:";
			std::cin >> propType;
		}
		std::cout << "������� ������ �� ������:";
		
		short roomAmount = 0;
		std::cout << "������� ���������� ������ :";
		std::cin >> roomAmount;
		int amountProperties = 0;
		for (int i = 0; i < properties.size(); i++) {
			bool matches = true;

			// Check each criterion, skip if 999 was entered for that criterion
			if (propType != 999 && properties[i].getPropType() != properties[i].getPropType(propType)) {
				matches = false;
			}

			if (roomAmount != 999 && properties[i].getRooms() != roomAmount) {
				matches = false;
			}

			if (properties[i].getIsRent() != rent) {
				matches = false;
			}

			// If all criteria match, print or process the property
			if (matches) {
				properties[i].PrintData();
				amountProperties++;
			}

		}
		if (amountProperties == 0) {
			std::cout << "��� ���������� ������� �� ��������� ��� ���� ���������\n";
		}
		_getch();
	}

	void displayUsersProp() {
		if (this->isLogedIn) {
			int counter = 1;
			
			for (int i = 0; i < properties.size(); i++) {
				if (properties[i].getUserName() == users[this->currentUser].getName()) {
					std::cout << counter << ".";
					properties[i].PrintData();
					counter++;
					std::cout << "\n";
				}
			}
			if (counter == 1) {
				std::cout << "��� ����������";
			}
		}
		_getch();
	}
	std::vector<User> getAllUsers() {
		return this->users;
	}
	RealEstate& AddEnd(User& user) {
		this->users.push_back(user);
		return *this;
	}	
	RealEstate& AddEndProp(Property& prop) {
		this->properties.push_back(prop);
		return *this;
	}
	std::vector<Property> getAllProperties() {
		return this->properties;
	};
	RealEstate& storeData(User& user, const std::string& fileName) {
		const std::string directory = "../users/";
		const std::string filePath = directory + fileName + ".txt";
		std::ofstream outFile(filePath);
		if (outFile.is_open()) {
			outFile << user;
			outFile.close();
		}
		else {
			std::cout<< "������ �������� ����� ��� ������: " << filePath << std::endl;
		}
		return *this;
	}

	RealEstate& readData(User& user, const std::string& fileName) {
		const std::string directory = "../users/";
		const std::string filePath = directory + fileName;
		std::ifstream inFile(filePath);
		if (inFile.is_open()) {
			inFile >> user;
			inFile.close();
		}
		else {
			std::cerr << "������ �������� ����� ��� ������: " << filePath << std::endl;
		}
		return *this;
	}
	bool GetDataUsers() {
		this->clearUsers();
		WIN32_FIND_DATAA data;
		const char *path = "../users";
		char buf[_MAX_PATH + 1];
		strcpy_s(buf, _MAX_PATH + 1, path);
		strcat_s(buf, _MAX_PATH + 1, "\\*.txt");
		HANDLE h = ::FindFirstFileA(buf, &data);
		if (!h) {
			return false;
		}
		User user;
		this->readData(user, data.cFileName);
		this->users.push_back(user);
		while (FindNextFileA(h, &data)) {
			this->readData(user, data.cFileName);
			this->users.push_back(user);
			
			
		}
		FindClose(h);
	}
	
	

	bool logIn() {

		std::cout << "������ ��'� �����������:";
		std::string name = "";
		std::cin >> name;
		int ind = -1;
		for (int i = 0; i < users.size(); i++) {
			if (users[i].getName() == name) {
				ind = i;
				break; 
			}
		}
		if (ind == -1) {
			return false;
		}
		
		std::cout << "\n������, ������:\n";
		std::string pass = "";
		std::cin >> pass;
		while (pass != users[ind].getPassword()) {
			std::cout << "\n������ �������\n";
			std::cin >> pass;
		}
		std::cout << "³���, ��� ��� ������ �����\n";
		users[ind].PrintData();
		this->isLogedIn = true;
		this->currentUser = ind;
		return true;
	}
	short getCurrentUser() {
		return this->currentUser;
	}
	bool getIsLoggedIn() {
		return this->isLogedIn;
	}
};

