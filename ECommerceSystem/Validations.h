#ifndef __VALIDATIONS_H
#define __VALIDATIONS_H

void cleanBuffer();
bool getInput(char* str, int& len, const int maxLen);
bool cinTypeCheck();
void usernameValidation(char* username, User** users, int numOfUsers);
bool checkUniqueUsername(char* username, User** users, int numOfUsers);
void passwordValidation(char* password);
bool checkLettersAndDigits(const char* str);
bool checkSpecialCharacters(const char* str);
bool checkLetters(const char* str);
bool checkLettersDigitsAndSpace(const char* str);
void countryValidation(char* country);
void cityValidation(char* city);
void streetValidation(char* street);
void buildingNumberValidation(int& buildingNumber);
void productNameValidation(char* productName, User* user);
bool isProductExists(char* productName, Product** products, int numOfProductsInCart);
void priceValidation(float& price);
void categoryValidation(int& category);
bool searchProductSelectionValidation(int& selection);
bool searchProductNameValidation(char* productName);
bool addProductToCartValidation(unsigned int& productID, const int numOfAllProducts);
Product* indexOfCheckoutProductValidation(int& index, Product** cart, int numOfProductsInCart, Product** chosenProducts, int numOfChosenProducts);
bool isSellerExists(User* seller, User** sellers, int numOfSellers);
void dateValidation(int& day, int& month, int& year);

#endif // __VALIDATIONS_