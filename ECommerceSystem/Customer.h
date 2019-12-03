#ifndef __CUSTOMER_H
#define __CUSTOMER_H

#include "OutResources.h"
#include "Product.h"
#include "Address.h"

class Checkout;

class Customer
{
private:
	char* username;
	char* password;
	Address address;
	Product** cart;
	int numOfProductsInCart;
	Checkout** orders;
	int numOfOrders;

public:
	Customer(char* username, char* password, Address address); // C'tor
	Customer(const Customer& other) = delete; // Disable copy c'tor
	~Customer(); // D'tor
	void show() const;
	void showCart() const;
	// Setters
	void setUsername(char* username);
	void setPassword(char* password);
	void setAddress(Address address);
	void setNumOfPruductsInCart(int numOfProductsInCart);
	void setNumOfOrders(int numOfOrders);
	// Getters
	char* getUsername() const;
	char* getPassword() const;
	Address getAddress() const;
	Product** getCart() const;
	int getNumOfProductsInCart() const;
	Checkout** getOrders() const;
	int getNumOfOrders() const;
};

#endif // __CUSTOMER_H