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

	while (1)
	{
		for (uint8 i = 0; i < 100; i++)
		{
			K.Add(rand() % 100);
			Check.Add(K[K.Num()]);
			for (uint8 j = 0; j < K.Num() - 1; j++)
			{
				if (Check[j] == K[i])
				{
					K.Empty(i);
					--i;
					break;
				}
			}
		}

		break;
	}

	for (uint8 i = 0; i < 100; i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::FromInt(K[i]));
	}



}

void AC_Cubic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

