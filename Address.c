#include "Address.h"

void	initAddress(Address* pAddress)
{
	printf("Enter city name: \n");
	myGets(pAddress->city, MAX_LEN);

	printf("Enter street name: \n");
	myGets(pAddress->street, MAX_LEN);

	pAddress->streetNum = getPositiveNumber("street's number");
	pAddress->floorNum = getPositiveNumber("floor's number");

}

void printAddress(const Address* pAddress)
{
	printf("City: %s, street: %s %d, floor number: %d \n", pAddress->city, pAddress->street, pAddress->streetNum, pAddress->floorNum);
}