#pragma once
#include "Gym.h"
#include "FileHelper.h"

int		writeGymToBinFile(const Gym* pGym, const char* fileName);
int		writeGymDetailsToBinFile(const Gym* pGym, FILE* fp);
int		writeGymAddressToBinFile(const Address* pAddress, FILE* fp);
int		writeGymEmployeesToBinFile(const EmployeeManager* empManager, FILE* fp);
int     writeEmployeeToBinFile(const Employee* pEmployee, FILE* fp);
int		writePersonToBinFile(const Person* pPerson, FILE* fp);
int		writeGymTraineesToBinFile(const TraineeManager* trManager, FILE* fp);
int		writeTraineeToBinFile(const Trainee* pTrainee, FILE* fp);
int		writeWorkoutToBinFile(const Workout* pWorkout, FILE* fp);
int		writeExerciseToBinFile(const Exercise* pExercise, FILE* fp);
int		writeAerobicExerciseToBinFile(const AerobicExercise* pExercise, FILE* fp);
int		writeStrengthExerciseToBinFile(const StrengthExercise* pExercise, FILE* fp);
int		writeEquipmentToBinFile(const Equipment* pEquip, FILE* fp);
int		writeGymEquipmentsToBinFile(const EquipmentManager* pEquip, FILE* fp);
int		writeGymDetailsToBinFile(const Gym* pGym, FILE* fp);
int		writeGymAddressToBinFile(const Address* pAddress, FILE* fp);
int		writeGymEmployeesToBinFile(const EmployeeManager* empManager, FILE* fp);
int     writeEmployeeToBinFile(const Employee* pEmployee, FILE* fp);
int		writePersonToBinFile(const Person* pPerson, FILE* fp);
int		writeGymTraineesToBinFile(const TraineeManager* trManager, FILE* fp);
int		writeTraineeToBinFile(const Trainee* pTrainee, FILE* fp);
int		writeWorkoutToBinFile(const Workout* pWorkout, FILE* fp);
int		writeExerciseToBinFile(const Exercise* pExercise, FILE* fp);
int		writeAerobicExerciseToBinFile(const AerobicExercise* pExercise, FILE* fp);
int		writeStrengthExerciseToBinFile(const StrengthExercise* pExercise, FILE* fp);
int		writeEquipmentToBinFile(const Equipment* pEquip, FILE* fp);
int		writeGymEquipmentsToBinFile(const EquipmentManager* pEquip, FILE* fp);
int		writeCompressedProductToBinFile(const Product* pProduct, FILE* fp);
int		writeGymStoreToBinFile(const Store* pStore, FILE* fp);

int		initGymFromBinFile(Gym* pGym, const char* fileName);
int		readGymDetailsFromBinFile(Gym* pGym, FILE* fp);
int		readGymEmployeesFromBinFile(EmployeeManager* empManager, FILE* fp);
int		readGymTraineesFromBinFile(TraineeManager* trManager, FILE* fp);
int		readGymEquipmentsFromBinFile(EquipmentManager* equipManager, FILE* fp);
int		readGymStoreFromBinFile(Store* pStore, FILE* fp);
int		readCompressedProductFromBinFile(Product* pProduct, FILE* fp);
int		readGymAddressFromBinFile(Address* pAddress, FILE* fp);
int		readEmployeeFromBinFile(Employee* pEmployee, FILE* fp);
int		initTraineeManagerFromBinFile(TraineeManager* trManager, FILE* fp);
int		readTraineeFromBinFile(Trainee* pTrainee, FILE* fp);
int		readEquipmentFromBinFile(Equipment* pEquip, FILE* fp);
int		readWorkoutFromBinFile(Workout* pWorkout, FILE* fp);
int		readExerciseFromBinFile(Exercise* pExercise, FILE* fp);
int		readStrengthExerciseFromBinFile(StrengthExercise* pExercise, FILE* fp);
int		readAerobicExerciseFromBinFile(AerobicExercise* pExercise, FILE* fp);
int		readPersonFromBinFile(Person* pPerson, FILE* fp);
int		readEmpTypeFromBinFile(eEmployeeType* pVal, FILE* fp);
int		readSubTypeFromBinFile(eSubscriptionType* pVal, FILE* fp);
int		readEquipTypeFromBinFile(eEquipmentType* pVal, FILE* fp);
int		initEquipmentManagerFromBinFile(EquipmentManager* equipManager, FILE* fp);
int 	initStoreArraysFromBinFile(Store* pStore, FILE* fp);
int		readGymStoreFromBinFile(Store* pStore, FILE* fp);
int		initEmployeeManagerFromBinFile(EmployeeManager* empManager, FILE* fp);
