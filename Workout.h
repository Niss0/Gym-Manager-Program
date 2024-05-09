#pragma once
#include "Exercise.h"


typedef struct
{
	Exercise**		ExerciseArr;
	int				numOfExercise;
} Workout;

void		initWorkout(Workout* pWorkout);
int			createWorkout(Workout* pWorkout, const EquipmentManager* eqManager);
int			addExercise(Workout* pWorkout, const EquipmentManager* eqManager);
void		deleteExercise(Workout* pWorkout);
void		printWorkout(const Workout* pWorkout);
void		freeExerciseArr(Exercise** exerciseArr, int size);
void		freeWorkout(Workout* pWorkout);
Exercise**	allocateExerciseArr(int size);

void		updateWorkoutMenu();
