#include "GymTextFile.h"

int writeGymToTextFile(const Gym* pGym, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "w");
	HANDLE_ERRORS(fp, printf("Error opening gym file to write \n"), 0);

	HANDLE_ERRORS(pGym, fclose(fp), 0);

	HANDLE_ERRORS(writeGymDetailsToTextFile(pGym, fp),
		printf("Error writing gym to text file \n"); fclose(fp), 0);

	HANDLE_ERRORS(writeGymEmployeesToTextFile(&pGym->empManager, fp),
		printf("Error writing employees to text file \n"); fclose(fp), 0);

	HANDLE_ERRORS(writeGymEquipmentsToTextFile(&pGym->equipManager, fp),
		printf("Error writing equipments to text file \n"); fclose(fp), 0);

	HANDLE_ERRORS(writeGymTraineesToTextFile(&pGym->trManager, fp),
		printf("Error writing trainees to text file \n"); fclose(fp), 0);

	HANDLE_ERRORS(writeGymStoreToTextFile(&pGym->store, fp),
		printf("Error writing store to text file \n"); fclose(fp), 0);

	fclose(fp);
	return 1;
}

int writeGymDetailsToTextFile(const Gym* pGym, FILE* fp)
{
	fprintf(fp, "%s\n", pGym->name);

	HANDLE_ERRORS(writeAddressToTextFile(&pGym->address, fp),
		printf("Error writing gym address to text file \n"), 0);

	fprintf(fp, "%.2lf\n", pGym->income);
	fprintf(fp, "%.2lf\n", pGym->expenses);

	return 1;
}

int writeAddressToTextFile(const Address* pAddress, FILE* fp)
{
	fprintf(fp, "%s\n", pAddress->city);
	fprintf(fp, "%s\n", pAddress->street);
	fprintf(fp, "%d\n", pAddress->streetNum);
	fprintf(fp, "%d\n", pAddress->floorNum);
	return 1;
}

int writePersonToTextFile(const Person* pPerson, FILE* fp)
{
	fprintf(fp, "%s\n", pPerson->name);
	fprintf(fp, "%s\n", pPerson->phoneNum);

	return 1;
}

int writeGymEmployeesToTextFile(const EmployeeManager* empManager, FILE* fp)
{
	fprintf(fp, "%lf\n", empManager->expenses);
	fprintf(fp, "%d\n", empManager->numOfEmployee);

	for (int i = 0; i < empManager->numOfEmployee; i++)
	{
		HANDLE_ERRORS(writeEmployeeToTextFile(empManager->employeeArr[i], fp),
			printf("Error writing employee to text file \n"), 0);
	}
	return 1;
}

int writeEmployeeToTextFile(const Employee* pEmployee, FILE* fp)
{
	HANDLE_ERRORS(writePersonToTextFile(&pEmployee->personalData, fp),
		printf("Error writing person to text file \n"), 0);

	fprintf(fp, "%d\n", pEmployee->salary);
	fprintf(fp, "%d\n", pEmployee->seniority);
	fprintf(fp, "%d\n", pEmployee->empType);

	return 1;
}

int writeGymEquipmentsToTextFile(const EquipmentManager* quipManager, FILE* fp)
{
	fprintf(fp, "%d\n", quipManager->nextSerialNum);
	fprintf(fp, "%d\n", quipManager->numOfEquipment);

	NODE* curNode = quipManager->equipmentList->head.next;
	Equipment* pEquipment;

	while (curNode != NULL)
	{
		pEquipment = (Equipment*)curNode->key;
		HANDLE_ERRORS(writeEquipmentToTextFile(pEquipment, fp),
			printf("Error writing equipment to text file \n"), 0);
		curNode = curNode->next;
	}

	return 1;
}

int writeEquipmentToTextFile(const Equipment* pEquipment, FILE* fp)
{
	fprintf(fp, "%s\n", pEquipment->name);
	fprintf(fp, "%d\n", pEquipment->serialNum);
	fprintf(fp, "%d\n", pEquipment->equipmentType);

	if (pEquipment->equipmentType == eAerobic)
		fprintf(fp, "%d\n", pEquipment->aerobic.maxDifficulty);
	else
		fprintf(fp, "%d\n", pEquipment->strength.maxWeight);

	return 1;
}

int writeGymTraineesToTextFile(const TraineeManager* trManager, FILE* fp)
{
	fprintf(fp, "%d\n", trManager->income);
	fprintf(fp, "%d\n", trManager->numOfTrainee);

	for (int i = 0; i < trManager->numOfTrainee; i++)
	{
		HANDLE_ERRORS(writeTraineeToTextFile(trManager->traineeArr[i], fp),
			printf("Error writing trainee to text file \n"), 0);
	}
	return 1;
}

