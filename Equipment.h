#pragma once
#include "General.h"
#define NUM_OF_EQUIP_TYPES   5
#define MAX_DIFFICULTY		 10
#define AVG_CALORIES_BURNED  8

typedef enum {
	eLegs, eHands, eBack, eChest, eShoulders, eAerobic, eNofEquipmentTypes
} eEquipmentType;

static const char* EquipmentTypeStr[eNofEquipmentTypes] = { "Legs", "Hands", "Back",
"Chest", "Shoulders", "Aerobic"};

typedef struct
{
	int			maxDifficulty;		
}AerobicEquipment;	

typedef struct
{
	int			maxWeight;			
}StrengthEquipment;

typedef struct Equipment_
{
	void			(*setEquipment)(struct Equipment_*);		
	void			(*print)(const struct Equipment_*);			
	eEquipmentType	equipmentType;								
	int				serialNum;									
	char			name[MAX_LEN];								
	union {
		AerobicEquipment aerobic;								
		StrengthEquipment strength;							
	};
} Equipment;


void				initEquipment(Equipment* pEquipment);
eEquipmentType		getEquipmentType();
void				printEquipment(const void* pEquipment);


void				initAerobicEquipment(Equipment* pEquipment);
void				setAerobicEquipment(Equipment* pEquipment);
void				printAerobicEquipment(const Equipment* pEquipment);

void				initStrengthEquipment(Equipment* pEquipment);
void				setStrengthEquipment(Equipment* pEquipment);
void				printStrengthEquipment(const Equipment* pEquipment);




