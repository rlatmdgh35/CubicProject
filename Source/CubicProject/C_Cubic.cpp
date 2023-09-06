#include "C_Cubic.h"
#include "Kismet/KismetMathLibrary.h"


#define Test

AC_Cubic::AC_Cubic()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_Cubic::BeginPlay()
{
	Super::BeginPlay();

#ifdef Test
	TArray<int32> K;
	TArray<int32> Check;


	K.Add(UKismetMathLibrary::RandomInteger(20));
	


	for (uint8 i = 1; i < 10; i++)
	{
		K.Add(UKismetMathLibrary::RandomInteger(20));
		Check.Add(K[K.Num() - 2]);

		for (uint8 j = 0; j < Check.Num() - 1; j++)
		{
			if (Check[j] == K[i])
			{
				if (!!Check[j])
				{
					UE_LOG(LogTemp, Log, TEXT("Check[%d] : %d"), j, Check[j]);
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("Check[%d] is null"), j);
				}


				if (!!K[i])
				{
					UE_LOG(LogTemp, Log, TEXT("K[%d] : %d"), i, K[i]);
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("K[%d] is null"), i);
				}

				/*K.Remove(K[i]);
				Check.Remove(Check[i - 1]);
				--i;*/


				break;
			}
		}
	}


	for (uint8 i = 0; i < 10; i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::FromInt(K[i]));
	}
#endif







}

void AC_Cubic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

