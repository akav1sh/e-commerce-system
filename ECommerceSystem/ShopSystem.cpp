#include "ShopSystem.h"

ShopSystem::ShopSystem(const char* name) // C'tor
	: name(nullptr), users(nullptr), allProducts(nullptr), numOfUsers(0), numOfAllProducts(0)
{
	setName(name);
}

ShopSystem::~ShopSystem() // D'tor
{
	for (int i = 0; i < numOfUsers; i++)
	{
		delete users[i];
	}

	delete[] users;
	delete[] allProducts; // The pointers already released at each of their seller d'tor
}

void ShopSystem::setName(const char* name)
{
	delete[] this->name; // Free previous name - if exists
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

char* ShopSystem::getName() const
{
	return name;
}

User** ShopSystem::getUsers() const
{
	return users;
}

int ShopSystem::getNumOfUsers() const
{
	return numOfUsers;
}

Product** ShopSystem::getAllProducts() const
{
	return allProducts;
}

int ShopSystem::getNumOfAllProducts() const
{
	return numOfAllProducts;
}

void ShopSystem::showCustomers() const
{
	bool isFound = false;

	for (int i = 0; i < numOfUsers; i++)
	{
		if (typeid(*users[i]) == typeid(Customer)) // Print only customers
		{
			if (!isFound)
			{
				cout << ShopSystem::name << " customers:\n" << endl;
				isFound = true;
			}
			cout << *users[i] << endl;
		}
	}

	if (!isFound) // No customers found
	{
		cout << "There are no registered customers yet.\n" << endl;
	}
}

void ShopSystem::showSellers() const
{
	bool isFound = false;

	for (int i = 0; i < numOfUsers; i++)
	{
		if (typeid(*users[i]) == typeid(Seller)) // Print only sellers
		{
			if (!isFound)
			{
				cout << ShopSystem::name << " sellers:\n" << endl;
				isFound = true;
			}
			cout << *users[i] << endl;
		}
	}

	if (!isFound) // No sellers found
	{
		cout << "There are no registered sellers yet.\n" << endl;
	}
}

void ShopSystem::showSellerCustomers() const
{
	bool isFound = false;

	for (int i = 0; i < numOfUsers; i++)
	{
		if (typeid(*users[i]) == typeid(SellerCustomer)) // Print only seller-customers
		{
			if (!isFound)
			{
				cout << ShopSystem::name << " seller-customers:\n" << endl;
				isFound = true;
			}
			cout << *users[i] << endl;
		}
	}

	if (!isFound) // No seller-customers found
	{
		cout << "There are no registered seller-customers yet.\n" << endl;
	}
}

void ShopSystem::showAllProducts() const
{
	if (numOfAllProducts == 0)
	{
		cout << "There are no products in the shop yet.\n" << endl;
	}
	else
	{
		cout << name << " products:\n" << endl;
		for (int i = 0; i < numOfAllProducts; i++)
		{
			cout << i + 1 << "." << *allProducts[i] << endl;
			cout << endl;
		}
	}
}

bool ShopSystem::mainMenu()
{
	Menu menu;
	Validations validator;
	int selection;

	menu.printMainMenu();
	cin >> selection;
	cout << endl;

	if (!validator.cinTypeCheck())
	{
		cout << "Please choose from one of the following options!\n" << endl;
		return true; // cin failed - wrong input type. Go back to login menu
	}

	switch ((LoginOptions)selection)
	{
	case SignupNewSeller:
	{
		User* newSeller = readUserData(TypeSeller);
		*this += newSeller; // Add new seller to users array
		if (!sellerMenu(newSeller)) // Repeatedly show seller menu until he asks to exit
		{
			return false; // Exit from the application
		}
		break;
	}
	case SignupNewCustomer:
	{
		User* newCustomer = readUserData(TypeCustomer);
		*this += newCustomer; // Add new customer to users array
		if (!customerMenu(newCustomer)) // Repeatedly show customer menu until he asks to exit
		{
			return false; // Exit from the application
		}
		break;
	}
	case SignupNewSC:
	{
		User* newSC = readUserData(TypeSellerCustomer);
		*this += newSC; // Add new seller-customer to users array
		if (!sellerCustomerMenu(newSC)) // Repeatedly show seller-customer menu until he asks to exit
		{
			return false; // Exit from the application
		}
		break;
	}
	case Login:
	{
		User* user = loginUser();
		if (user) // User found
		{
			if (typeid(*user) == typeid(Seller)) // Seller
			{
				if (!sellerMenu(user)) // Repeatedly show seller menu until he asks to exit
				{
					return false; // Exit from the application
				}
			}
			else if (typeid(*user) == typeid(Customer)) // Customer
			{
				if (!customerMenu(user)) // Repeatedly show customer menu until he asks to exit
				{
					return false; // Exit from the application
				}
			}
			else // Seller-Customer
			{
				if (!sellerCustomerMenu(user)) // Repeatedly show seller-customer menu until he asks to exit
				{
					return false; // Exit from the application
				}
			}
		}
		break;
	}
	case ViewCustomers:
	{
		showCustomers();
		break;
	}
	case ViewSellers:
	{
		showSellers();
		break;
	}
	case ViewSC:
	{
		showSellerCustomers();
		break;
	}
	case Exit:
		return false; // Exit from the application
	default: // Invalid option
		cout << "Please choose from one of the following options!\n" << endl;
	}

	return true; // Go back to login menu
}

bool ShopSystem::sellerMenu(User* user)
{
	Seller* seller = dynamic_cast<Seller*>(user); if (!seller) return false;
	Validations validator;
	Menu menu;
	int selection;

	menu.printSellerMenu();
	cin >> selection;
	cout << endl;

	if (!validator.cinTypeCheck()) // cin failed - ask again for valid type
	{
		cout << "Please choose from one of the following options!\n" << endl;
	}
	else // Valid type
	{
		switch ((SellerOptions)selection)
		{
		case AddNewProduct:
		{
			Product* newProduct = readProductData(seller);
			seller->addProduct(newProduct); // Add the new product to its seller
			this->addProductToStock(newProduct); // Add the new product to the general products array
			break;
		}
		case SellerSearchProduct:
		{
			searchProducts();
			break;
		}
		case ViewProducts:
		{
			seller->showProducts();
			cout << endl;
			break;
		}
		case ViewFeedbacks:
		{
			seller->showFeedbacks();
			cout << endl;
			break;
		}
		case SellerPreviousMenu:
			return true; // Go back to previous menu
		case SellerExit:
			return false; // Exit from the application
		default:
			cout << "Please choose from one of the following options!\n" << endl;
		}
	}

	return sellerMenu(seller); // Repeatedly show menu
}

bool ShopSystem::customerMenu(User* user)
{
	Customer* customer = dynamic_cast<Customer*>(user); if (!customer) return false;
	Menu menu;
	Validations validator;
	int selection;

	menu.printCustomerMenu();
	cin >> selection;
	cout << endl;

	if (!validator.cinTypeCheck()) // cin failed - ask again for valid type
	{
		cout << "Please choose from one of the following options!\n" << endl;
	}
	else
	{
		switch ((CustomerOptions)selection)
		{
		case CustomerSearchProduct:
		{
			searchProducts();
			break;
		}
		case AddProductToCart:
		{
			addProductToUserCart(customer);
			break;
		}
		case ViewCart:
		{
			customer->showCart();
			break;
		}
		case CheckoutAndPlaceOrder:
		{
			checkout(customer);
			break;
		}
		case WriteFeedback:
		{
			writeFeedback(customer);
			break;
		}
		case CustomerPreviousMenu:
			return true; // Go back to previous menu
		case CustomerExit:
			return false; // Exit from the application
		default:
			cout << "Please choose from one of the following options!\n" << endl;
		}
	}

	return customerMenu(customer); // Repeatedly show menu
}

bool ShopSystem::sellerCustomerMenu(User* user)
{
	SellerCustomer* sc = dynamic_cast<SellerCustomer*>(user); if (!sc) return false;
	Menu menu;
	Validations validator;
	int selection;

	menu.printSellerCustomerMenu();
	cin >> selection;
	cout << endl;

	if (!validator.cinTypeCheck()) // cin failed - ask again for valid type
	{
		cout << "Please choose from one of the following options!\n" << endl;
	}
	else
	{
		switch ((SellerCustomerOptions)selection)
		{
		case ViewCustomerMenu:
		{
			if (!customerMenu(sc)) // Repeatedly show customer menu until he asks to exit
			{
				return false; // Exit from the application
			}
			break;
		}
		case ViewSellerMenu:
		{
			if (!sellerMenu(sc)) // Repeatedly show seller menu until he asks to exit
			{
				return false;
			}
			break;
		}
		case SCPreviousMenu:
			return true; // Go back to previous menu
		case SCExit:
			return false; // Exit from the application
		default:
			cout << "Please choose from one of the following options!\n" << endl;
		}
	}

	return sellerCustomerMenu(sc); // Repeatedly show menu
}

const ShopSystem& ShopSystem::operator+=(User* user)
{
	User** temp = new User*[numOfUsers + 1]; // Create bigger array to add the new user

	// Move the pointers from the current array to temp
	for (int i = 0; i < numOfUsers; i++)
	{
		temp[i] = users[i];
	}
	temp[numOfUsers] = user; // Add the new user
	numOfUsers++;

	delete[] users; // Free the current array
	users = temp; // Update users array to temp
	return *this;
}

void ShopSystem::addProductToStock(Product* newProduct)
{
	Product** temp = new Product*[numOfAllProducts + 1]; // Create bigger array to add the new product

	// Move the pointers from the current array to temp
	for (int i = 0; i < numOfAllProducts; i++)
	{
		temp[i] = allProducts[i];
	}
	temp[numOfAllProducts] = newProduct; // Add the new product
	numOfAllProducts++;

	delete[] allProducts; // Free the current array
	allProducts = temp; // Update products array to temp
}

User* ShopSystem::loginUser()
{
	Validations validator;
	char username[MAX_CHARACTERS], password[MAX_CHARACTERS];
	bool isValidUsername, isValidPassword;
	int len = 0;

	cout << "Please login with your credentials.\n" << endl;
	validator.cleanBuffer();
	cout << "Username: ";
	isValidUsername = validator.getInput(username, len, MAX_CHARACTERS);
	cout << "Password: ";
	isValidPassword = validator.getInput(password, len, MAX_CHARACTERS);

	if (!(isValidUsername && isValidPassword)) // One of the inputs not valid
	{
		cout << endl << "Wrong details. Login failed!\n" << endl;
		return nullptr; // Invalid input - login failed
	}

	// Check if the entered username and password match to registered user
	for (int i = 0; i < numOfUsers; i++)
	{
		if (strcmp(users[i]->getUsername(), username) == 0)
		{
			if (strcmp(users[i]->getPassword(), password) == 0)
			{
				cout << "Logged in successfully!\n" << endl;
				cout << "Welcome back " << users[i]->getUsername() << "!\n" << endl;
				return users[i]; // User found
			}
		}
	}

	cout << endl << "Wrong details. Login failed!\n" << endl;
	return nullptr; // User not found - login failed
}

void ShopSystem::searchProducts() const
{
	Validations validator;
	char productName[MAX_PRODUCT_NAME_LENGTH];
	int selection, numOfMatchingProducts = 0;
	bool isFound = false;

	if (numOfAllProducts == 0) // No products in the shop
	{
		cout << "There are no products in the shop yet.\n" << endl;
	}
	else
	{
		if (validator.searchProductSelectionValidation(selection)) // Selection validation
		{
			if ((SearchProductOptions)selection == AllProducts)
			{
				showAllProducts(); // Show all the products in the shop
			}
			else // SpecificProductName
			{
				validator.cleanBuffer();
				if (validator.searchProductNameValidation(productName))
				{
					// Search for matching products in the general products array
					for (int i = 0; i < numOfAllProducts; i++)
					{
						if (strcmp(productName, allProducts[i]->getName()) == 0) // Match
						{
							if (!isFound)
							{
								cout << "Products found:\n" << endl;
								isFound = true;
							}

							cout << numOfMatchingProducts + 1 << "." << *allProducts[i] << endl;
							cout << endl;
							numOfMatchingProducts++;
						}
					}
				}

				if (numOfMatchingProducts == 0) // No matching products found
				{
					cout << "No products found. Keep searching! We have it all in " << ShopSystem::name << ".\n" << endl;
				}
			}
		}
	}
}

void ShopSystem::addProductToUserCart(User* user)
{
	Customer* customer = dynamic_cast<Customer*>(user); if (!customer) return;
	Validations validator;
	unsigned int productID = 0;

	if (numOfAllProducts == 0) // No products in the shop
	{
		cout << "There are no available products at the moment in the shop.\n" << endl;
	}
	else
	{
		if (validator.addProudctToCartValidation(productID, numOfAllProducts)) // Valid product ID
		{
			for (int i = 0; i < numOfAllProducts; i++)
			{
				if (productID == allProducts[i]->getSerialNumber()) // Match
				{
					if (!validator.isProductBelongsToUser(user, allProducts[i]->getSerialNumber()))
					{
						if (!validator.isProductExists(allProducts[i]->getSerialNumber(), customer->getCart(), customer->getNumOfProductsInCart()))
						{
							// Add the chosen product to customer's cart
							customer->addProductToCart(allProducts[i]);
							cout << "The product '" << allProducts[i]->getName() << "' added to cart successfully!\n" << endl;
						}
						else
						{
							cout << "You already added this product to your cart.\n" << endl;
						}
					}
					else
					{
						cout << "You can't add your own products to your cart.\n" << endl;
					}
					return;
				}
			}
		}
	}
}

void ShopSystem::checkout(User* user)
{
	Customer* customer = dynamic_cast<Customer*>(user); if (!customer) return;

	if (customer->getNumOfProductsInCart() == 0) // No products in cart
	{
		cout << "Please add products to your cart before checkout.\n" << endl;
	}
	else
	{
		Checkout* order = new Checkout(customer);

		order->createNewOrder();
		if (order->getNumOfChosenProducts() == 0) // No products selected
		{
			cout << endl << "Order cancelled!\n" << endl;
			delete order;
		}
		else
		{
			cout << endl << *order;
			order->placeOrder(); // Place order
			customer->initCart(); // Initialize customer cart
			customer->addOrder(order); // Add the new order to customer orders
		}
	}
}

Date ShopSystem::readDate()
{
	Validations validator;
	int day, month, year;

	cout << endl << "Fill in the date details.\n" << endl;
	validator.dateValidation(day, month, year);
	return Date(day, month, year);
}

void ShopSystem::readTextForFeedback(char* text) const
{
	Validations validator;
	int len = 0;
	bool isValid;

	validator.cleanBuffer();
	do
	{
		cout << endl << "Please write your feedback here (up to 90 characters):" << endl;
		isValid = validator.getInput(text, len, MAX_FEEDBACK_LENGTH);
		if (!isValid)
		{
			cout << "Invalid input length. Please write again!" << endl;
		}
	} while (!isValid);
}

void ShopSystem::writeFeedback(User* user)
{
	Customer* customer = dynamic_cast<Customer*>(user); if (!customer) return;
	Validations validator;
	int index;

	if (customer->getNumOfOrders() == 0)
	{
		cout << "You have 0 orders made. Make an order so you could leave a feedback.\n" << endl;
	}
	else 
	{
		customer->showOrders();
		cout << endl << "Choose the index of the order you wish to make the feedback about: ";
		cin >> index;
		if (!validator.cinTypeCheck() || !(1 <= index && index <= customer->getNumOfOrders()))
		{
			cout << "You don't have such order.\n" << endl;
		}
		else 
		{
			Checkout* selectedOrder = customer->getOrders()[index - 1];

			cout << *selectedOrder;
			cout << "Pick the index of the product to write its seller the feedback: ";
			cin >> index;
			if (!validator.cinTypeCheck() || !(1 <= index && index <= selectedOrder->getNumOfChosenProducts()))
			{
				cout << "You don't have such product in this order.\n" << endl;
			}
			else 
			{
				Product* chosenProuct = selectedOrder->getChosenProducts()[index - 1];
				Seller* seller = dynamic_cast<Seller*>(chosenProuct->getSeller()); if (!seller) return;
				char text[MAX_FEEDBACK_LENGTH];

				readTextForFeedback(text);
				seller->addFeedback(new Feedback(user, chosenProuct, readDate(), text)); // Add the feedback to its seller
				cout << endl << "Your feedback to " << chosenProuct->getSeller()->getUsername() << " added successfully!\n" << endl;
			}
		}
	}
}

User* ShopSystem::readUserData(UserType type)
{
	Validations validator;
	char username[MAX_CHARACTERS], password[MAX_CHARACTERS];
	char country[MAX_CHARACTERS], city[MAX_CHARACTERS], street[MAX_CHARACTERS];
	int buildingNumber;

	cout << "Thanks for joining in!"<< endl;
	cout << "We are using an universal and decentralized authentication." << endl;
	cout << "Please fill in the following fields:\n" << endl;

	validator.usernameValidation(username, users, numOfUsers);
	validator.passwordValidation(password);
	validator.countryValidation(country);
	validator.cityValidation(city);
	validator.streetValidation(street);
	validator.buildingNumberValidation(buildingNumber);
	cout << endl << "Registration completed successfully!\n" << endl;

	if (type == TypeSellerCustomer) // Seller-Customer
	{
		return new SellerCustomer(username, password, Address(country, city, street, buildingNumber));
	}
	else if (type == TypeSeller) // Seller
	{
		return new Seller(username, password, Address(country, city, street, buildingNumber));
	}
	else // Customer
	{
		return new Customer(username, password, Address(country, city, street, buildingNumber));
	}
}

Product* ShopSystem::readProductData(User* user)
{
	Validations validator;
	char productName[MAX_PRODUCT_NAME_LENGTH];
	float price;
	int category;

	cout << "Please fill in the following fields.\n" << endl;
	validator.productNameValidation(productName, user);
	validator.priceValidation(price);
	validator.categoryValidation(category);

	cout << endl << "Product added successfully!\n" << endl;
	return new Product(productName, price, category, user);
}