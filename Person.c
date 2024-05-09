#include "Person.h"

#define PHONE_NUM_LEN 10

void initPerson(Person* pPerson)
{
    pPerson->name = getStrExactLength("Please enter your name:");
    getPhoneNumber(pPerson);

}

void getPhoneNumber(Person* pPerson)
{
    char tempPhoneNum[MAX_LEN];
    int ok = 0;

    do {
        ok = 1;
        printf("Enter your phone number (%d digits): \n", PHONE_NUM_LEN);
        myGets(tempPhoneNum, MAX_LEN);
        if (strlen(tempPhoneNum) != PHONE_NUM_LEN)
        {
            printf("Phone number should be %d digits \n", PHONE_NUM_LEN);
            ok = 0;
        }
        else
        {
            for (int i = 0; i < PHONE_NUM_LEN; i++)
            {
                if (tempPhoneNum[i] < '0' || tempPhoneNum[i] > '9')
                {
                    printf("You need to enter only digits \n");
                    ok = 0;
                    break;
                }
            }
        }
    } while (!ok);

    strcpy(pPerson->phoneNum, tempPhoneNum);
}

void printPerson(const Person* pPerson)
{
	printf("Name: %s, phone number: %s ", pPerson->name, pPerson->phoneNum);
}
