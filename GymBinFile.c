#include "GymBinFile.h"


int	writeGymToBinFile(const Gym* pGym, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	HANDLE_ERRORS(fp, printf("Error openning gym file to write\n"), 0);

	HANDLE_ERRORS(writeGymDetailsToBinFile(pGym, fp),
		printf("Error writing gym details to file\n"); fclose(fp), 0);

	HANDLE_ERRORS(writeGymEmployeesToBinFile(&pGym->empManager, fp),
		printf("Error writing gym employees to file\n"); fclose(fp), 0);

	HANDLE_ERRORS(writeGymEquipmentsToBinFile(&pGym->equipManager, fp),
		printf("Error writing gym equipments to file\n"); fclose(fp), 0);

	HANDLE_ERRORS(writeGymTraineesToBinFile(&pGym->trManager, fp),
		printf("Error writing gym trainees to file\n"); fclose(fp), 0);

	HANDLE_ERRORS(writeGymStoreToBinFile(&pGym->store, fp),
		printf("Error writing gym store to file\n"); fclose(fp), 0);

	fclose(fp);
	return 1;
}

int writeGymDetailsToBinFile(const Gym* pGym, FILE* fp)
{
	HANDLE_ERRORS(writeStringToBinFile(pGym->name, fp),
		printf("Error writing gym name to binary file"), 0); // Write gym name to file

	HANDLE_ERRORS(writeGymAddressToBinFile(&pGym->address, fp),
		printf("Error writing gym address to binary file"), 0);

	HANDLE_ERRORS(writeDoubleToBinFile(pGym->income, fp),
		printf("Error writing gym income to binary file"), 0); // Write gym income to file

	HANDLE_ERRORS(writeDoubleToBinFile(pGym->expenses, fp),
		printf("Error writing gym expenses to binary file"), 0); // Write gym expenses to file

	return 1;

}

int writeGymAddressToBinFile(const Address* pAddress, FILE* fp)
{
	HANDLE_ERRORS(writeStringToBinFile(pAddress->city, fp),
		printf("Error writing gym city to binary file"), 0); // Write city to file 

	HANDLE_ERRORS(writeStringToBinFile(pAddress->street, fp),
		printf("Error writing gym street to binary file"), 0); // Write street to file

	HANDLE_ERRORS(writeIntToBinFile(pAddress->streetNum, fp),
		printf("Error writing gym street number to binary file"), 0); // Write street number to file

	HANDLE_ERRORS(writeIntToBinFile(pAddress->floorNum, fp),
		printf("Error writing gym floor number to binary file"), 0); // Write floor number to file

	return 1;
}

