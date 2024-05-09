#include "EmployeeManager.h"

void initEmployeeManager(EmployeeManager* empManager)
{
	empManager->employeeArr = NULL;
	empManager->numOfEmployee = 0;
	empManager->expenses = 0;
	empManager->sortType = eUnSorted;
}

int addEmployee(EmployeeManager* empManager)
{
	Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
	Employee** newEmployeeArr = empManager->employeeArr;
	if (newEmployee == NULL)
		return 0;

	int firstTime = 1;
	initEmployee(newEmployee);
	do {
		if (firstTime)
			firstTime = 0;
		else if (!firstTime)
		{
			printf("This employee's phone number is already in use. Try again.\n");
			getPhoneNumber(&newEmployee->personalData);
		}
	} while (!isUniqeEmployeeByPhoneNumber(empManager, newEmployee->personalData.phoneNum));

	newEmployeeArr = (Employee**)realloc(newEmployeeArr, sizeof(Employee*) * (empManager->numOfEmployee + 1));
	if (newEmployeeArr == NULL)
	{
		free(newEmployee);
		return 0;
	}

	empManager->employeeArr = newEmployeeArr;
	empManager->employeeArr[(empManager->numOfEmployee)++] = newEmployee;
	empManager->expenses += newEmployee->salary;
	printf("\n");
	return 1;
}

void deleteEmployee(EmployeeManager* empManager)
{
	int deleteIndex;
	if (empManager->numOfEmployee == 0)
	{
		printf("There are no employees to delete \n\n");
		return;
	}

	printEmployeeArr(empManager);
	deleteIndex = getNumberInRange("employee's index you want to delete", 1,empManager->numOfEmployee) - 1;
	Employee* tmpEmployee = empManager->employeeArr[deleteIndex];
	empManager->employeeArr[deleteIndex] = empManager->employeeArr[--empManager->numOfEmployee];
	empManager->sortType = eUnSorted;
	empManager->expenses -= tmpEmployee->salary;

	printf("\n");
}

int isUniqeEmployeeByPhoneNumber(EmployeeManager* empManager, char* currPhoneNumber)
{
	for (int i = 0; i < empManager->numOfEmployee; i++)
	{
		if (strcmp(empManager->employeeArr[i]->personalData.phoneNum, currPhoneNumber) == 0)
			return 0;
	}
	return 1;
}

int compareEmployeeBySalary(const void* v1, const void* v2)
{
	Employee* e1 = *(Employee**)v1;
	Employee* e2 = *(Employee**)v2;
	return e1->salary - e2->salary;

}

int compareEmployeeBySeniority(const void* v1, const void* v2)
{
	Employee* e1 = *(Employee**)v1;
	Employee* e2 = *(Employee**)v2;
	return e1->seniority - e2->seniority;
}

int compareEmployeeByType(const void* v1, const void* v2)
{
	Employee* e1 = *(Employee**)v1;
	Employee* e2 = *(Employee**)v2;
	return e1->empType - e2->empType;
}

int compareEmployeeByName(const void* v1, const void* v2)				// for the third sort and search
{
	Employee* e1 = *(Employee**)v1;
	Employee* e2 = *(Employee**)v2;

	return strcmp(e1->personalData.name, e2->personalData.name);
}

void sortEmployee(EmployeeManager* empManager)
{
	if (empManager->numOfEmployee == 0)
	{
		printf("There are no employees to sort \n\n");
		return;
	}
	eSortType sortType = getSortType();
	int (*compare)(const void*, const void*) = NULL;
	if (sortType == eSalarySorted)
		compare = compareEmployeeBySalary;
	else if (sortType == eSenioritySorted)
		compare = compareEmployeeBySeniority;
	else if (sortType == eNameSorted)
		compare = compareEmployeeByName;
	else
		compare = compareEmployeeByType;

	qsort(empManager->employeeArr, empManager->numOfEmployee, sizeof(Employee*), compare);
	empManager->sortType = sortType;
	printf("\n");
}

