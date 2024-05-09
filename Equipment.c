#include "Equipment.h"

void initEquipment(Equipment* pEquipment)
{
    pEquipment->equipmentType = getEquipmentType();
    printf("Enter equipment name: \n");
    myGets(pEquipment->name, MAX_LEN);

    if (pEquipment->equipmentType == eAerobic)
        initAerobicEquipment(pEquipment);
    else 
        initStrengthEquipment(pEquipment);
    pEquipment->setEquipment(pEquipment);
    printf("\n");
}

eEquipmentType getEquipmentType()
{
    int option;
    printf("\n");
    do {
        printf("Please select equipment's type: \n");
        for (int i = 0; i < eNofEquipmentTypes; i++)
            printf("%d for %s\n", i, EquipmentTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNofEquipmentTypes);
    getchar();
    return (eEquipmentType)option;
}   

void printEquipment(const void* pEquipment)
{
    Equipment* tmpEquipment = (Equipment*)pEquipment;
    printf("Equipment name: %s, type: %s, serial number: %d, ",
        tmpEquipment->name, EquipmentTypeStr[tmpEquipment->equipmentType],tmpEquipment->serialNum);
    tmpEquipment->print(pEquipment);
}


// Aerobic Equipment

void initAerobicEquipment(Equipment* pEquipment)
{
    pEquipment->setEquipment = setAerobicEquipment;
    pEquipment->print = printAerobicEquipment;
}

void printAerobicEquipment(const Equipment* pEquipment)
{
    printf("max difficulty of %d\n", pEquipment->aerobic.maxDifficulty);
}


void setAerobicEquipment(Equipment* pEquipment)
{
    pEquipment->aerobic.maxDifficulty = getNumberInRange("aerobic equipment max difficulty", 1, MAX_DIFFICULTY);
}


// Strength Equipment

void initStrengthEquipment(Equipment* pEquipment)
{
    pEquipment->setEquipment = setStrengthEquipment;
    pEquipment->print = printStrengthEquipment;
}

void setStrengthEquipment(Equipment* pEquipment)
{
    pEquipment->strength.maxWeight = getPositiveNumber("strength equipment max weight");
}

void printStrengthEquipment(const Equipment* pEquipment)
{
    printf("max weight of %d KG \n", pEquipment->strength.maxWeight);
}
