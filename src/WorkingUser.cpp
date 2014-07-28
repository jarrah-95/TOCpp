/* 
 * File:   WorkingUser.cpp
 * Author: jarrah
 * 
 * Created on 28 July 2014, 3:29 PM
 */
#include <string>
#include <openssl/sha.h>
#include <cstring>
#include <exception>
class WorkingUser {
private:
	//CheckOut checkOuts;
	PersonDatabase personDatabase;
	ProductDatabase productDatabase;
	int userNumber;
public:
	WorkingUSer();
	void addDatabases();
	void addPersonToDatabase(std::string, long);
	void addProductToDatabase(std::string, long, long);
	bool addToCart(std::string);
	void adminWriteOutDatabase(std::string);
	void buyProducts();
	std::string getCheckOut();
	std::string* getCheckOutNames();
	std::string* getCheckOutPrices();
	void getPMKeyS(std::string);
	double getPrice();
	long getProductBarCode(int index);
	std::string* getProductNames();
	int getProductNumber(int);
	double getProductPrice(int);
	std::string getSecurePassword(std::string);
	std::string* getUserNames();
	bool isDouble(std::string);
	bool isInteger(std::string);
	bool isLong(std::string);
	void logOut();
	bool passwordsEqual(std::string);
	// scrollPane printDatabase(std::string);
	void removePerson(int);
	void removeProduct(int);
	void setAdminPassword(std::string);
	void setNumberOfProducts(int, int);
	void setUserCanBuy(int, bool);
	bool userCanBuy(int);
	std::string userName();
	int userNumber();
};
WorkingUser::WorkingUser()
{
	WorkingUser::productDatabase = new ProductDatabase();
	WorkingUser::personDatabase = new PersonDatabase();
	//WorkingUser::checkOuts = new CheckOut();
	WorkingUser::userNumber = -1;
}
void WorkingUser::addDatabases()
{
	int error = productDatabase.readDatabase("productDatabase.txt");
	if(error == -1) {
		printf("there was an error reading the productDatabase");
	}
	else {
		printf("I have imported %d products\n", error);
	}
	error = personDatabase.readDatabase("personDatabase.txt");
	if(error == -1) {
		printf("there was an error reading the personDatabase");
	}
	else {
		printf("I have imported %d people\n", error);
	}
}
void WorkingUser::getPMKeyS(std::string input)
{
	bool correct = false;
	bool broken = false;
	int first;
	if(!(input == '\0' || input == ""))  int first = input.at(0);
	else broken = true;
	if((first > 65 && first < 90) || (first > 97 && first < 122)) {
		input = input.substr(1, input.length(), std::string::size_type);
	}
	if(broken || !WorkingUser::isLong(input) || !personDatabase.personExists(std::stol(input, std::string::size_type))) {
		userNumber = -1;
	} 
	else {
		correct = true;
		userNumber = personDatabase.findPerson(stol(input, std::string::size_type));
	}
}
std::string* WorkingUser::getUserNames() 
{
	return personDatabase.getUserNames();
}
std::string* WorkingUser::getProductNames()
{
	return productDatabase.getProductNames();
}
std::string WorkingUser::getSecurePassword(std::string passwordToHash)
{
	char* unHashed = new char[passwordToHash.length()+1];
	for(int i = 0; i < passwordToHash.length(); i++) {
		unHashed[i] = passwordToHash.at(i);
	}
	unHashed[passwordToHash.length()+1] = '\0';
	char* hashed = new char[strlen(unHashed)];
	SHA1(unHashed, std::strlen(unHashed), hashed);
	std::string output(hashed);
	return output;
}
bool WorkingUser::passwordsEqual(std::string pw)
{
	std::string testing = WorkingUser::getSecurePassword(pw);
	return (testing == personDatabase.getPersonName(-2));
}
void WorkingUser::setAdminPassword(std::string pw)
{
	personDatabase.setAdminPassword(pw);
}
bool WorkingUser::isInteger(std::string s)
{
	try {
		std::stoi(s);
	}
	catch (exception& E) {
		return false;
	}
	return true;
}
bool WorkingUser::isLong(std::string s)
{
	try {
		std::stol(s);
	}
	catch (exception& E) {
		return false;
	}
	return true;
}
bool WorkingUser::isDouble(std::string s)
{
	try {
		std::stod(s);
	}
	catch (exception& E) {
		return false;
	}
	return true;
}
// scrollPane printDatabase goes here
void WorkingUser::logOut()
{
	userNumber = -1;
	//checkOuts = new CheckOut();
}
void WorkingUser::buyProducts()
{
//	WorkingUser::personDatabase.addCost(WorkingUser::userNumber, checkOuts.getPrice());
//	WorkingUser::checkOuts.productBought();
	WorkingUser::productDatabase.writeOutDatabase("productDatabase.txt");
	WorkingUser::personDatabase.writeOutDatabase("personDatabase.txt");
	WorkingUser::logOut();
}
std::string WorkingUser::getCheckOut()
{
	//return checkOuts.getCheckOut(1);
}
std::string* WorkingUser::getCheckOutNames()
{
	//return checkOuts.getCheckOutNames();
}
std::string* WorkingUser::getCheckOutPrices()
{
	//return checkOuts.getCheckOutPrices();
}
std::string WorkingUser::userName()
{
	return userNumber == -1 ? "error" : PersonDatabase.getPersonName(WorkingUser::userNumber);
}
// add to cart goes here;
int WorkingUser::userNumber()
{
	return userNumber;
}
double WorkingUser::getPrice()
{
	long price = checkOuts.getPrice();
	return ((double)price)/100;
}
void WorkingUser::addPersonToDatabase(std::string name, long PMKeyS)
{
	personDatabase.setDatabasePerson(personDatabase.emptyPerson(), name, 0,0, PMKeyS, true);
}
void WorkingUser::addProductToDatabase(std::string name, long barCode, long price)
{
	productDatabase.setDatabaseProduct(productDatabase.emptyProduct(), name, price, barCode);
}
void WorkingUser::adminWriteOutDatabase(std::string type)
{
	switch (type) {
		case "Person": personDatabase.adminWriteOutDatabase("adminPersonDatabase.txt");
						break;
		case "Product":productDatabase.adminWriteOutDatabase("adminProductDatabase.xt");
						break;
		default:personDatabase.adminWriteOutDatabase("adminPersonDatabase.txt");
	}
}
void WorkingUser::removePerson(int index)
{
	personDatabase.delPerson(index);
}
void WorkingUser::removeProduct(int index)
{
	productDatabase.delProduct(index);
}
long WorkingUser::getProductBarCode(int index)
{
	return productDatabase.getBarCode(index);
}
double WorkingUser::getProductPrice(int index)
{
	return productDatabase.getProductPrice(index);
}
int WorkingUser::getProductNumber(int index)
{
	return productDatabase.getNumber(index);
}
void WorkingUser::setNumberOfProducts(int index, int numberOfProducts)
{
	productDatabase.setNumber(index, numberOfProducts);
}
bool WorkingUser::userCanBuy(int index)
{
	return personDatabase.personCanBuy(index);
}
void WorkingUser::setUserCanBuy(int index, bool canBuy)
{
	personDatabase.setPersonCanBuy(index, canBuy);
}