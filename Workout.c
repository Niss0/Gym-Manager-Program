#include "Workout.h"

void initWorkout(Workout* pWorkout)
{
	pWorkout->ExerciseArr = NULL;
	pWorkout->numOfExercise = 0;
}

int createWorkout(Workout* pWorkout, const EquipmentManager* eqManager)
{
	if (pWorkout->numOfExercise != 0)
	{
		printf("There is already an existing workout \n");
		return 0;
	}
	int numOfExercises = getNumberInRange("number of exercises you want in your workout", 1,
		eqManager->numOfEquipment);
	pWorkout->ExerciseArr = (Exercise**)malloc(sizeof(Exercise*));

	for (int i = 0; i < numOfExercises; i++)
		addExercise(pWorkout, eqManager);

	return 1;
}

int addExercise(Workout* pWorkout, const EquipmentManager* eqManager)
{
	if (eqManager->numOfEquipment == 0)
	{
		printf("There are no equipments \n");
		return 0;
	}

	Exercise* newExercise = (Exercise*)malloc(sizeof(Exercise));
	Exercise** newExeArr = pWorkout->ExerciseArr;
	if (newExercise == NULL)
		return 0;

	initExercise(newExercise, eqManager);
	newExeArr = (Exercise**)realloc(newExeArr, sizeof(Exercise*) * (pWorkout->numOfExercise + 1));
	if (newExeArr == NULL)
	{
		free(newExeArr);
		return 0;
	}

	pWorkout->ExerciseArr = newExeArr;
	pWorkout->ExerciseArr[(pWorkout->numOfExercise)++] = newExercise;
	return 1;
}

void deleteExercise(Workout* pWorkout)
{
	int deleteIndex;
	if (pWorkout->numOfExercise == 0)
	{
		printf("There are no exercise to delete \n\n");
		return;
	}

	printWorkout(pWorkout);
	deleteIndex = getNumberInRange("exercise's index you want to delete", 1, pWorkout->numOfExercise) - 1;
	Exercise* tempExercise = pWorkout->ExerciseArr[deleteIndex];
	pWorkout->ExerciseArr[deleteIndex] = pWorkout->ExerciseArr[--(pWorkout->numOfExercise)];
	free(tempExercise);
	printf("\n");
}

void printWorkout(const Workout* pWorkout)
{
	if (pWorkout->numOfExercise == 0)
	{
		printf("There is no workout yet \n\n");
		return;
	}
	generalArrayFunction(pWorkout->ExerciseArr, pWorkout->numOfExercise, sizeof(Exercise*), printExercise);
	printf("\n");
}

void freeExerciseArr(Exercise** exerciseArr, int size)
{
	for (int i = 0; i < size; i++)
	{
		free(exerciseArr[i]);
	}
	free(exerciseArr);
}

void freeWorkout(Workout* pWorkout)
{
	freeExerciseArr(pWorkout->ExerciseArr, pWorkout->numOfExercise);
	free(pWorkout);
}

Exercise** allocateExerciseArr(int size)
{
	Exercise** exerciseArr = (Exercise**)malloc(sizeof(Exercise*) * size);
	CHECK_IF_EQUALS(exerciseArr, NULL, NULL);
	for (int i = 0; i < size; i++)
	{
		exerciseArr[i] = (Exercise*)malloc(sizeof(Exercise));
		if (exerciseArr[i] == NULL)
		{
			freeExerciseArr(exerciseArr, i);
		}
	}
	return exerciseArr;
}



void updateWorkoutMenu()
{
	printf("What do you want to do? \n");
	printf("1) Add Exercise \n");
	printf("2) Delete Exercise \n");
	printf("3) Update Exercise \n");
	printf("-1) Return to previous menu \n");
}
