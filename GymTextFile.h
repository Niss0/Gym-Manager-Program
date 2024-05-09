#pragma once
#include "Gym.h"

int		writeGymToTextFile(const Gym* pGym, const char* fileName);
int		writeGymDetailsToTextFile(const Gym* pGym, FILE* fp);
int		writeAddressToTextFile(const Address* pAddress, FILE* fp);
int		writePersonToTextFile(const Person* pPerson, FILE* fp);
int		writeGymEmployeesToTextFile(const EmployeeManager* empManager, FILE* fp);
int		writeEmployeeToTextFile(const Employee* pEmployee, FILE* fp);
int		writeGymEquipmentsToTextFile(const EquipmentManager* quipManager, FILE* fp);
int		writeEquipmentToTextFile(const Equipment* pEquipment, FILE* fp);
int		writeGymTraineesToTextFile(const TraineeManager* trManager, FILE* fp);
int		writeTraineeToTextFile(const Trainee* pTrainee, FILE* fp);
int		writeWorkoutToTextFile(const Workout* pWorkout, FILE* fp);
int		writeExerciseToTextFile(const Exercise* pExercise, FILE* fp);
int		writeAerobicExerciseToTextFile(const AerobicExercise* pAerobicExercise, FILE* fp);
int		writeStrengthExerciseToTextFile(const StrengthExercise* pStrengthExercise, FILE* fp);
int		writeGymStoreToTextFile(const Store* pStore, FILE* fp);
int		writeProductToTextFile(const Product* pProduct, FILE* fp);

int		readGymFromTextFile(Gym* pGym, const char* fileName);
int		readGymDetailsFromTextFile(Gym* pGym, FILE* fp);
int		readAddressFromTextFile(Address* pAddress, FILE* fp);
int		readPersonFromTextFile(Person* pPerson, FILE* fp);
int		readGymEmployeesFromTextFile(EmployeeManager* empManager, FILE* fp);
int		readEmployeeFromTextFile(Employee* pEmployee, FILE* fp);
int		readGymEquipmentsFromTextFile(EquipmentManager* quipManager, FILE* fp);
int		readEquipmentFromTextFile(Equipment* pEquipment, FILE* fp);
int		readGymTraineesFromTextFile(TraineeManager* trManager, FILE* fp);
int		readTraineeFromTextFile(Trainee* pTrainee, FILE* fp);
int		readWorkoutFromTextFile(Workout* pWorkout, FILE* fp);
int		readExerciseFromTextFile(Exercise* pExercise, FILE* fp);
int		readAerobicExerciseFromTextFile(AerobicExercise* pAerobicExercise, FILE* fp);
int		readStrengthExerciseFromTextFile(StrengthExercise* pStrengthExercise, FILE* fp);
int		readGymStoreFromTextFile(Store* pStore, FILE* fp);
int		readProductFromTextFile(Product* pProduct, FILE* fp);

char* readStrFromTextFile(FILE* fp);
