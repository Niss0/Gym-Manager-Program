#include "Trainee.h"

int	initTrainee(Trainee* pTrainee)
{
    initPerson(&pTrainee->personalData);
    pTrainee->workout = (Workout*)malloc(sizeof(Workout));
    if (pTrainee->workout == NULL)
        return 0;
    initWorkout(pTrainee->workout);
    pTrainee->subscriptionType = getSubscriptionType();
    return 1;
}

eSubscriptionType getSubscriptionType()
{
    int option;
    printf("\n");
    do {
        printf("Please select subscription's type: \n");
        for (int i = 0; i < eNofSubscriptionTypes; i++)
            printf("%d for %s\n", i, SubscriptionTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNofSubscriptionTypes);
    getchar();
    return (eSubscriptionType)option;
}

void printTrainee(const void* v)
{
    const Trainee* pTrainee = *(const Trainee**)v;
    printPerson(&pTrainee->personalData);
    if (!pTrainee->workout)
        printf("is %s subscription and has no workout yet \n", SubscriptionTypeStr[pTrainee->subscriptionType]);
    else
        printf("is %s subscription and has %d exrcises in the workout \n",
            SubscriptionTypeStr[pTrainee->subscriptionType], pTrainee->workout->numOfExercise);
}

void freeTrainee(Trainee* pTrainee)
{
    freeWorkout(pTrainee->workout);
    free(pTrainee->personalData.name);
    free(pTrainee);
}
