#pragma once
#include "General.h"
#include "Workout.h"

#define PHONE_NUM_LEN	10


typedef struct Person
{
	char*			name;						
	char			phoneNum[PHONE_NUM_LEN+1];	
} Person;

void				initPerson(Person* pPerson);	
void				getPhoneNumber(Person* pPerson);
void				printPerson(const Person* pPerson);
