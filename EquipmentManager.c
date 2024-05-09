#include "EquipmentManager.h"

int initEquipmentManager(EquipmentManager* equipManager)
{
	equipManager->equipmentList = (LIST*)malloc(sizeof(LIST));
	if (!L_init(equipManager->equipmentList))
		return 0;
	
	equipManager->numOfEquipment = 0;
	equipManager->nextSerialNum = 1;
	return 1;
}

int addEquipment(EquipmentManager* equipManager)
{
	Equipment* pEquipment = (Equipment*)calloc(1, sizeof(Equipment));
	if (!pEquipment)
		return 0;

	initEquipment(pEquipment);
	pEquipment->serialNum = equipManager->nextSerialNum++;				// update equipment's serial number

	NODE* newNode = &equipManager->equipmentList->head;
	newNode = L_insert(newNode, pEquipment);
	if (!newNode)
	{
		L_free(equipManager->equipmentList, free);
		return 0;
	}
	equipManager->numOfEquipment++;
	return 1;

}

Equipment* findEquipmentBySerialNumber(const EquipmentManager* equipManager, int currSerialNum)
{
	NODE* curNode = equipManager->equipmentList->head.next;
	Equipment* pEquipment;
	while (curNode != NULL)
	{
		pEquipment = (Equipment*)(curNode->key);
		if (isEquipmentSerialNumber(pEquipment, currSerialNum))
			return curNode->key;
		curNode = curNode->next;
	}
	return NULL;
}

int isEquipmentSerialNumber(const Equipment* equipManager, int serialNum)
{
	return equipManager->serialNum == serialNum;
}

void printEquipmentList(const EquipmentManager* equipManager)
{
	if (equipManager->numOfEquipment == 0)
	{
		printf("\nThere are no equipments to print \n\n");
		return;
	}

	else if (equipManager->numOfEquipment == 1)
		printf("\nThere is only one equipment: \n");
	else
		printf("\nThere are %d equipments: \n", equipManager->numOfEquipment);

	L_print(equipManager->equipmentList, printEquipment);		
	printf("\n");
}

void freeEquipments(LIST* lst)
{
	NODE* curNode = lst->head.next;
	NODE* temp;
	while (curNode != NULL)
	{
		temp = curNode->next;
		free((Equipment*)curNode->key);
		curNode = curNode->next;
	}
}



void showEquipmentMenu()
{
	printf("1) Add Equipment \n");
	printf("2) Print all Equipments \n");
	printf("-1) Return to main menu \n");
}

void manageEquipments(EquipmentManager* equipManager)
{
	int choice;
	printHeader("Equipment Department");
	do
	{
		showEquipmentMenu();
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			if (!addEquipment(equipManager))
				printf("Error adding an Equipment \n\n");
			break;
		case 2:
			printEquipmentList(equipManager);
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

