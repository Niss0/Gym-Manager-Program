#include "GymTextFile.h"
#include "GymBinFile.h"

#define TEXT_FILE_NAME "test_gym_data.txt"
#define BIN_FILE_NAME "test_gym_data.bin"

int initGymFromFile(Gym* pGym);

int main()
{
	Gym gym;
	if (!initGymFromFile(&gym))
	{
		printf("\nCreating gym data manually: \n");
		if (!initGymNoFile(&gym))
			printf("Error init gym manually \n");
	}
	int choice;
	do
	{
		printHeader("Gym Manager");
		showMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			managementCases(&gym);
			break;
		case 2:
			financeCases(&gym);
			break;
		case 3:
			storeCases(&gym.store, &gym.trManager);
			break;
		case EXIT:
			if (!writeGymToTextFile(&gym, TEXT_FILE_NAME))
				printf("Error saving gym to text file \n");
			else if (!writeGymToBinFile(&gym, BIN_FILE_NAME))
				printf("Error writing gym to file \n");
			
			freeGymRec(&gym, 5);
			printf("Gym saved Successfully to files \n");
			break;
		default:
			printf("Wrong option, Please Try again \n\n");
			timeDelay(2);
			break;
		} 
	} while (choice != EXIT);
}

int initGymFromFile(Gym* pGym)
{
	int fileChoice;
	int firstTime = 1;
	do
	{
		if (firstTime)
			firstTime = 0;
		else
			printf("Wrong option, your choice should be 1-2. Try again. \n");

		printf("1) Load gym from text file \n");
		printf("2) Load gym from binary file \n");
		scanf("%d", &fileChoice);

	} while (fileChoice != 1 && fileChoice != 2);
	
	switch (fileChoice)
	{
	case 1:
		HANDLE_ERRORS(readGymFromTextFile(pGym, TEXT_FILE_NAME),
			printf("Error loading gym from text file \n"), 0);

		printf("Gym Successfully loaded from text file! \n");
		break;
	case 2:
		HANDLE_ERRORS(initGymFromBinFile(pGym, BIN_FILE_NAME),
			printf("Error loading gym from binary file \n"), 0);

		printf("Gym Successfully loaded from binary file! \n");
		break;
	} 
	return 1;
}







