#pragma once
#include "Product.h"
#include "TraineeManager.h"
#include "list.h"

#define VIP_DISCOUNT			0.85

typedef struct
{
	Product*	productsArr;	
	int			numOfProducts;	
	int*		stockCap;			
	int*		supplierPrices;	
	double		income;			
	double		expenses;		
}Store;

void		initStore(Store* pStore);
int			getValidProductsNumber(Store* pStore, char* name, int currMax);
int			addProduct(Store* pStore);
int			deleteProduct(Store* pStore);
int			orderProductsToStock(Store* pStore);
int			sellProducts(Store* pStore, TraineeManager* trManager);
double		calculatePrice(Trainee* pTrainee, int price, int numOfProducts);
void		fillStoreStock(Store* pStore);
void		updateProductPrice(Store* pStore);
void		printStoreProducts(const Store* pStore);
int			findProductIndex(Store* pStore);
void		printProcutsPrice(const Store* pStore);
void		printStoreStock(const Store* pStore);
void		printMostWantedProduct(const Store* pStore);
void		printStoreIncome(const Store* pStore);
void		printStoreExpenses(const Store* pStore);
void		printStoreProfit(const Store* pStore);
void		freeStore(Store* pStore);

void		showStoreManu();
void		storeCases(Store* pStore, TraineeManager* trManager);


