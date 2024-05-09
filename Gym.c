#include "Gym.h"


int initGymNoFile(Gym* pGym)
{
	pGym->income = 0;
	pGym->expenses = 0;
	pGym->name = getStrExactLength("Enter gym's name: ");
	initAddress(&pGym->address);
	initEmployeeManager(&pGym->empManager);
	if (!initEquipmentManager(&pGym->equipManager))
	{
		printf("Error init equipment manager \n");
		return 0;
	}
	initTraineeManager(&pGym->trManager);
	initStore(&pGym->store);

	return 1;
}

void printGymIncome(Gym* pGym)
{
	pGym->income = pGym->trManager.income + pGym->store.income;
	printStoreIncome(&pGym->store);
	printTraineesIncome(&pGym->trManager);
	printf("Total gym income: $%.2lf \n\n", pGym->income);
}

void printGymExpenses(Gym* pGym)
{
	pGym->expenses = pGym->empManager.expenses + pGym->store.expenses;
	printStoreExpenses(&pGym->store);
	printSalaryExpenses(&pGym->empManager);
	printf("Total gym expenses: $%.2lf \n\n", pGym->expenses);
}

void printGymProfit(const Gym* pGym)
{
	double profit = pGym->income - pGym->expenses;
	printf("Total gym profit: $%.2lf \n\n", profit);
}

void printGymDetails(const Gym* pGym)
{
	printf("Gym name: %s \n", pGym->name);
	printAddress(&pGym->address);
	printf("Number of employees: %d \nNumber of Trainees: %d \n\n", 
		pGym->empManager.numOfEmployee, pGym->trManager.numOfTrainee);
}

void freeGymRec(Gym* pGym, int step)
{
	if (step == 1)
	{
		free(pGym->name);
		return;
	}
	else if (step == 2)
	{
		freeEmployeeArr(pGym->empManager.employeeArr, pGym->empManager.numOfEmployee);
		freeGymRec(pGym, step - 1);
	}
	else if (step == 3)
	{
		freeEquipments(pGym->equipManager.equipmentList);
		L_free(pGym->equipManager.equipmentList, free);
		free(pGym->equipManager.equipmentList);
		freeGymRec(pGym, step - 1);
	}
	else if (step == 4)
	{
		freeTraineeArr(pGym->trManager.traineeArr, pGym->trManager.numOfTrainee);
		freeGymRec(pGym, step - 1);
	}
	else // step == 5
	{
		freeStore(&pGym->store);
		freeGymRec(pGym, step - 1);
	}

}

void showMenu()
{
	printf("Please choose one of the following options \n");
	printf("1) Management Department \n");
	printf("2) Finance & Data Department \n");
	printf("3) Store Department \n");
	printf("-1) Exit \n"); 
}

void showManagementMenu()
{
	printHeader("Management Department");
	printf("1) Employees \n");
	printf("2) Trainees \n");
	printf("3) Equipments \n");
	printf("-1) Return to previous menu \n");
}

void showFinanceMenu()
{
	printf("1) Print gym's income \n");
	printf("2) Print gym's expenses \n");
	printf("3) Print gym's revenue \n");
	printf("4) Print gym's details \n");
	printf("-1) Return to previous menu \n");
}

void managementCases(Gym* pGym)
{
	int choice;
	system("cls");
	do {
		showManagementMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			manageEmployees(&pGym->empManager);
			break;
		case 2:
			manageTrainees(&pGym->trManager, &pGym->equipManager);
			break;
		case 3:
			manageEquipments(&pGym->equipManager);
			break;
		case EXIT:
			system("cls");
			break;
		default:
			printf("Wrong option \n");
			timeDelay(2);
			break;
		}
	} while (choice != EXIT);
}

void financeCases(Gym* pGym)
{
	int choice;
	printHeader("Data & Finance Department");
	do {
		showFinanceMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printGymIncome(pGym);
			break;
		case 2:
			printGymExpenses(pGym);
			break;
		case 3:
			printGymProfit(pGym);
			break;
		case 4:
			printGymDetails(pGym);
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