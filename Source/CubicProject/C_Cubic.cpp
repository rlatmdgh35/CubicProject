#include "C_Cubic.h"
#include "C_Helpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Materials/Material.h"
#include "Components/StaticMeshComponent.h"


#define Test

AC_Cubic::AC_Cubic()
{
	PrimaryActorTick.bCanEverTick = true;

	C_Helpers::CreateSceneComponent(this, &RootSceneComponent, "RootSceneComponent");

	// Get Color Material Assets
	C_Helpers::GetAsset(&MainColor[0], "/Game/Materials/MAT_White");
	C_Helpers::GetAsset(&MainColor[1], "/Game/Materials/MAT_Red");
	C_Helpers::GetAsset(&MainColor[2], "/Game/Materials/MAT_Green");
	C_Helpers::GetAsset(&MainColor[3], "/Game/Materials/MAT_Blue");
	C_Helpers::GetAsset(&MainColor[4], "/Game/Materials/MAT_Orange");
	C_Helpers::GetAsset(&MainColor[5], "/Game/Materials/MAT_Yellow");
	C_Helpers::GetAsset(&MainColor[6], "/Game/Materials/MAT_Black");


	// CreateSceneComponent (Block)
	UStaticMesh* cubeMesh;
	C_Helpers::GetAsset(&cubeMesh, "/Game/StaticMeshes/SM_Cube");
	for (int32 i = 0; i < 27; i++)
	{
		FString str = "Block" + FString::FromInt(i);
		FName name(*str);
		C_Helpers::CreateSceneComponent(this, &BlockMesh[i], name, RootSceneComponent);

		BlockMesh[i]->SetStaticMesh(cubeMesh);
		BlockMesh[i]->SetMaterial(0, Black);
	}

	// CreateSceneComponent (Plane)
	UStaticMesh* planeMesh;
	C_Helpers::GetAsset(&planeMesh, "/Game/StaticMeshes/SM_Plane");
	for (int32 i = 0; i < 54; i++)
	{
		FString str = "Plane" + FString::FromInt(i);
		FName name(*str);
		C_Helpers::CreateSceneComponent(this, &Plane[i], name, RootSceneComponent);

		Plane[i]->SetStaticMesh(planeMesh);
	}


	// Set Location (Block)
	for (int32 i = 0; i < 3; i++)
	{
		for (int32 j = 0; j < 3; j++)
		{
			for (int32 k = 0; k < 3; k++)
			{
				int32 index = i * 9 + j * 3 + k;
				BlockMesh[index]->SetRelativeLocation(FVector(135 * (i - 1), 135 * (k - 1), 135 * (1 - j)));
			}
		}
	}

	// Set Location (Plane)
	for (int32 i = 0; i < 6; i++)
	{
		for (int32 j = 0; j < 3; j++)
		{
			for (int32 k = 0; k < 3; k++)
			{
				int32 index = i * 9 + j * 3 + k;

				if (i == 0)
				{
					Plane[index]->SetRelativeLocation(FVector(135.f * (j - 1), 135.f * (k - 1), -185.1f));
					Plane[index]->SetRelativeRotation(FRotator(180, 0, 0));
				}

				else if (i == 1)
				{
					Plane[index]->SetRelativeLocation(FVector(-185.1f, 135.f * (k - 1), 135.f * (1 - j)));
					Plane[index]->SetRelativeRotation(FRotator(90, 0, 0));
				}

				else if (i == 2)
				{
					Plane[index]->SetRelativeLocation(FVector(135.f * (k - 1), 185.1f, 135.f * (1 - j)));
					Plane[index]->SetRelativeRotation(FRotator(0, 0, 90));
				}

				else if (i == 3)
				{
					Plane[index]->SetRelativeLocation(FVector(185.1f, 135.f * (1 - k), 135.f * (1 - j)));
					Plane[index]->SetRelativeRotation(FRotator(270, 0, 0));
				}

				else if (i == 4)
				{
					Plane[index]->SetRelativeLocation(FVector(135 * (1 - k), -185.1f, 135.f * (1 - j)));
					Plane[index]->SetRelativeRotation(FRotator(0, 0, 270));
				}

				else
					Plane[index]->SetRelativeLocation(FVector(135.f * (1 - j), 135.f * (k - 1), 185.1f));
			}
		}
	}



}

void AC_Cubic::BeginPlay()
{
	Super::BeginPlay();


#ifndef Test
	for (int32 i = 0; i < 48; i++)
	{
		if (i % 6 == 0)			Color[i] = White;
		else if (i % 6 == 1)	Color[i] = Blue;
		else if (i % 6 == 2)	Color[i] = Red;
		else if (i % 6 == 3)	Color[i] = Green;
		else if (i % 6 == 4)	Color[i] = Orange;
		else					Color[i] = Yellow;
	}

	for (int32 i = 0; i < 10; i++)
	{
		int32 rand1 = UKismetMathLibrary::RandomIntegerInRange(0, 47);
		int32 rand2 = UKismetMathLibrary::RandomIntegerInRange(0, 47);

		GLog->Log(FString::FromInt(rand1));
		GLog->Log(FString::FromInt(rand2));

		UMaterial* swV = nullptr;
		swV = Color[rand1];
		Color[rand1] = Color[rand2];
		Color[rand2] = swV;
	}

	for (int32 i = 0; i < 6; i++)
	{
		for (int32 j = 0; j < 3; j++)
		{
			for (int32 k = 0; k < 3; k++)
			{
				int32 index = i * 9 + j * 3 + k;

				if (k == 1 && j == 1)
				{
					if (i == 0)			Plane[index]->SetMaterial(0, White);
					else if (i == 1)	Plane[index]->SetMaterial(0, Blue);
					else if (i == 2)	Plane[index]->SetMaterial(0, Red);
					else if (i == 3)	Plane[index]->SetMaterial(0, Green);
					else if (i == 4)	Plane[index]->SetMaterial(0, Orange);
					else				Plane[index]->SetMaterial(0, Yellow);
				}
				else if (index < 48)	Plane[index]->SetMaterial(0, Color[index]);
				else
				{
					for (int t = 0; t < 5; t++)
						Plane[index]->SetMaterial(0, Color[9 * t + 4]);
				}
			}
		}
	}
#endif

	for (int32 i = 0; i < 3; i++)
	{
		for (int32 j = 0; j < 3; j++)
		{
			int32 index = i * 3 + j;

			if (index % 2 == 1 && !(i == 1 && j == 1)) // Odd Number (5 Excluded)
			{
				int32 randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				Plane[index]->SetMaterial(0, MainColor[randomValue]);
			}
			else // Even Number
			{
				int32 randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				Plane[index]->SetMaterial(0, MainColor[randomValue]);

			}
		}
	}









}

void AC_Cubic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AC_Cubic::RandomColor(int32 InValue)
{
	while (true)
	{
		int32 randomColor = UKismetMathLibrary::RandomIntegerInRange(0, 3);

		if (InValue == 0)
		{
			if(randomColor == 0)

			return;
		}
		if (InValue == 1)
		{

		}
		if (InValue == 2);
		if (InValue == 3);
		if (InValue == 4);
		if (InValue == 5);


	}

}