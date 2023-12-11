#pragma warning(disable : 4996)
#include <iostream>
#include "User.h";
#include "Input.h"
#include "RealEstate.h"
#include "Property.h"
#include "Window.h"
using namespace std;

int main() {
	setlocale(0, "ukr");
	ASD::Window wind;
	Input<string> inp;
	RealEstate est;
	User user1("Name2", "pass2", "phone2", false);
	est.storeData(user1, user1.getName());
	
	
	
	int num = -1;
	while (num != 0) {
		wind.Clear();
		wind.DrawMenu(est.getIsLoggedIn());
		num = inp.AskNum();
		

		if(wind.GetPage()== 1){
			switch (num) {
			case 1: {
				wind.Clear();
				est.createUser();
				break;
			}
			case 2: {
				wind.Clear();
				est.logIn();
				break;
			}
			case 3: {
				wind.Clear();
				num = 0; // You probably meant to assign the value, not compare
				break;
			}
			case 4: {
				wind.SetPage();
				break;
			}

			}
		}
		if (wind.GetPage() == 2) {
			switch (num) {
			case 1: {
				wind.Clear();
				est.createProperty();
				break;
			}
			case 2: {
				wind.Clear();
				est.displayUsersProp();
				est.deleteProp();
				break;
			}
			case 3: {
				wind.Clear();
				est.ShowAllProperties();
				break;
			}
			case 4: {
				wind.Clear();
				est.displayUsersProp();
				break;
			}
			case 5: {
				wind.Clear();
				est.filterProp();
				break;
			}
			case 6: {
				num = 0;
			}
			}
		}
			
	}
	//est.readData(user1, "Name.txt");
	//user1.PrintData();
	//est.createUser();
	//est.logIn();
	//prop.displayCities();
	//cout << prop.checkCity("lalal");

	/*est.GetDataUsers();
	est.createProperty();
	est.createProperty();*/
	//est.ShowAllProperties();
	//est.filterProp();


	return 0;
}