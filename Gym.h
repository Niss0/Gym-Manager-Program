#pragma once

#include "EmployeeManager.h"
#include "TraineeManager.h"
#include "Address.h"
#include "Store.h"

typedef struct
{
	double				income;				
	double				expenses;	
	char*				name;				
	Address				address;			
	EmployeeManager		empManager;			
	TraineeManager		trManager;			
	EquipmentManager	equipManager;		
	Store				store;				
}Gym;

int		initGymNoFile(Gym* pGym);
void	printGymIncome(Gym* pGym);
void	printGymExpenses(Gym* pGym);
void	printGymProfit(const Gym* pGym);
void	printGymDetails(const Gym* pGym);
void	freeGymRec(Gym* pGym, int step);

void	showMenu();
void	showManagementMenu();
void	showFinanceMenu();

void	managementCases(Gym* pGym);
void	financeCases(Gym* pGym);

