#include "Address.h"

Address::Address(const string& country, const string& city, const string& street, int buildingNumber) // C'tor
	: country(country), city(city), street(street), buildingNumber(buildingNumber)
{
}

Address::Address(ifstream& inFile)
{
	int len;
	//COUNTRY
	inFile.read((char*)&len, sizeof(len));
	inFile.read((char*)&country, len);
	//country[len] = '\0';

	//CITY
	inFile.read((char*)&len, sizeof(len));
	inFile.read((char*)&city, len);
	//city[len] = '\0';

	//STREET
	inFile.read((char*)&len, sizeof(len));
	inFile.read((char*)&street, len);
	//street[len] = '\0';

	//BUILDINGNUMBER
	inFile.read((char*)&buildingNumber, sizeof(buildingNumber));
}

void Address::save(ofstream& outFile) const
{
	//COUNTRY
	int len = country.length();
	outFile.write((const char*)&len, sizeof(len));
	outFile.write((const char*)country.c_str(), len);

	//CITY
	len = city.length();
	outFile.write((const char*)&len, sizeof(len));
	outFile.write((const char*)city.c_str(), len);

	//STREET
	len = street.length();
	outFile.write((const char*)&len, sizeof(len));
	outFile.write((const char*)street.c_str(), len);

	//BUILDINGNUMBER
	outFile.write((const char*)&buildingNumber, sizeof(buildingNumber));
}

void Address::setCountry(const string& country)
{
	this->country = country;
}

void Address::setCity(const string& city)
{
	this->city = city;
}

void Address::setStreet(const string& street)
{
	this->street = street;
}

void Address::setBuildingNumber(int buildingNumber)
{
	this->buildingNumber = buildingNumber;
}

const string& Address::getCountry() const
{
	return country;
}

const string& Address::getCity() const
{
	return city;
}

const string& Address::getStreet() const
{
	return street;
}

int Address::getBuildingNumber() const
{
	return buildingNumber;
}

ostream& operator<<(ostream& os, const Address& address)
{
	os << address.street << " " << address.buildingNumber << ", " << address.city << ", " << address.country;
	return os;
}