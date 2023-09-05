#include "C_Cubic.h"
#include <time.h>



AC_Cubic::AC_Cubic()
{
	PrimaryActorTick.bCanEverTick = true;

	srand(time(NULL));
}

void AC_Cubic::BeginPlay()
{
	Super::BeginPlay();
	


	TArray<int> K;
	TArray<int> Check;



	for (int i = 0; i < 5; i++)
	{
		K.Add(i);
		if (i == 3)
		{
			K.Empty(i);
			--i;
		}

	}

	for (int i = 0; i < 5; i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::FromInt(K[i]));
	}







	/*
	K.Add(rand() % 100);

	for (uint8 i = 1; i < 10; i++)
	{
		K.Add(rand() % 100);
		Check.Add(K[K.Num() - 2]);
		for (uint8 j = 0; j < Check.Num(); j++)
		{
			if (Check[j] == K[i])
			{
				K.Empty(i);
				Check.Empty(i - 1);
				--i;
				break;
			}
		}
	}


	for (uint8 i = 0; i < 10; i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::FromInt(K[i]));
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::FromInt(K.Num()));
	*/

}

void AC_Cubic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

