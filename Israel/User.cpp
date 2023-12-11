#include "User.h"
#include <iostream>
#include <string>
#include "Input.h"
User::User() {
	this->setName("");
	this->setPassword("");
	this->setPhoneNum("");
	this->setBroker(false);
	
}
User::User(const std::string& name= "", const std::string& pass = "", const std::string& phone = "", bool isbr) {
	this->setName(name);
	this->setPassword(pass);
	this->setPhoneNum(phone);
	this->setBroker(isbr);
}
bool User::setName(const std::string newName) {
	if (newName == "") {
		return false;
	}
	this->name = newName;
	return true; 
}
bool User::setPassword(const std::string& newPassword) {
	this->password = newPassword;
	return true; // или false в зависимости от вашей логики
}
bool User::setPhoneNum(const std::string& newPhoneNum) {
	this->phoneNum = newPhoneNum;
	return true; // или false в зависимости от вашей логики
}
std::string User::getName() { return this->name; }
std::string User::getPassword() { return this->password; }
std::string User::getPhoneNum() { return this->phoneNum; }