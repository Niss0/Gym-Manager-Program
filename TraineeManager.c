#include "TraineeManager.h"

void initTraineeManager(TraineeManager* trManager)
{
	trManager->traineeArr = NULL;
	trManager->numOfTrainee = 0;
	trManager->income = 0;
}

int addTrainee(TraineeManager* trManager)
{
	Trainee* newTrainee = (Trainee*)malloc(sizeof(Trainee));
	Trainee** newTraineeArr = trManager->traineeArr;
	int firstTime = 1;
	CHECK_IF_EQUALS(newTrainee, NULL, 0);
	
	initTrainee(newTrainee);
	do {
		if (firstTime)
			firstTime = 0;
		else if (!firstTime)
		{
			printf("This trainee's phone number is already in use. Try again.\n");
			getPhoneNumber(&newTrainee->personalData);
		}
	} while (!isUniqeTraineeByPhoneNumber(trManager, newTrainee->personalData.phoneNum));

	newTraineeArr = (Trainee**)realloc(newTraineeArr, sizeof(Trainee*) * (trManager->numOfTrainee + 1));
	HANDLE_ERRORS(newTraineeArr, free(newTrainee), 0);

	trManager->traineeArr = newTraineeArr;
	trManager->traineeArr[(trManager->numOfTrainee)++] = newTrainee;

	if (newTrainee->subscriptionType == eRegular)
		trManager->income += REGULAR_PRICE;
	else	// newTrainee->subscriptionType == eVIP
		trManager->income += VIP_PRICE;
	printf("\n");
	return 1;
}

void deleteTrainee(TraineeManager* trManager)
{
	int deleteIndex;
	if (trManager->numOfTrainee == 0)
	{
		printf("There are no trainees to delete \n\n");
		return;
	}

	printTraineeArr(trManager);
	deleteIndex = getNumberInRange("trainee's index you want to delete", 1, trManager->numOfTrainee) - 1;
	Trainee* tmpTrainee = trManager->traineeArr[deleteIndex];
	trManager->traineeArr[deleteIndex] = trManager->traineeArr[--(trManager->numOfTrainee)];
	if (tmpTrainee->subscriptionType == eRegular)
		trManager->income -= REGULAR_PRICE;
	else	// tmpTrainee->subscriptionType == eVIP
		trManager->income -= VIP_PRICE;
	printf("\n");
}

int isUniqeTraineeByPhoneNumber(TraineeManager* trManager, char* currPhoneNumber)
{
	for (int i = 0; i < trManager->numOfTrainee; i++)
	{
		if (strcmp(trManager->traineeArr[i]->personalData.phoneNum, currPhoneNumber) == 0)
			return 0;
	}
	return 1;
}

int createTraineeWorkout(TraineeManager* trManager, const EquipmentManager* equipManager)
{
	if (equipManager->numOfEquipment == 0)
	{
		printf("There are no equipments\n");
		return 0;
	}
		
	Trainee* traineeFound = findTraineeByIndex(trManager);
	CHECK_IF_EQUALS(traineeFound, NULL, 0);
	return createWorkout(traineeFound->workout, equipManager);
}

Trainee* findTraineeByIndex(const TraineeManager* trManager)
{
	if (trManager->numOfTrainee == 0)
	{
		printf("There are no trainees \n\n");
		return NULL;
	}
	generalArrayFunction(trManager->traineeArr, trManager->numOfTrainee, sizeof(Trainee*), printTrainee);
	CHECK_IF_EQUALS(trManager->numOfTrainee, 0, NULL);
	int traineeIndex = getNumberInRange("trainee's index", 1, trManager->numOfTrainee);
	return trManager->traineeArr[traineeIndex - 1];
}

void getLiftRecordByMuscle(const TraineeManager* trManager, eEquipmentType muscle)
{
	int maxWeight = 0, currWeight;
	char strongestTraineeName[MAX_LEN];
	for (int i = 0; i < trManager->numOfTrainee; i++)
	{
		currWeight = getTraineeLiftRecord(trManager->traineeArr[i], muscle);
		if (currWeight > maxWeight)
		{
			maxWeight = currWeight;
			strcpy(strongestTraineeName, trManager->traineeArr[i]->personalData.name);
		}
	}
	if (maxWeight == 0)
		printf("There are no exercises with %s's equipment \n", EquipmentTypeStr[muscle]);
	else
		printf("%s has the strongest %s with a lift record of %d KG \n", strongestTraineeName,
		EquipmentTypeStr[muscle], maxWeight);
}

