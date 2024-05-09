#pragma once
#include "General.h"

typedef unsigned char BYTE;

typedef struct
{
	char			name[MAX_LEN];		
	int				price;				
	int				stock;				
	int				amountSold;			
}Product;

void			initProduct(Product* pProduct);
void			printProduct(const Product* pProduct);

