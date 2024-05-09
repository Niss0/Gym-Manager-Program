#include "Product.h"

void initProduct(Product* pProduct)
{
	printf("Enter product name: \n");
	myGets(pProduct->name, MAX_LEN);

	pProduct->price = getPositiveNumber("product price (in dollers)");

	pProduct->amountSold = 0;
	pProduct->stock = 0;
}

void printProduct(const Product* pProduct)
{
	printf("Product name: %s, price: %d$ \n", 
		pProduct->name, pProduct->price);
}