int writeTraineeToTextFile(const Trainee* pTrainee, FILE* fp)
{
	HANDLE_ERRORS(writePersonToTextFile(&pTrainee->personalData, fp),
		printf("Error writing person to text file \n"), 0);

	fprintf(fp, "%d\n", pTrainee->subscriptionType);

	return writeWorkoutToTextFile(pTrainee->workout, fp);
}

int writeWorkoutToTextFile(const Workout* pWorkout, FILE* fp)
{
	fprintf(fp, "%d\n", pWorkout->numOfExercise);

	for (int i = 0; i < pWorkout->numOfExercise; i++)
	{
		HANDLE_ERRORS(writeExerciseToTextFile(pWorkout->ExerciseArr[i], fp),
			printf("Error writing exercise to text file \n"), 0);
	}
	return 1;
}

int writeExerciseToTextFile(const Exercise* pExercise, FILE* fp)
{
	HANDLE_ERRORS(writeEquipmentToTextFile(&pExercise->equipment, fp),
		printf("Error writing equipment to text file \n"), 0);

	if (pExercise->equipment.equipmentType == eAerobic)
	{
		HANDLE_ERRORS(writeAerobicExerciseToTextFile(&pExercise->aerobicExercise, fp),
			printf("Error writing aerobic equipment to text file \n"), 0);
	}
	else
	{
		HANDLE_ERRORS(writeStrengthExerciseToTextFile(&pExercise->strengthExercise, fp),
			printf("Error writing strength equipment to text file \n"), 0);
	}
	return 1;
}

int writeAerobicExerciseToTextFile(const AerobicExercise* pAerobicExercise, FILE* fp)
{
	fprintf(fp, "%d\n", pAerobicExercise->difficulty);
	fprintf(fp, "%d\n", pAerobicExercise->duration);

	return 1;
}

int writeStrengthExerciseToTextFile(const StrengthExercise* pStrengthExercise, FILE* fp)
{
	fprintf(fp, "%d\n", pStrengthExercise->numOfSets);
	fprintf(fp, "%d\n", pStrengthExercise->numOfRepetitions);
	fprintf(fp, "%d\n", pStrengthExercise->weight);

	return 1;
}

int writeGymStoreToTextFile(const Store* pStore, FILE* fp)
{
	fprintf(fp, "%.2lf\n", pStore->income);
	fprintf(fp, "%.2lf\n", pStore->expenses);
	fprintf(fp, "%d\n", pStore->numOfProducts);

	for (int i = 0; i < pStore->numOfProducts; i++)
	{
		HANDLE_ERRORS(writeProductToTextFile(&pStore->productsArr[i], fp),
			printf("Error writing product to text file \n"), 0);

		fprintf(fp, "%d\n", pStore->supplierPrices[i]);
		fprintf(fp, "%d\n", pStore->stockCap[i]);
	}
	return 1;
}

int writeProductToTextFile(const Product* pProduct, FILE* fp)
{
	fprintf(fp, "%s\n", pProduct->name);								// name
	fprintf(fp, "%d\n", pProduct->price);								// price
	fprintf(fp, "%d\n", pProduct->stock);								// stock
	fprintf(fp, "%d\n", pProduct->amountSold);							//amount products sold

	return 1;
}



int readGymFromTextFile(Gym* pGym, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "r");
	HANDLE_ERRORS(fp, printf("Error opening gym file \n"), 0);

	HANDLE_ERRORS(pGym, fclose(fp), 0);

	HANDLE_ERRORS(readGymDetailsFromTextFile(pGym, fp),
		printf("Error loading gym details from text file \n"); fclose(fp), 0);

	HANDLE_ERRORS(readGymEmployeesFromTextFile(&pGym->empManager, fp),
		printf("Error loading employees from text file \n"); fclose(fp);
	freeGymRec(pGym, 1), 0);

	HANDLE_ERRORS(readGymEquipmentsFromTextFile(&pGym->equipManager, fp),
		printf("Error loading equipments from text file \n"); fclose(fp);
	freeGymRec(pGym, 2), 0);

	HANDLE_ERRORS(readGymTraineesFromTextFile(&pGym->trManager, fp),
		printf("Error loading trainees from text file \n"); fclose(fp);
	freeGymRec(pGym, 3), 0);

	HANDLE_ERRORS(readGymStoreFromTextFile(&pGym->store, fp),
		printf("Error loading store from text file \n"); fclose(fp);
	freeGymRec(pGym, 4), 0);

	fclose(fp);
	return 1;
}

