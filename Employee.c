#include "Employee.h"

void initEmployee(Employee* pEmployee)
{
    initPerson(&pEmployee->personalData);
    getSeniority(pEmployee);
    pEmployee->empType = getEmployeeType();
    initSalary(pEmployee);
}

void initSalary(Employee* pEmployee)
{
    pEmployee->salary = (pEmployee->seniority * SALARY_BONUS) + baseSalary[pEmployee->empType];
}

void getSalary(Employee* pEmployee)
{
    pEmployee->salary = getPositiveNumber("salary (in dollers)");
}

void getSeniority(Employee* pEmployee)
{
    pEmployee->seniority = getNumberInRange("seniority (in years)", 0, 60);
}

eEmployeeType getEmployeeType()
{
    int option;
    printf("\n");
    do {
        printf("Please select your job: \n");
        for (int i = 0; i < eNofEmployeeTypes; i++)
            printf("%d for %s\n", i, EmployeeTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNofEmployeeTypes);
    getchar();
    printf("\n");
    return (eEmployeeType)option;
}

void printEmployee(const void* v)
{
    const Employee* pEmployee = *(const Employee**)v;
    printPerson(&pEmployee->personalData);
    printf("is working %d years as a %s with salary of %d$ \n", pEmployee->seniority, EmployeeTypeStr[pEmployee->empType], pEmployee->salary);
}

void freeEmployee(Employee* pEmployee)
{
    free(pEmployee->personalData.name);
    free(pEmployee);
}

