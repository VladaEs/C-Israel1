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
		std::cout << "Ви перейшли в меню для створення користувача!\n\n";
		std::cout << "Введіть ім'я користувача:";
		std::string name = "";
		std::cin >> name;
		while (inp.checkFileFolder(name)) {
			std::cout << "Введіть інше ім'я, це вже зайняте\n";
			std::cin >> name;
		}
		std::cout << "\nІм'я зареєстровано правильно\n\n";
		std::cout << "Введіть, пароль:\n";
		std::string pass = "";
		std::cin >> pass;
		while (pass.length() <= 4) {
			std::cout << "пароль повинен бути довшим за 4 символи\n";
			std::cin >> pass;
		}
		std::cout << "\nПароль зареєстровано правильно\n\n";
		std::cout << "Введіть, номер телефону:\n";
		std::string phone;
		while (phone.length() !=10) {
			std::cin >> phone;
			phone = inp.clearChars(phone);
		}
		std::cout << "\nТелефон зареєстровано правильно\n\n";
		std::cout << "\nВи будете брокером чи звичайним користувачем? 0-звичайний 1-брокер \n\n";
		short brok = 0;
		std::cin >> brok;
		while (brok != 0 && brok != 1) {
			std::cout << "Введіть правильно!!!\n";
			std::cout << "\nВи будете брокером чи звичайним користувачем? 0-звичайний 1-брокер \n\n";
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
			std::cout << "\n У вас дуже багато публікацій";
			_getch();
			return;
		}
		if (users[currentUser].getBroker() == 1 && users[currentUser].getAmount() >9) {
			std::cout << "\n У вас дуже багато публікацій";
			_getch();
			return;
		}
		Property prop;
		std::cout << "Ви перейшли в меню для створення публікації!\n\n";
		std::cout << "Введіть назву міста із запропонованих:\n\n";
		prop.displayCities();
		std::cout << "\n\n";
		std::string city;
		while (!inp.checkStrings(city) && !prop.checkCity(city)) {
			std::cout << "Місто: ";
			std::cin >> city;
		}
		std::cout << "Все вірно";
		std::cout << "\nВведіть назву вулиці із запропонованих:\n\n";
		prop.displaystreets();
		std::cout << "\n\n";
		std::string street;
		while (!inp.checkStrings(street) && !prop.CheckStreet(street)) {
			std::cout << "Вулиця:";
			std::cin >> street;
		}
		std::cout << "Все вірно\n";
		std::cout << "Який тип мешкання у вас (введіть число):\n";
		prop.showPropType();
		int propType=10;
		std::cin >> propType;
		while (!prop.checkPropType(propType)) {
			std::cout << "Невірно\n";
			std::cin >> propType;
		}
		std::cout << "\nВсе вірно\n";
		std::cout << "\nСкільки поверхів у вас: ";
		int floors = 0;
		std::cin >> floors;
		std::cout << "\nСкільки кімнат у вас: ";
		int rooms = 0;
		std::cin >> rooms;

		std::cout << "\nЯкий номер дому: ";
		int HouseNum= 0;
		std::cin >> HouseNum;
		int rent;
		std::cout << "\nЧи ви будете здавати помешкання чи продавати(виберіть номер) : ";
		std::cout << "\n1. Сдавати\n";
		std::cout << "2. Продавати\n";
		std::cin >> rent;
		while (rent != 1 && rent != 2) {
			std::cout << "Невірно";
			std::cin >> rent;
		}
		if (rent == 1) rent = true;
		if (rent == 2) rent = false;

		std::cout << "\nЯка ціна: ";
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
				std::cout << "Нeчего удалять\n";
				return false;
			}
			int propNum = 0;
			std::cout << "Какое имущество Вы хотите удалить? Напишите номер по порядку:";
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
		std::cout << "Вы хотите видеть имущество которое сдается или продается?\n 1.Сдается \n 2.Продается\n";
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
		std::cout << "Какой тип имущества Вам нужен:";
		properties[0].showPropType();
		short propType = 0;
		while (propType != 1 && propType != 2 && propType != 3) {
			std::cout << "Введите номер:";
			std::cin >> propType;
		}
		std::cout << "Сколько комнат вы хотите:";
		
		short roomAmount = 0;
		std::cout << "Введите количество комнат :";
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
			std::cout << "Нет публикаций которые бы подходили под ваши параметры\n";
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
				std::cout << "нет публикаций";
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
			std::cout<< "Ошибка открытия файла для записи: " << filePath << std::endl;
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
			std::cerr << "Ошибка открытия файла для чтения: " << filePath << std::endl;
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

		std::cout << "Введіть ім'я користувача:";
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
		
		std::cout << "\nВведіть, пароль:\n";
		std::string pass = "";
		std::cin >> pass;
		while (pass != users[ind].getPassword()) {
			std::cout << "\nпароль невірний\n";
			std::cin >> pass;
		}
		std::cout << "Вітаю, раді Вас бачити знову\n";
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

