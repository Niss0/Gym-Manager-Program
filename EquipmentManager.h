#pragma once
#include "Equipment.h"
#include "list.h"

typedef struct
{
	int				numOfEquipment;		
	LIST*			equipmentList;		
	int				nextSerialNum;		
} EquipmentManager;

int				initEquipmentManager(EquipmentManager* equipManager);
int				addEquipment(EquipmentManager* equipManager);
Equipment*		findEquipmentBySerialNumber(const EquipmentManager* equipManager, int currSerialNum);
int				isEquipmentSerialNumber(const Equipment* pEquipment, int serialNum);
void			printEquipmentList(const EquipmentManager* equipManager);
void			freeEquipments(LIST* lst);

void			showEquipmentMenu();
void			manageEquipments(EquipmentManager* eqManager);
