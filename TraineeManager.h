#pragma once
#include "Trainee.h"
#include "Workout.h"

#define REGULAR_PRICE	50
#define VIP_PRICE		100

typedef struct
{
	Trainee**	traineeArr;			
	int			numOfTrainee;		
	int			income;				
} TraineeManager;

void		initTraineeManager(TraineeManager* trManager);
int			addTrainee(TraineeManager* trManager);
void		deleteTrainee(TraineeManager* trManager);
int			isUniqeTraineeByPhoneNumber(TraineeManager* trManager, char* currPhoneNumber);
int			createTraineeWorkout(TraineeManager* trManager, const EquipmentManager* equipManager);
Trainee*	findTraineeByIndex(const TraineeManager* trManager);	
void		getLiftRecordByMuscle(const TraineeManager* trManager, eEquipmentType muscle);
int			getTraineeLiftRecord(const Trainee* pTrainee, eEquipmentType muscle);
void		printStrongestLifter(const TraineeManager* trManager);
void		printTraineeWorkout(const TraineeManager* trManager);
void		printTraineeArr(const TraineeManager* trManager);
void		printTraineesIncome(TraineeManager* trManager);
Trainee**	allocateTraineeArr(int size);
void		freeTraineeArr(Trainee** traineeArr, int size);

void		showTraineeMenu();
void		manageTrainees(TraineeManager* trManager, EquipmentManager* equipManager);
int			updateWorkoutCases(TraineeManager* trManager, EquipmentManager* equipManager);
void		updateWorkout(Workout* pWorkout, EquipmentManager* equipManager);