int getTraineeLiftRecord(const Trainee* pTrainee, eEquipmentType muscle)
{
	int maxWeight = 0;
	for (int i = 0; i < pTrainee->workout->numOfExercise; i++)
	{
		if (pTrainee->workout->ExerciseArr[i]->equipment.equipmentType == muscle)
		{
			int currWeight = pTrainee->workout->ExerciseArr[i]->strengthExercise.weight;			
			if (currWeight > maxWeight)
				maxWeight = currWeight;
		}
	}
	return maxWeight;
}

void printStrongestLifter(const TraineeManager* trManager)
{
	if (trManager->numOfTrainee == 0)
	{
		printf("There are no trainees \n\n");
		return;
	}
	eEquipmentType muscle = getEquipmentType();
	if (muscle == eAerobic)
		printf("Aerobic's equipments has no weight \n");
	else
		getLiftRecordByMuscle(trManager, muscle);
	printf("\n");
}

void printTraineeWorkout(const TraineeManager* trManager)
{
	Trainee* traineeFound = findTraineeByIndex(trManager); // if traineeFound is NULL so we will print message inside findTraineeByIndex
	if (!traineeFound)
		return;
	if (!traineeFound->workout)
	{
		printf("Trainee has no workout yet \n\n");
		return;
	}
		
	CALL_FUNC_IF_TRUE(traineeFound, printWorkout(traineeFound->workout));
	printf("\n");
}

void printTraineesIncome(TraineeManager* trManager)
{
	double subIncome = trManager->income;
	printf("Subscriptions income: $%.2lf \n", subIncome);
}

void printTraineeArr(const TraineeManager* trManager)
{
	if (trManager->numOfTrainee == 0)
	{
		printf("There are no trainees \n\n");
		return;
	}
	generalArrayFunction(trManager->traineeArr, trManager->numOfTrainee, sizeof(Trainee*), printTrainee);
	printf("\n");
}

Trainee** allocateTraineeArr(int size)
{
	Trainee** traineeArr = (Trainee**)malloc(sizeof(Trainee*) * size);
	CHECK_IF_EQUALS(traineeArr, NULL, NULL);
	for (int i = 0; i < size; i++)
	{
		traineeArr[i] = (Trainee*)malloc(sizeof(Trainee));
		if (!traineeArr[i])
		{
			freeTraineeArr(traineeArr, i);
			return NULL;
		}
	}
	return traineeArr;
}

void freeTraineeArr(Trainee** traineeArr, int size)
{
	for (int i = 0; i < size; i++)
		freeTrainee(traineeArr[i]);
	free(traineeArr);
}




void showTraineeMenu()
{
	printf("1) Add Trainee \n");
	printf("2) Delete Trainee \n");
	printf("3) Create Trainee workout \n");		
	printf("4) Update Trainee workout \n");
	printf("5) Print strongest lifter \n");
	printf("6) Print Trainee's workout \n");				
	printf("7) Print all Trainees \n");
	printf("-1) Return to main menu \n");
}

void manageTrainees(TraineeManager* trManager, EquipmentManager* equipManager)
{
	printHeader("Trainee Department");
	int choice;
	do
	{
		showTraineeMenu();
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			if (!addTrainee(trManager))
				printf("Error adding a trainee \n\n");
			break;
		case 2: 
			deleteTrainee(trManager);
			break;
		case 3:
			if (!createTraineeWorkout(trManager, equipManager))
				printf("Error in creating new workout \n\n");
			break;
		case 4:
			if(!updateWorkoutCases(trManager, equipManager))
				printf("Error in updating workout \n\n");
			break;
		case 5:
			printStrongestLifter(trManager);
			break;
		case 6:
			printTraineeWorkout(trManager);
			break;
		case 7:
			printTraineeArr(trManager);
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

int updateWorkoutCases(TraineeManager* trManager, EquipmentManager* equipManager)
{
	Trainee* pTrainee = findTraineeByIndex(trManager);
	if (!pTrainee)
		return 0;

	if (pTrainee->workout->numOfExercise == 0)
	{
		printf("There is no Workout yet \n");
		return 0;
	}
	int choice;
	do
	{
		updateWorkoutMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			if (!addExercise(pTrainee->workout, equipManager))
				printf("Error adding exercise \n\n");
			break;
		case 2:
			deleteExercise(pTrainee->workout);
			break;
		case 3:
			updateWorkout(pTrainee->workout, equipManager);
			break;
		case EXIT:
			system("cls");
			break;
		default:
			printf("Wrong option \n");
			timeDelay(2);
			break;
		}
	} while (choice != EXIT);

	return 1;
}

void updateWorkout(Workout* pWorkout, EquipmentManager* equipManager)
{
	printWorkout(pWorkout);
	int exerciseIndex = getNumberInRange("exercise's index you want to update", 1, pWorkout->numOfExercise);
	initExercise(pWorkout->ExerciseArr[exerciseIndex], equipManager);
}