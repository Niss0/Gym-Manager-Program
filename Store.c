#include "Store.h"

void initStore(Store* pStore)
{
	pStore->productsArr = NULL;
	pStore->stockCap = NULL;
	pStore->supplierPrices = NULL;
	pStore->numOfProducts = 0;
	pStore->income = 0;
	pStore->expenses = 0;
}

int getValidProductsNumber(Store* pStore, char* name, int currMax)
{
	int firstTime = 1;
	int numOfProducts = 0;

	do {
		if (firstTime)
			firstTime = 0;
		else
			printf("The number of %s you can buy is between 1 - %d \n", name, currMax);
		printf("How many %s do you want to purchase? (1 - %d)\n", name, currMax);
		scanf("%d", &numOfProducts);
	} while (numOfProducts > currMax || numOfProducts < 0);

	return numOfProducts;
}

int addProduct(Store* pStore)
{
	int* newStockCap = pStore->stockCap;
	int* newSupplierPrices = pStore->supplierPrices;
	Product* newProductsArr = pStore->productsArr;

	newProductsArr = (Product*)realloc(newProductsArr, sizeof(Product) * (pStore->numOfProducts + 1));
	CHECK_IF_EQUALS(newProductsArr, NULL, 0);

	newStockCap = (int*)realloc(newStockCap, sizeof(int) * (pStore->numOfProducts + 1));
	CHECK_IF_EQUALS(newStockCap, NULL, 0);

	newSupplierPrices = (int*)realloc(newSupplierPrices, sizeof(int) * (pStore->numOfProducts + 1));
	CHECK_IF_EQUALS(newSupplierPrices, NULL, 0);

	Product newProduct;
	initProduct(&newProduct);

	pStore->stockCap[pStore->numOfProducts] = getPositiveNumber("new product stock cap");
	pStore->supplierPrices[pStore->numOfProducts] = getPositiveNumber("new product supplier price");
	newProductsArr[pStore->numOfProducts++] = newProduct;

	pStore->productsArr = newProductsArr;
	pStore->stockCap = newStockCap;
	pStore->supplierPrices = newSupplierPrices;

	printf("\n");
	return 1;
}

int deleteProduct(Store* pStore)
{
	int deleteIndex;
	HANDLE_ERRORS(pStore->numOfProducts, printf("There are no products to delete \n\n"), 0);
	deleteIndex = findProductIndex(pStore);
	pStore->productsArr[deleteIndex] = pStore->productsArr[--(pStore->numOfProducts)];
	pStore->stockCap[deleteIndex] = pStore->stockCap[pStore->numOfProducts];
	pStore->supplierPrices[deleteIndex] = pStore->supplierPrices[pStore->numOfProducts];

	printf("\n");
	return 1;
}

int orderProductsToStock(Store* pStore)
{
	HANDLE_ERRORS(pStore->numOfProducts, printf("There are no products to order \n\n"), 0);

	int index = findProductIndex(pStore);
	Product* pProduct = &pStore->productsArr[index];

	if (pProduct->stock == pStore->stockCap[index])
	{
		printf("%s's stock is already full \n\n", pProduct->name);
		return 0;
	}

	int currMax = pStore->stockCap[index] - pProduct->stock;
	int numOfProducts = getValidProductsNumber(pStore, pProduct->name, currMax);

	pStore->expenses += (pProduct->price * numOfProducts);		
	pProduct->stock += numOfProducts;								

	printf("\n");
	return 1;
}

int	sellProducts(Store* pStore, TraineeManager* trManager)
{
	HANDLE_ERRORS(pStore->numOfProducts, printf("There are no products to sell \n\n"), 0);

	Trainee* traineeFound = findTraineeByIndex(trManager);
	CHECK_IF_EQUALS(traineeFound, NULL, 0);
	int index = findProductIndex(pStore);
	Product* pProduct = &pStore->productsArr[index];

	if (pProduct->stock == 0)
	{
		printf("There is no %s in stock \n\n", pProduct->name);
		return 0;
	}

	int numOfProducts = getValidProductsNumber(pStore, pProduct->name, pProduct->stock);

	pStore->income += calculatePrice(traineeFound, pProduct->price, numOfProducts);
	pProduct->stock -= numOfProducts;							
	pProduct->amountSold += numOfProducts;
	
	printf("\n");
	return 1;
}

double calculatePrice( Trainee* pTrainee, int price, int numOfProducts)
{
	double totalPrice;
	if (pTrainee->subscriptionType == eVIP)
		totalPrice = (price * numOfProducts) * VIP_DISCOUNT;			// price after vip discount
	else
		totalPrice = price * numOfProducts;
	
	return totalPrice;
}

