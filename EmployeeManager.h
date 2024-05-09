#pragma once
#include "Employee.h"
#include "General.h"

typedef enum {
	eUnSorted, eSalarySorted, eSenioritySorted, eNameSorted, eTypeSorted, eNofSortTypes
} eSortType;

static const char* sortTypeStr[eNofSortTypes] = { "Unsorted", "Sorted by salary","sorted by seniority", "Sorted by name","Sorted by job's type" };

typedef struct
{
	Employee**	employeeArr;		
	int			numOfEmployee;		
	double		expenses;			
	eSortType	sortType;			
} EmployeeManager;

void		initEmployeeManager(EmployeeManager* empManager);
int			addEmployee(EmployeeManager* empManager);
void		deleteEmployee(EmployeeManager* empManager);
int			isUniqeEmployeeByPhoneNumber(EmployeeManager* empManager, char* currPhoneNumber);
int			compareEmployeeBySalary(const void* v1, const void* v2);
int			compareEmployeeBySeniority(const void* v1, const void* v2);
int			compareEmployeeByType(const void* v1, const void* v2);
int			compareEmployeeByName(const void* v1, const void* v2);
void		sortEmployee(EmployeeManager* empManager);
Employee*	findEmployeeByParameter(const Employee** pEmployeeArr, int numOfEmployees, eSortType sortType);
void		findEmployee(const EmployeeManager* empManager);
eSortType	getSortType();
void		printEmployeeArr(const EmployeeManager* empManager);
void		freeEmployeeArr(Employee** empArr, int size);
void		printSalaryExpenses(EmployeeManager* empManager);
Employee** allocateEmployeeArr(int size);

void		showEmployeeMenu();
void		manageEmployees(EmployeeManager* empManager);



