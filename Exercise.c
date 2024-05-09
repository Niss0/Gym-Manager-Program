#include "Exercise.h"


void initExercise(Exercise* pExercise, const EquipmentManager* equipManager)
{
	selectExerciseEquipment(pExercise, equipManager);

	if (pExercise->equipment.equipmentType == eAerobic)
		initAerobicExercise(pExercise);
	else
		initStrengthExercise(pExercise);

	pExercise->setExercise(pExercise);
}

void selectExerciseEquipment(Exercise* pExercise, const EquipmentManager* equipManager)
{
	int currSerialNum, firstTime = 1;
	Equipment* equip;
	do {
		if (firstTime)
			firstTime = 0;
		else
			printf("\nThere is no equipment with serial number %d. Try again. \n", currSerialNum);
		printEquipmentList(equipManager);

		printf("Enter the equipment's serial number you want for the exercise: \n");
		scanf("%d", &currSerialNum);
		equip = findEquipmentBySerialNumber(equipManager, currSerialNum);
	} while (!equip);

	pExercise->equipment = *equip;

}

int calcBurnedCalories(const Exercise* pExercise)
{
	int duration = pExercise->aerobicExercise.duration;
	int difficulty = pExercise->aerobicExercise.difficulty;
	int res = (AVG_CALORIES_BURNED + difficulty) * duration;
	return res;
}

void printExercise(const void* v)
{
	const Exercise* tmpExercise = *(Exercise**)v;
	printEquipment(&tmpExercise->equipment);
	tmpExercise->print(tmpExercise);
}


void initAerobicExercise(Exercise* pExercise)
{
	pExercise->print = printAerobicExercise;
	pExercise->setExercise = setAerobicExercise;
}

void setAerobicExercise(Exercise* pExercise)
{
	pExercise->aerobicExercise.difficulty = getNumberInRange("exercise difficulty", 1,
		pExercise->equipment.aerobic.maxDifficulty);
	pExercise->aerobicExercise.duration = getPositiveNumber("exercise duration (in minutes)");
	printf("\n");
}

void printAerobicExercise(const Exercise* pExercise)
{
	int burnedCalories = calcBurnedCalories(pExercise);
	printf("duration: %d \ndifficulty level: %d \nestimated burned calories: %d \n"
		, pExercise->aerobicExercise.duration, pExercise->aerobicExercise.difficulty, burnedCalories);
}


void initStrengthExercise(Exercise* pExercise)
{
	pExercise->print = printStrengthExercise;
	pExercise->setExercise = setStrengthExercise;

}

void setStrengthExercise(Exercise* pExercise)
{
	pExercise->strengthExercise.weight = getNumberInRange("exercise weight", 0, pExercise->equipment.strength.maxWeight);
	pExercise->strengthExercise.numOfSets = getPositiveNumber("number of sets");
	pExercise->strengthExercise.numOfRepetitions = getPositiveNumber("number of repetitions");
	printf("\n");
}

void printStrengthExercise(const Exercise* pExercise)
{
	printf("Weight: %d \nNumber of Sets: %d \nNumber of Reps: %d \n", pExercise->strengthExercise.weight,
		pExercise->strengthExercise.numOfSets, pExercise->strengthExercise.numOfRepetitions);
}

