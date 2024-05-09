#pragma once
#include "Workout.h"
#include "Person.h"

typedef enum {
	eRegular, eVIP, eNofSubscriptionTypes
} eSubscriptionType;

static const char* SubscriptionTypeStr[eNofSubscriptionTypes] = { "Regular", "VIP"};

typedef struct 
{
	Person				personalData;
	Workout*			workout;
	eSubscriptionType	subscriptionType;
} Trainee;

int					initTrainee(Trainee* trainee);
eSubscriptionType	getSubscriptionType();
void				printTrainee(const void* v);
void				freeTrainee(Trainee* pTrainee);