int	writeGymEmployeesToBinFile(const EmployeeManager* empManager, FILE* fp)
{

	HANDLE_ERRORS(writeDoubleToBinFile(empManager->expenses, fp),
		printf("Error loading gym expenses on employees to binary file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(empManager->numOfEmployee, fp),
		printf("Error loading num of employees to binary file"), 0);

	for (int i = 0; i < empManager->numOfEmployee; i++)
	{
		HANDLE_ERRORS(writeEmployeeToBinFile(empManager->employeeArr[i], fp),
			printf("Error loading employee %d to binary file", i), 0); // 
	}
	return 1;

}

int writeEmployeeToBinFile(const Employee* pEmployee, FILE* fp)
{
	HANDLE_ERRORS(writePersonToBinFile(&pEmployee->personalData, fp),
		printf("Error writing person"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pEmployee->salary, fp),
		printf("Error writing employee salary to file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pEmployee->seniority, fp),
		printf("Error writing employee seniority to file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pEmployee->empType, fp),
		printf("Error writing employee type to file"), 0);

	return 1;
}

int writePersonToBinFile(const Person* pPerson, FILE* fp)
{
	HANDLE_ERRORS(writeStringToBinFile(pPerson->name, fp),
		printf("Error writing name to file"), 0);

	HANDLE_ERRORS(writeStringToBinFile(pPerson->phoneNum, fp),
		printf("Error writing phone number to file"), 0);

	return 1;
}

int	writeGymTraineesToBinFile(const TraineeManager* trManager, FILE* fp)
{
	HANDLE_ERRORS(writeIntToBinFile(trManager->income, fp),
		printf("Error writing income from trainees to binary file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(trManager->numOfTrainee, fp),
		printf("Error writing num of trainees to binary file"), 0);

	for (int i = 0; i < trManager->numOfTrainee; i++)
	{
		HANDLE_ERRORS(writeTraineeToBinFile(trManager->traineeArr[i], fp),
			printf("Error writing trainee number %d to binary file", i), 0);
	}
	return 1;
}

int	writeTraineeToBinFile(const Trainee* pTrainee, FILE* fp)
{
	HANDLE_ERRORS(writePersonToBinFile(&pTrainee->personalData, fp),
		printf("Error writing trainee details to binary file\n"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pTrainee->subscriptionType, fp),
		printf("Error writing subscription type to binary file\n"), 0);

	HANDLE_ERRORS(writeWorkoutToBinFile(pTrainee->workout, fp),
		printf("Error writing workout to binary file\n"), 0);

	return 1;
}

int	writeWorkoutToBinFile(const Workout* pWorkout, FILE* fp)
{
	HANDLE_ERRORS(writeIntToBinFile(pWorkout->numOfExercise, fp),
		printf("Error writing number of exercises to binary file"), 0);

	for (int i = 0; i < pWorkout->numOfExercise; i++)
	{
		HANDLE_ERRORS(writeExerciseToBinFile(pWorkout->ExerciseArr[i], fp),
			printf("Error writing exercise to binary file"), 0);
	}

	return 1;
}

int	writeExerciseToBinFile(const Exercise* pExercise, FILE* fp)
{
	HANDLE_ERRORS(writeEquipmentToBinFile(&pExercise->equipment, fp),
		printf("Error writing equipment to binary file"), 0);

	if (pExercise->equipment.equipmentType == eAerobic)
	{
		HANDLE_ERRORS(writeAerobicExerciseToBinFile(&pExercise->aerobicExercise, fp),
			printf("Error writing aerobic exercise to binary file"), 0);
	}
	else // Strength Exercise
	{
		HANDLE_ERRORS(writeStrengthExerciseToBinFile(&pExercise->strengthExercise, fp),
			printf("Error writing aerobic exercise to binary file"), 0);
	}

	return 1;
}

int writeStrengthExerciseToBinFile(const StrengthExercise* pExercise, FILE* fp)
{
	HANDLE_ERRORS(writeIntToBinFile(pExercise->numOfSets, fp),
		printf("Error writing exercise sets to binary file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pExercise->numOfRepetitions, fp),
		printf("Error writing exercise reps to binary file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pExercise->weight, fp),
		printf("Error writing exercise weight to binary file"), 0);

	return 1;
}

int writeAerobicExerciseToBinFile(const AerobicExercise* pExercise, FILE* fp)
{
	HANDLE_ERRORS(writeIntToBinFile(pExercise->difficulty, fp),
		printf("Error writing exercise difficulty to binary file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pExercise->duration, fp),
		printf("Error writing exercise duration to binary file"), 0);

	return 1;
}

int writeEquipmentToBinFile(const Equipment* pEquip, FILE* fp)
{
	HANDLE_ERRORS(writeStringToBinFile(pEquip->name, fp),
		printf("Error writing equipment name to binary file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pEquip->serialNum, fp),
		printf("Error writing equipment serial num to binary file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pEquip->equipmentType, fp),
		printf("Error writing equipment type to binary file"), 0);

	if (pEquip->equipmentType == eAerobic)
	{
		HANDLE_ERRORS(writeIntToBinFile(pEquip->aerobic.maxDifficulty, fp),
			printf("Error writing equipment max difficulty to binary file"), 0);
	}
	else
	{
		HANDLE_ERRORS(writeIntToBinFile(pEquip->strength.maxWeight, fp),
			printf("Error writing equipment max weight to binary file"), 0);
	}

	return 1;
}

int	writeGymEquipmentsToBinFile(const EquipmentManager* pEquip, FILE* fp)
{
	HANDLE_ERRORS(writeIntToBinFile(pEquip->nextSerialNum, fp),
		printf("Error writing next serial num of equipment to binary file\n"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pEquip->numOfEquipment, fp),
		printf("Error writing number of equipments to binary file\n"), 0);

	NODE* newNode = pEquip->equipmentList->head.next;

	for (int i = 0; i < pEquip->numOfEquipment; i++)
	{
		HANDLE_ERRORS(writeEquipmentToBinFile((const Equipment*)newNode->key, fp),
			printf("Error writing equipment to binary file\n"), 0);

		newNode = newNode->next;
	}

	return 1;
}

int writeCompressedProductToBinFile(const Product* pProduct, FILE* fp)
{
	BYTE data[4] = { 0 };
	BYTE len = (BYTE)strlen(pProduct->name);
	CHECK_IF_NOT_EQUALS(fwrite(&len, sizeof(BYTE), 1, fp), 1, 0);
	HANDLE_ERRORS(writeCharsToBinFile(pProduct->name, len, fp),
		printf("Error writing product name to binary file"), 0);

	data[0] = pProduct->price >> 2;
	data[1] = pProduct->price << 6 | pProduct->stock >> 4;
	data[2] = pProduct->stock << 4 | pProduct->amountSold >> 8;
	data[3] = pProduct->amountSold & 0xFF;

	CHECK_IF_NOT_EQUALS(fwrite(data, sizeof(BYTE), 4, fp), 4, 0);

	//name len is 1 byte
	//name is len bytes (without /0)
	//price is 10 Bytes
	//stock is 10 Bytes
	//amountSold is 12 Bytes

	return 1;
}

int	writeGymStoreToBinFile(const Store* pStore, FILE* fp)
{
	HANDLE_ERRORS(writeDoubleToBinFile(pStore->income, fp),
		printf("Error writing store income to binary file"), 0);

	HANDLE_ERRORS(writeDoubleToBinFile(pStore->expenses, fp),
		printf("Error writing store income to binary file"), 0);

	HANDLE_ERRORS(writeIntToBinFile(pStore->numOfProducts, fp),
		printf("Error writing num of products to binary file"), 0);

	for (int i = 0; i < pStore->numOfProducts; i++)
	{
		HANDLE_ERRORS(writeCompressedProductToBinFile(&pStore->productsArr[i], fp),
			printf("Error loading product number %d to binary file", i), 0);

		HANDLE_ERRORS(writeIntToBinFile(pStore->supplierPrices[i], fp),
			printf("Error loading product number %d's supplier price to binary file", i), 0);

		HANDLE_ERRORS(writeIntToBinFile(pStore->stockCap[i], fp),
			printf("Error loading product number %d's stock cap to binary file", i), 0);
	}

	return 1;
}

int	initGymFromBinFile(Gym* pGym, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	HANDLE_ERRORS(fp, printf("Error openning gym file to write\n"), 0);

	HANDLE_ERRORS(readGymDetailsFromBinFile(pGym, fp),
		printf("Error loading gym details from binary file\n"); fclose(fp), 0);

	HANDLE_ERRORS(initEmployeeManagerFromBinFile(&pGym->empManager, fp),
		printf("Error loading gym employees from binary file\n"); fclose(fp);
	freeGymRec(pGym, 1), 0);

	HANDLE_ERRORS(initEquipmentManagerFromBinFile(&pGym->equipManager, fp),
		printf("Error loading gym employees from binary file\n"); fclose(fp);
	freeGymRec(pGym, 2), 0);

	HANDLE_ERRORS(initTraineeManagerFromBinFile(&pGym->trManager, fp),
		printf("Error loading trainee manager from binary file\n"); fclose(fp);
	freeGymRec(pGym, 3), 0);

	HANDLE_ERRORS(readGymStoreFromBinFile(&pGym->store, fp),
		printf("Error loading gym employees from binary file\n"); fclose(fp);
	freeGymRec(pGym, 4), 0);

	fclose(fp);

	return 1;
}


int	readGymDetailsFromBinFile(Gym* pGym, FILE* fp)
{
	HANDLE_ERRORS(readStringFromBinFile(&pGym->name, fp),
		printf("Error reading gym name from binary file\n"), 0);

	HANDLE_ERRORS(readGymAddressFromBinFile(&pGym->address, fp),
		printf("Error reading gym address from binary file"), 0);

	HANDLE_ERRORS(readDoubleFromBinFile(&pGym->income, fp),
		printf("Error reading gym income from binary file"), 0); // Write gym income to file

	HANDLE_ERRORS(readDoubleFromBinFile(&pGym->expenses, fp),
		printf("Error reading gym expenses from binary file"), 0); // Write gym expenses to file

	return 1;
}

int	initEmployeeManagerFromBinFile(EmployeeManager* empManager, FILE* fp)
{
	HANDLE_ERRORS(readDoubleFromBinFile(&empManager->expenses, fp),
		printf("Error reading gym expenses on employees from binary file\n"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&empManager->numOfEmployee, fp),
		printf("Error reading num of employees from binary file\n"), 0);

	HANDLE_ERRORS(readGymEmployeesFromBinFile(empManager, fp),
		printf("Error reading employees from binary file\n"), 0);

	return 1;
}

int	readGymEmployeesFromBinFile(EmployeeManager* empManager, FILE* fp)
{
	empManager->employeeArr = allocateEmployeeArr(empManager->numOfEmployee);

	for (int i = 0; i < empManager->numOfEmployee; i++)
	{
		HANDLE_ERRORS(readEmployeeFromBinFile(empManager->employeeArr[i], fp),
			printf("Error loading employee %d to binary file", i);
		freeEmployeeArr(empManager->employeeArr, i), 0); // 
	}
	empManager->sortType = eUnSorted;
	return 1;
}

int	readEmployeeFromBinFile(Employee* pEmployee, FILE* fp)
{
	HANDLE_ERRORS(readPersonFromBinFile(&pEmployee->personalData, fp),
		printf("Error reading person from binary file"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&pEmployee->salary, fp),
		printf("Error reading employee salary from binary file"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&pEmployee->seniority, fp),
		printf("Error reading employee seniority from binary file"), 0);

	HANDLE_ERRORS(readEmpTypeFromBinFile(&(pEmployee->empType), fp),
		printf("Error reading employee type from binary file"), 0);

	return 1;
}

int initTraineeManagerFromBinFile(TraineeManager* trManager, FILE* fp)
{

	HANDLE_ERRORS(readIntFromBinFile(&trManager->income, fp),
		printf("Error reading trainees income from binary file\n"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&trManager->numOfTrainee, fp),
		printf("Error reading num of trainees from binary file\n"), 0);

	HANDLE_ERRORS(readGymTraineesFromBinFile(trManager, fp),
		printf("Error reading trainees from binary file\n"), 0);

	return 1;
}

int	readGymTraineesFromBinFile(TraineeManager* trManager, FILE* fp)
{
	trManager->traineeArr = allocateTraineeArr(trManager->numOfTrainee);

	for (int i = 0; i < trManager->numOfTrainee; i++)
	{
		HANDLE_ERRORS(readTraineeFromBinFile(trManager->traineeArr[i], fp),
			printf("Error reading trainee number %d from binary file", i);
		freeTraineeArr(trManager->traineeArr, i), 0);
	}
	return 1;
}

int	readTraineeFromBinFile(Trainee* pTrainee, FILE* fp)
{
	HANDLE_ERRORS(readPersonFromBinFile(&pTrainee->personalData, fp),
		printf("Error reading trainee details from binary file\n"), 0);

	HANDLE_ERRORS(readSubTypeFromBinFile(&pTrainee->subscriptionType, fp),
		printf("Error reading subscription type from binary file\n"), 0);

	pTrainee->workout = (Workout*)malloc(sizeof(Workout));
	CHECK_IF_EQUALS(pTrainee->workout, NULL, 0);
	HANDLE_ERRORS(readWorkoutFromBinFile(pTrainee->workout, fp),
		printf("Error reading workout from binary file\n"), 0);

	return 1;
}

int	readWorkoutFromBinFile(Workout* pWorkout, FILE* fp)
{
	HANDLE_ERRORS(readIntFromBinFile(&pWorkout->numOfExercise, fp),
		printf("Error reading number of exercises from binary file"), 0);

	pWorkout->ExerciseArr = allocateExerciseArr(pWorkout->numOfExercise);

	for (int i = 0; i < pWorkout->numOfExercise; i++)
	{
		HANDLE_ERRORS(readExerciseFromBinFile(pWorkout->ExerciseArr[i], fp),
			printf("Error writing exercise to binary file"), 0);
	}

	return 1;
}

int	readExerciseFromBinFile(Exercise* pExercise, FILE* fp)
{
	HANDLE_ERRORS(readEquipmentFromBinFile(&pExercise->equipment, fp),
		printf("Error writing equipment to binary file"), 0);

	if (pExercise->equipment.equipmentType == eAerobic)
	{
		HANDLE_ERRORS(readAerobicExerciseFromBinFile(&pExercise->aerobicExercise, fp),
			printf("Error writing aerobic exercise to binary file"), 0);
		pExercise->print = printAerobicExercise;
		pExercise->setExercise = setAerobicExercise;
	}
	else // Strength Exercise
	{
		HANDLE_ERRORS(readStrengthExerciseFromBinFile(&pExercise->strengthExercise, fp),
			printf("Error writing aerobic exercise to binary file"), 0);
		pExercise->print = printStrengthExercise;
		pExercise->setExercise = setStrengthExercise;
	}

	return 1;
}

int	readAerobicExerciseFromBinFile(AerobicExercise* pExercise, FILE* fp)
{
	HANDLE_ERRORS(readIntFromBinFile(&pExercise->difficulty, fp),
		printf("Error reading exercise difficulty from binary file"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&pExercise->duration, fp),
		printf("Error reading exercise duration from binary file"), 0);

	return 1;
}

int	readStrengthExerciseFromBinFile(StrengthExercise* pExercise, FILE* fp)
{
	HANDLE_ERRORS(readIntFromBinFile(&pExercise->numOfSets, fp),
		printf("Error reading exercise sets from binary file"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&pExercise->numOfRepetitions, fp),
		printf("Error reading exercise reps from binary file"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&pExercise->weight, fp),
		printf("Error reading exercise weight from binary file"), 0);

	return 1;
}

int	initEquipmentManagerFromBinFile(EquipmentManager* equipManager, FILE* fp)
{
	equipManager->equipmentList = (LIST*)malloc(sizeof(LIST));
	HANDLE_ERRORS(L_init(equipManager->equipmentList), free(equipManager->equipmentList), 0);

	HANDLE_ERRORS(readIntFromBinFile(&equipManager->nextSerialNum, fp),
		printf("Error reading equipment next serial num from binary file"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&equipManager->numOfEquipment, fp),
		printf("Error reading number of equipments from binary file"), 0);

	HANDLE_ERRORS(readGymEquipmentsFromBinFile(equipManager, fp),
		L_free(equipManager->equipmentList, free), 0);

	return 1;

}

int	readGymEquipmentsFromBinFile(EquipmentManager* equipManager, FILE* fp)
{

	NODE* newNode = &equipManager->equipmentList->head;

	for (int i = 0; i < equipManager->numOfEquipment; i++)
	{
		Equipment* pEquip = (Equipment*)malloc(sizeof(Equipment));
		HANDLE_ERRORS(readEquipmentFromBinFile(pEquip, fp),
			printf("Error reading equipment number %d from binary file\n", i), 0);

		newNode = L_insert(newNode, pEquip);
		HANDLE_ERRORS(newNode, L_free(equipManager->equipmentList, free), 0);
	}

	return 1;
}

int	readEquipmentFromBinFile(Equipment* pEquip, FILE* fp)
{
	HANDLE_ERRORS(readFixSizeStrFromBinFile(pEquip->name, fp),
		printf("Error reading equipment name from binary file"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&pEquip->serialNum, fp),
		printf("Error reading equipment serial num from binary file"), 0);

	HANDLE_ERRORS(readEquipTypeFromBinFile(&pEquip->equipmentType, fp),
		printf("Error reading equipment type from binary file"), 0);

	if (pEquip->equipmentType == eAerobic)
	{
		HANDLE_ERRORS(readIntFromBinFile(&pEquip->aerobic.maxDifficulty, fp),
			printf("Error reading equipment max difficulty from binary file"), 0);
		pEquip->print = printAerobicEquipment;
		pEquip->setEquipment = setAerobicEquipment;
	}
	else
	{
		HANDLE_ERRORS(readIntFromBinFile(&pEquip->strength.maxWeight, fp),
			printf("Error reading equipment max weight from binary file"), 0);
		pEquip->print = printStrengthEquipment;
		pEquip->setEquipment = setStrengthEquipment;
	}

	return 1;
}

int initStoreArraysFromBinFile(Store* pStore, FILE* fp)
{
	HANDLE_ERRORS(readIntFromBinFile(&pStore->numOfProducts, fp),
		printf("Error reading num of products from binary file\n"), 0);

	pStore->productsArr = (Product*)malloc(pStore->numOfProducts * sizeof(Product));
	HANDLE_ERRORS(pStore->productsArr, printf("Error creating products from binary file\n"), 0);

	pStore->supplierPrices = (int*)malloc(pStore->numOfProducts * sizeof(int));
	HANDLE_ERRORS(pStore->supplierPrices, printf("Error creating supplier prices array from binary file\n");
	free(pStore->productsArr), 0);

	pStore->stockCap = (int*)malloc(pStore->numOfProducts * sizeof(int));
	HANDLE_ERRORS(pStore->stockCap, printf("Error creating stock cap array from binary file\n");
	free(pStore->productsArr); free(pStore->supplierPrices), 0);

	return 1;
}

int	readGymStoreFromBinFile(Store* pStore, FILE* fp)
{
	HANDLE_ERRORS(readDoubleFromBinFile(&pStore->income, fp),
		printf("Error reading store income from binary file\n"), 0);

	HANDLE_ERRORS(readDoubleFromBinFile(&pStore->expenses, fp),
		printf("Error reading store income from binary file\n"), 0);

	CHECK_IF_EQUALS(initStoreArraysFromBinFile(pStore, fp), 0, 0);

	for (int i = 0; i < pStore->numOfProducts; i++)
	{
		HANDLE_ERRORS(readCompressedProductFromBinFile(&pStore->productsArr[i], fp),
			printf("Error reading product number %d from binary file\n", i), 0);

		HANDLE_ERRORS(readIntFromBinFile(&pStore->supplierPrices[i], fp),
			printf("Error reading product number %d supplier price from binary file\n", i), 0);

		HANDLE_ERRORS(readIntFromBinFile(&pStore->stockCap[i], fp),
			printf("Error reading product number %d stock cap from binary file\n", i), 0);
	}

	return 1;
}

int readCompressedProductFromBinFile(Product* pProduct, FILE* fp)
{
	CHECK_IF_EQUALS(pProduct, NULL, 0);
	BYTE len;
	CHECK_IF_NOT_EQUALS(fread(&len, sizeof(BYTE), 1, fp), 1, 0);
	HANDLE_ERRORS(readCharsFromBinFile(pProduct->name, len, fp),
		printf("Error reading product name\n"), 0);
	pProduct->name[len] = '\0';

	BYTE data[4];
	CHECK_IF_NOT_EQUALS(fread(data, sizeof(BYTE), 4, fp), 4, 0);
	pProduct->price = (data[0] << 2) | (data[1] >> 6);
	pProduct->stock = ((data[1] & 0x3F) << 4) | (data[2] >> 4);
	pProduct->amountSold = ((data[2] & 0x0F) << 8) | data[3];

	return 1;
}

int readGymAddressFromBinFile(Address* pAddress, FILE* fp)
{
	HANDLE_ERRORS(readFixSizeStrFromBinFile(pAddress->city, fp),
		printf("Error reading address city from binary file"), 0);

	HANDLE_ERRORS(readFixSizeStrFromBinFile(pAddress->street, fp),
		printf("Error reading address street from binary file"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&pAddress->streetNum, fp),
		printf("Error reading address street number from binary file"), 0);

	HANDLE_ERRORS(readIntFromBinFile(&pAddress->floorNum, fp),
		printf("Error reading address floor from binary file"), 0);

	return 1;
}

int readPersonFromBinFile(Person* pPerson, FILE* fp)
{
	HANDLE_ERRORS(readStringFromBinFile(&pPerson->name, fp),
		printf("Error reading name from file"), 0);

	HANDLE_ERRORS(readFixSizeStrFromBinFile(pPerson->phoneNum, fp),
		printf("Error reading phone number from file"), 0);

	return 1;
}

int	 readEmpTypeFromBinFile(eEmployeeType* pVal, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fread(pVal, sizeof(int), 1, fp), 1, 0);

	return 1;
}

int	 readSubTypeFromBinFile(eSubscriptionType* pVal, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fread(pVal, sizeof(int), 1, fp), 1, 0);

	return 1;
}

int	 readEquipTypeFromBinFile(eEquipmentType* pVal, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fread(pVal, sizeof(int), 1, fp), 1, 0);

	return 1;
}