void fillStoreStock(Store* pStore)
{
	HANDLE_ERRORS(pStore->numOfProducts, printf("There are no products in store \n\n"), );
	
	int isFull = 1;
	double totalCost = 0;
	for (int i = 0; i < pStore->numOfProducts; i++)
	{
		if(pStore->productsArr[i].stock != pStore->stockCap[i])
		{
			totalCost += (pStore->stockCap[i] - pStore->productsArr[i].stock) * pStore->supplierPrices[i];
			pStore->productsArr[i].stock = pStore->stockCap[i];
			isFull = 0;
		}
	}
	pStore->expenses += totalCost;

	if (isFull)
		printf("Stock is already full \n\n");
	printf("Stock has been successfully filled \n\n");
}

void updateProductPrice(Store* pStore)
{
	HANDLE_ERRORS(pStore->numOfProducts, printf("There are no products to update \n\n"), );

	int index = findProductIndex(pStore);
	Product* pProduct = &pStore->productsArr[index];
	printf("Enter %s new price: \n", pProduct->name);
	scanf("%d", &pProduct->price);
	printf("\n");
}

void printStoreProducts(const Store* pStore)
{
	HANDLE_ERRORS(pStore->numOfProducts, printf("There are no products in store \n\n"), );
	generalArrayFunction(pStore->productsArr, pStore->numOfProducts, sizeof(Product), printProduct);
}

int findProductIndex(Store* pStore)
{
	printStoreProducts(pStore);
	return getNumberInRange("product's index", 1, pStore->numOfProducts) - 1;			
}

void printProcutsPrice(const Store* pStore)
{
	HANDLE_ERRORS(pStore->numOfProducts, printf("There are no products in store \n\n"), );

	for (int i = 0; i < pStore->numOfProducts; i++)
		printf("%s price is $%d \n", pStore->productsArr[i].name, pStore->productsArr[i].price);
	printf("\n");
}

void printStoreStock(const Store* pStore)
{
	HANDLE_ERRORS(pStore->numOfProducts, printf("There are no products in store \n\n"), );

	for (int i = 0; i < pStore->numOfProducts; i++)
		printf("%s has %d units in stock \n", pStore->productsArr[i].name, pStore->productsArr[i].stock);
	printf("\n");
}

void printMostWantedProduct(const Store* pStore)
{
	HANDLE_ERRORS(pStore->numOfProducts, printf("There are no products in store \n\n"), );

	int maxPurchases = pStore->productsArr[0].amountSold;
	int maxIndex = 0;
	for (int i = 1; i < pStore->numOfProducts; i++)
	{
		if (pStore->productsArr[i].amountSold > maxPurchases)
		{
			maxPurchases = pStore->productsArr[i].amountSold;
			maxIndex = i;
		}
	}
	if (maxPurchases == 0)
		printf("No product was sold yet \n");
	else
		printf("Most bought product was %s with %d purchases \n\n", pStore->productsArr[maxIndex].name, maxPurchases);
	
	printf("\n");
}

void printStoreIncome(const Store* pStore)
{
	printf("Store income: $%.2lf \n", pStore->income);
}

void printStoreExpenses(const Store* pStore)
{
	printf("Store expenses: $%.2lf \n", pStore->expenses);
}

void printStoreProfit(const Store* pStore)
{
	double profit = pStore->income - pStore->expenses;
	printf("Store profit: $%.2lf \n\n", profit);
}

void freeStore(Store* pStore)
{
	free(pStore->productsArr);
	free(pStore->supplierPrices);
	free(pStore->stockCap);
}

void showStoreManu()
{
	printf("1) Add product \n");
	printf("2) Delete product \n");
	printf("3) Order products to Store \n");
	printf("4) Sell products to Trainee \n");
	printf("5) Fill stock \n");
	printf("6) update product price \n");
	printf("7) Print products price \n");
	printf("8) Print most wanted product \n");
	printf("9) Print stock \n");
	printf("10) Print income \n");
	printf("11) Print expenses \n");
	printf("12) Print revenue \n");
	printf("-1) Return to previous menu \n");
}

void storeCases(Store* pStore, TraineeManager* trManager)
{
	int choice;
	system("cls");
	printHeader("Store Department");
	do {
		showStoreManu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			if (!addProduct(pStore))
				printf("Error adding product to store \n");
			break;
		case 2:
			if (!deleteProduct(pStore))
				printf("Error deleting product from store \n");
			break;
		case 3:
			if (!orderProductsToStock(pStore))
				printf("Error order product to store \n");
			break;
		case 4:
			if (!sellProducts(pStore, trManager))
				printf("Error selling product to trainee \n");
			break;
		case 5:
			fillStoreStock(pStore);
			break;
		case 6:
			updateProductPrice(pStore);
			break;
		case 7:
			printProcutsPrice(pStore);
			break;
		case 8:
			printMostWantedProduct(pStore);
			break;
		case 9:
			printStoreStock(pStore);
			break;
		case 10:
			printStoreIncome(pStore);
			printf("\n");
			break;
		case 11:
			printStoreExpenses(pStore);
			printf("\n");
			break;
		case 12:
			printStoreProfit(pStore);
			break;
		case EXIT:
			system("cls");
			break;
		default:
			printf("Wrong option \n");
			break;
		}
	} while (choice != EXIT);
}