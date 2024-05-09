#pragma once
#include "EquipmentManager.h"

typedef struct
{
	int			difficulty;		
	int			duration;		
}AerobicExercise;

typedef struct
{
	int			weight;				
	int			numOfRepetitions;	
	int			numOfSets;			
}StrengthExercise;

typedef struct Exercise_
{
	void		(*setExercise)(struct Exercise_*);		
	void		(*print)(const struct Exercise_*);		
	Equipment	equipment;								
	union {
		AerobicExercise aerobicExercise;				
		StrengthExercise strengthExercise;				
	};
} Exercise;

void		initExercise(Exercise* pExercise, const EquipmentManager* eqManager);
void		selectExerciseEquipment(Exercise* pExercise, const EquipmentManager* eqManager);
int			calcBurnedCalories(const Exercise* pExercise);
void		printExercise(const void* pExercise);

void		initAerobicExercise(Exercise* pExercise);
void		setAerobicExercise(Exercise* pExercise);
void		printAerobicExercise(const Exercise* pExercise);

void		initStrengthExercise(Exercise* pExercise);
void		setStrengthExercise(Exercise* pExercise);
void		printStrengthExercise(const Exercise* pExercise);



