#pragma once
#include "General.h"
#include "Person.h"

#define JOB_TYPES					5

#define	BASE_RECEPTIONIST_SALARY	1200
#define BASE_TRAINER_SALARY			1500	
#define BASE_CLEANER_SALARY			750
#define BASE_MANAGER_SALARY			1800	
#define BASE_SELLER_SALARY			1200

#define SALARY_BONUS				25

static const int baseSalary[JOB_TYPES] = { BASE_RECEPTIONIST_SALARY, BASE_TRAINER_SALARY,
BASE_CLEANER_SALARY, BASE_MANAGER_SALARY, BASE_SELLER_SALARY };

typedef enum { eReceptionist, eTrainer, eCleaner, eManager, eSeller, eNofEmployeeTypes	
} eEmployeeType;

static const char* EmployeeTypeStr[eNofEmployeeTypes] = { "Receptionist", "Trainer", "Cleaner", "Manager", "Seller"};

typedef struct 
{
	Person			personalData;	
	int				salary;				
	int				seniority;					
	eEmployeeType	empType;			
} Employee;


void			initEmployee(Employee* pEmployee);
void			initSalary(Employee* pEmployee);
void			getSalary(Employee* pEmployee);
void			getSeniority(Employee* pEmployee);
eEmployeeType	getEmployeeType();
void			printEmployee(const void* v);
void			freeEmployee(Employee* pEmployee);