int readGymDetailsFromTextFile(Gym* pGym, FILE* fp)
{
	pGym->name = readStrFromTextFile(fp);					// read char*
	CHECK_IF_EQUALS(pGym->name, NULL, 0);

	HANDLE_ERRORS(readAddressFromTextFile(&pGym->address, fp),
		printf("Error loading gym address from text file \n"), 0);


	CHECK_IF_NOT_EQUALS(fscanf(fp, "%lf\n", &pGym->income), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%lf\n", &pGym->expenses), 1, 0);


	return 1;
}

int readAddressFromTextFile(Address* pAddress, FILE* fp)
{
	fscanf(fp, " %[^\n]\n", pAddress->city);				// read char[MAX_LEN]
	fscanf(fp, " %[^\n]\n", pAddress->street);				// read char[MAX_LEN]

	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pAddress->streetNum), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pAddress->floorNum), 1, 0);

	return 1;
}

int readPersonFromTextFile(Person* pPerson, FILE* fp)
{
	pPerson->name = readStrFromTextFile(fp);
	fscanf(fp, "%s\n", pPerson->phoneNum);

	return 1;
}

int readGymEmployeesFromTextFile(EmployeeManager* empManager, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%lf\n", &empManager->expenses), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &empManager->numOfEmployee), 1, 0);

	empManager->employeeArr = (Employee**)malloc(empManager->numOfEmployee * sizeof(Employee*));
	HANDLE_ERRORS(empManager->employeeArr, printf("Error creating employees from text file"), 0);


	for (int i = 0; i < empManager->numOfEmployee; i++)
	{
		Employee* pEmployee = (Employee*)malloc(sizeof(Employee));
		HANDLE_ERRORS(readEmployeeFromTextFile(pEmployee, fp),
			printf("Error loading employee from text file \n");
		freeEmployeeArr(empManager->employeeArr, i), 0);

		empManager->employeeArr[i] = pEmployee;
	}
	empManager->sortType = eUnSorted;
	return 1;
}

int readEmployeeFromTextFile(Employee* pEmployee, FILE* fp)
{
	HANDLE_ERRORS(readPersonFromTextFile(&pEmployee->personalData, fp),
		printf("Error loading person from text file \n"), 0);

	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pEmployee->salary), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pEmployee->seniority), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pEmployee->empType), 1, 0);

	return 1;
}

int readGymEquipmentsFromTextFile(EquipmentManager* equipManager, FILE* fp)		// need to check
{
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &equipManager->nextSerialNum), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &equipManager->numOfEquipment), 1, 0);

	equipManager->equipmentList = (LIST*)malloc(sizeof(LIST));
	if (equipManager->equipmentList == NULL)
		return 0;

	HANDLE_ERRORS(L_init(equipManager->equipmentList), free(equipManager->equipmentList), 0);
	NODE* newNode = &equipManager->equipmentList->head;

	for (int i = 0; i < equipManager->numOfEquipment; i++)
	{
		Equipment* pEquipment = (Equipment*)malloc(sizeof(Equipment));
		HANDLE_ERRORS(pEquipment, printf("Error creating equipment \n"), 0);

		HANDLE_ERRORS(readEquipmentFromTextFile(pEquipment, fp),
			printf("Error loading equipment from text file \n"); free(pEquipment), 0);

		newNode = L_insert(newNode, pEquipment);
		HANDLE_ERRORS(newNode, L_free(equipManager->equipmentList, free), 0);
	}

	return 1;
}

int readEquipmentFromTextFile(Equipment* pEquipment, FILE* fp)
{
	fscanf(fp, " %[^\n]\n", pEquipment->name);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pEquipment->serialNum), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pEquipment->equipmentType), 1, 0);

	if (pEquipment->equipmentType == eAerobic)
	{
		CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pEquipment->aerobic.maxDifficulty), 1, 0);
		pEquipment->print = printAerobicEquipment;
		pEquipment->setEquipment = setAerobicEquipment;
	}
	else
	{
		CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pEquipment->strength.maxWeight), 1, 0);
		pEquipment->print = printStrengthEquipment;
		pEquipment->setEquipment = setStrengthEquipment;
	}
	return 1;
}

int readGymTraineesFromTextFile(TraineeManager* trManager, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &trManager->income), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &trManager->numOfTrainee), 1, 0);

	trManager->traineeArr = (Trainee**)malloc(trManager->numOfTrainee * sizeof(Trainee*));
	HANDLE_ERRORS(trManager->traineeArr, printf("Error creating trainees from text file"), 0);

	for (int i = 0; i < trManager->numOfTrainee; i++)
	{
		Trainee* pTrainee = (Trainee*)malloc(sizeof(Trainee));
		HANDLE_ERRORS(readTraineeFromTextFile(pTrainee, fp),
			printf("Error loading trainee from text file \n");
		freeTraineeArr(trManager->traineeArr, i), 0);

		trManager->traineeArr[i] = pTrainee;
	}
	return 1;
}

