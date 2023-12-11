#pragma once
#include <iostream>
#include <string>


class User
{
	std::string name;
	std::string password;
	std::string phoneNum;
	bool broker;
	short amountPubl=0;
public:

	User(const std::string& name, const std::string& pass, const std::string& phone, bool isbr = false);
	User();

	friend std::ostream& operator<<(std::ostream& os, const User& user)
	{
		// Сериализация объекта в поток вывода
		os << user.name << " " << user.password << " " << user.phoneNum << " " << user.broker;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, User& user)
	{
		// Десериализация объекта из потока ввода
		is >> user.name >> user.password >> user.phoneNum >> user.broker;
		return is;
	}
	bool setName(const std::string newName);
	bool setPassword(const std::string& newPassword);
	bool setPhoneNum(const std::string& newPhoneNum);
	bool setBroker(bool val) {
		this->broker = val;
		return true;
	}
	bool getBroker() {
		return this->broker;
	}
	std::string getName();
	std::string getPassword();
	std::string getPhoneNum();
	short getAmount() {
		return this->amountPubl;
	}
	short addAmount() {
		return this->amountPubl+=1;
	}
	short removeAmount() {
		return this->amountPubl -=1 ;
	}
	short SetAmount(short num){
		this->amountPubl = num;
		return this->amountPubl;
	}
	void PrintData() {
		std::cout << "\nname:" << this->getName() << "\tpassword:" << this->getPassword() << "\tphone:" << this->getPhoneNum() << "\tbroker:" << this->getBroker()<<"\n\n";
	}

};