Employee* findEmployeeByParameter(const Employee** pEmployeeArr, int numOfEmployees, eSortType sortType)
{
	Employee** pFound;
	Employee tempEmployee;
	Employee* pTempEmployee;
	pTempEmployee = &tempEmployee;


	if (sortType == eSalarySorted)
	{
		getSalary(&tempEmployee);
		pFound = bsearch(&pTempEmployee, pEmployeeArr, numOfEmployees, sizeof(Employee*), compareEmployeeBySalary);
	}
	else if (sortType == eSenioritySorted)
	{
		getSeniority(&tempEmployee);
		pFound = bsearch(&pTempEmployee, pEmployeeArr, numOfEmployees, sizeof(Employee*), compareEmployeeBySeniority);
	}
	else if (sortType == eNameSorted)
	{
		tempEmployee.personalData.name = getStrExactLength("enter your name: ");
		pFound = bsearch(&pTempEmployee, pEmployeeArr, numOfEmployees, sizeof(Employee*), compareEmployeeByName);
	}
	else							// sortType == eTypeSorted
	{
		tempEmployee.empType = getEmployeeType();
		pFound = bsearch(&pTempEmployee, pEmployeeArr, numOfEmployees, sizeof(Employee*), compareEmployeeByType);
	}

	if (!pFound)
		return NULL;
	return *pFound;
}

void findEmployee(const EmployeeManager* empManager)				// if there are 2 or more employees with the same data like seniority/type/salary, it's return just the first 
{
	eSortType sortType = empManager->sortType;
	Employee* pEmployee;

	if (sortType == eUnSorted)
	{
		printf("The search cannot be performed, employees' array not sorted \n\n");
		return;
	}

	pEmployee = findEmployeeByParameter(empManager->employeeArr, empManager->numOfEmployee, sortType);
	if (!pEmployee)
		printf("Employee was not found \n");
	else
	{
		printf("Employee found! \n");
		printEmployee(&pEmployee);
	}
	printf("\n");
}

eSortType getSortType()
{
	int option;
	printf("\n\n");
	do {
		printf("Base on what field do you want to sort?\n");
		for (int i = 1; i < eNofSortTypes; i++)
			printf("%d for %s\n", i, sortTypeStr[i]);
		scanf("%d", &option);
	} while (option < 1 || option >= eNofSortTypes);
	getchar();
	return (eSortType)option;
}

void printEmployeeArr(const EmployeeManager* empManager)
{
	if (empManager->numOfEmployee == 0)
	{
		printf("There are no employees \n\n");
		return;
	}
	generalArrayFunction(empManager->employeeArr, empManager->numOfEmployee, sizeof(Employee*), printEmployee);
	printf("\n");
}

void freeEmployeeArr(Employee** empArr, int size)
{
	for (int i = 0; i < size; i++)
		freeEmployee(empArr[i]);
	free(empArr);
}

void printSalaryExpenses(EmployeeManager* empManager)
{
	printf("Salary expenses: $%.2lf \n", empManager->expenses);
}

Employee** allocateEmployeeArr(int size)
{
	Employee** empArr = (Employee**)malloc(sizeof(Employee*) * size);
	CHECK_IF_EQUALS(empArr, NULL, NULL);
	for (int i = 0; i < size; i++)
	{
		empArr[i] = (Employee*)malloc(sizeof(Employee));
		if (!empArr[i])
		{
			freeEmployeeArr(empArr, i);
			return NULL;
		}
	}
	return empArr;
}




void showEmployeeMenu()
{
	printf("1) Add Employee \n");
	printf("2) Delete Employee \n");
	printf("3) Sort Employee \n");
	printf("4) Find Employee \n");
	printf("5) Print all employees \n");
	printf("-1) Return to previous menu \n");
}

void manageEmployees(EmployeeManager* empManager)
{
	int choice;
	printHeader("Employee Department");
	do 
	{
		showEmployeeMenu();
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			if (!addEmployee(empManager))
				printf("Error adding an employee \n\n");
			break;
		case 2:
			deleteEmployee(empManager);
			break;
		case 3:
			sortEmployee(empManager);
			break;
		case 4:
			findEmployee(empManager);
			break;
		case 5:
			printEmployeeArr(empManager);
			break;
		case EXIT:
			system("cls");
			break;
		default:
			printf("Wrong option \n\n");
			break;
		}
	} while (choice != EXIT);

}

