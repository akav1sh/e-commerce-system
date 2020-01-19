#include "Customer.h"
#include "Checkout.h"

Checkout::Checkout(User& customer) // C'tor
	: customer(customer), totalPrice(0)
{
}

Checkout::~Checkout() // D'tor
{
	//delete[] chosenProducts; // The pointers will be released at each of their seller d'tor
	//delete[] sellers; // The pointers will be released at the shop system d'tor
}

vector<Product*> Checkout::getChosenProducts() const
{
	return chosenProducts;
}

int Checkout::getNumOfChosenProducts() const
{
	return chosenProducts.size();
}

float Checkout::getTotalPrice() const
{
	return totalPrice;
}

vector<User*> Checkout::getSellers() const
{
	return sellers;
}

int Checkout::getNumOfSellers() const
{
	return sellers.size();
}

User& Checkout::getCustomer() const
{
	return customer;
}

ostream& operator<<(ostream& os, const Checkout& checkout)
{
	os << "Chosen products:\n" << endl;
	for (int i = 0; i < checkout.chosenProducts.size(); i++)
	{
		os << i + 1 << "." << *checkout.chosenProducts[i] << endl;
		os << endl;
	}
	return os;
}

void Checkout::calculateTotalPrice()
{
	for (int i = 0; i < chosenProducts.size(); i++)
	{
		totalPrice += chosenProducts[i]->getPrice();
	}
}

//void Checkout::addChosenProduct(Product& newProduct)
//{
//	Product** temp = new Product*[numOfChosenProducts + 1]; // Create bigger array to add the new product
//
//	// Move the pointers from the current array to temp
//	for (int i = 0; i < numOfChosenProducts; i++)
//	{
//		temp[i] = chosenProducts[i];
//	}
//	temp[numOfChosenProducts] = &newProduct; // Add the new product
//	numOfChosenProducts++;
//
//	delete[] chosenProducts; // Free the current array
//	chosenProducts = temp; // Update products array to temp
//}

//void Checkout::addSeller(User& seller)
//{
//	User** temp = new User*[numOfSellers + 1]; // Create bigger array to add the new seller
//
//	// Move the pointers from the current array to temp
//	for (int i = 0; i < numOfSellers; i++)
//	{
//		temp[i] = sellers[i];
//	}
//	temp[numOfSellers] = &seller; // Add the new seller
//	numOfSellers++;
//
//	delete[] sellers; // Free the current array
//	sellers = temp; // Update sellers array to temp
//}

void Checkout::createNewOrder()
{
	Customer* customer = dynamic_cast<Customer*>(&this->customer); if (!customer) return;
	Product* product;
	Validations validator;
	int index = 0;
	bool toContinue = true;

	while (toContinue)
	{
		product = validator.indexOfCheckoutProductValidation(index, customer->getCart(), customer->getNumOfProductsInCart(), chosenProducts, chosenProducts.size());
		if (index == -1) // Customer finished to add products to order
		{
			toContinue = false;
		}
		else
		{
			// Add product to the chosen products array
			//addChosenProduct(*product);
			chosenProducts.push_back(product);
			// Only if seller not exists already - add product's seller to the sellers array
			if (!validator.isSellerExists(product->getSeller(), sellers, sellers.size()))
			{
				//addSeller(product->getSeller());
				sellers.push_back(&product->getSeller());
			}
		}
	}
	calculateTotalPrice();
}

void Checkout::showSellersNames() const
{
	cout << "\tSellers names: " << sellers[0]->getUsername();
	for (int i = 1; i < sellers.size(); i++)
	{
		cout << ", " << sellers[i]->getUsername();
	}
	cout << endl;
}

void Checkout::showProductsNames() const
{
	cout << "Products names: " << chosenProducts[0]->getName();
	for (int i = 1; i < chosenProducts.size(); i++) 
	{
		cout << ", " << chosenProducts[i]->getName();
	}
	cout << endl;
}