int readTraineeFromTextFile(Trainee* pTrainee, FILE* fp)
{
	HANDLE_ERRORS(readPersonFromTextFile(&pTrainee->personalData, fp),
		printf("Error loading person from text file \n"), 0);

	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pTrainee->subscriptionType), 1, 0);

	Workout* pWorkout = (Workout*)malloc(sizeof(Workout));
	HANDLE_ERRORS(readWorkoutFromTextFile(pWorkout, fp),
		printf("Error loading workout from text file \n"), 0);
	pTrainee->workout = pWorkout;

	return 1;
}

int readWorkoutFromTextFile(Workout* pWorkout, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pWorkout->numOfExercise), 1, 0);

	pWorkout->ExerciseArr = (Exercise**)malloc(pWorkout->numOfExercise * sizeof(Exercise*));
	HANDLE_ERRORS(pWorkout->ExerciseArr, printf("Error creating workout from text file"), 0);


	for (int i = 0; i < pWorkout->numOfExercise; i++)
	{
		Exercise* pExercise = (Exercise*)malloc(sizeof(Exercise));
		HANDLE_ERRORS(readExerciseFromTextFile(pExercise, fp),
			printf("Error loading exercise from text file \n"), 0);

		pWorkout->ExerciseArr[i] = pExercise;
	}
	return 1;
}

int readExerciseFromTextFile(Exercise* pExercise, FILE* fp)
{
	HANDLE_ERRORS(readEquipmentFromTextFile(&pExercise->equipment, fp),
		printf("Error loading equipment from text file \n"), 0);

	if (pExercise->equipment.equipmentType == eAerobic)
	{
		HANDLE_ERRORS(readAerobicExerciseFromTextFile(&pExercise->aerobicExercise, fp),
			printf("Error loading aerobic equipment from text file \n"), 0);
		pExercise->print = printAerobicExercise;
		pExercise->setExercise = printAerobicExercise;
	}
	else
	{
		HANDLE_ERRORS(readStrengthExerciseFromTextFile(&pExercise->strengthExercise, fp),
			printf("Error loading strength equipment from text file \n"), 0);
		pExercise->print = printStrengthExercise;
		pExercise->setExercise = printAerobicExercise;
	}
	return 1;
}

int readAerobicExerciseFromTextFile(AerobicExercise* pAerobicExercise, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pAerobicExercise->difficulty), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pAerobicExercise->duration), 1, 0);

	return 1;
}

int readStrengthExerciseFromTextFile(StrengthExercise* pStrengthExercise, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pStrengthExercise->numOfSets), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pStrengthExercise->numOfRepetitions), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pStrengthExercise->weight), 1, 0);

	return 1;
}

int readGymStoreFromTextFile(Store* pStore, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%lf\n", &pStore->income), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%lf\n", &pStore->expenses), 1, 0);

	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pStore->numOfProducts), 1, 0);

	pStore->productsArr = (Product*)malloc(pStore->numOfProducts * sizeof(Product));
	HANDLE_ERRORS(pStore->productsArr, printf("Error creating products from binary file\n"), 0);

	pStore->supplierPrices = (int*)malloc(pStore->numOfProducts * sizeof(int));
	HANDLE_ERRORS(pStore->supplierPrices, printf("Error creating supplier prices array from binary file\n");
	free(pStore->productsArr), 0);

	pStore->stockCap = (int*)malloc(pStore->numOfProducts * sizeof(int));
	HANDLE_ERRORS(pStore->stockCap, printf("Error creating stock cap array from binary file\n");
	free(pStore->productsArr); free(pStore->supplierPrices), 0);

	for (int i = 0; i < pStore->numOfProducts; i++)
	{
		Product pProduct;

		HANDLE_ERRORS(readProductFromTextFile(&pProduct, fp),
			printf("Error loading product from text file \n"), 0);

		pStore->productsArr[i] = pProduct;

		CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pStore->supplierPrices[i]), 1, 0);
		CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pStore->stockCap[i]), 1, 0);
	}
	return 1;
}

int readProductFromTextFile(Product* pProduct, FILE* fp)
{
	fscanf(fp, " %[^\n]\n", pProduct->name);				// read char[MAX_LEN]
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pProduct->price), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pProduct->stock), 1, 0);
	CHECK_IF_NOT_EQUALS(fscanf(fp, "%d\n", &pProduct->amountSold), 1, 0);

	return 1;
}
