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
	C_Helpers::GetAsset(&MainColor[1], "/Game/Materials/MAT_Blue");
	C_Helpers::GetAsset(&MainColor[2], "/Game/Materials/MAT_Red");
	C_Helpers::GetAsset(&MainColor[3], "/Game/Materials/MAT_Green");
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
		BlockMesh[i]->SetMaterial(0, MainColor[6]);
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
				BlockMesh[index]->SetRelativeLocation(FVector(135 * (k - 1), 135 * (j - 1), 135 * (i - 1)));
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



	// Set Color The Center
	for (int32 i = 0; i < 6; i++)
		Plane[9 * i + 4]->SetMaterial(0, MainColor[i]);

	// Set Color Buttom Plane
	for (int32 i = 0; i < 3; i++)
	{
		for (int32 j = 0; j < 3; j++)
		{
			int32 index = i * 3 + j;

			if (index % 2 == 1) // Even Number
			{
				int32 randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				int32 outValue;
				Plane[index]->SetMaterial(0, MainColor[randomValue]);

				while (true)
				{
					if (RandomColor(randomValue, outValue))
					{
						if (index == 1)		Plane[16]->SetMaterial(0, MainColor[outValue]);
						if (index == 3)		Plane[43]->SetMaterial(0, MainColor[outValue]);
						if (index == 5)		Plane[25]->SetMaterial(0, MainColor[outValue]);
						if (index == 7)		Plane[34]->SetMaterial(0, MainColor[outValue]);

						// randomValue != outValue
						if (randomValue < outValue)		MakeTrue(randomValue, outValue);
						else							MakeTrue(outValue, randomValue);
						
						break;
					}
					else	randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				}
			}
			else if (index % 2 == 0 && !(i == 1 && j == 1)) // Odd Number (5 Excluded)
			{
				int32 randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				int32 outValue1;
				int32 outValue2;
				Plane[index]->SetMaterial(0, MainColor[randomValue]);

				while (true)
				{
					if (RandomColor(randomValue, outValue1, outValue2))
					{
						if (index == 0)
						{
							Plane[44]->SetMaterial(0, MainColor[outValue1]);
							Plane[15]->SetMaterial(0, MainColor[outValue2]);
						}
						if (index == 2)
						{
							Plane[17]->SetMaterial(0, MainColor[outValue1]);
							Plane[24]->SetMaterial(0, MainColor[outValue2]);
						}
						if (index == 6)
						{
							Plane[35]->SetMaterial(0, MainColor[outValue1]);
							Plane[42]->SetMaterial(0, MainColor[outValue2]);
						}
						if (index == 8)
						{
							Plane[26]->SetMaterial(0, MainColor[outValue1]);
							Plane[33]->SetMaterial(0, MainColor[outValue2]);
						}

						// randomValue != outValue1 != outValue2
						if (randomValue < outValue1 && randomValue < outValue2)
						{
							if (outValue1 < outValue2)		MakeTrue(randomValue, outValue1, outValue2);
							else							MakeTrue(randomValue, outValue2, outValue1);
						}
						else if (outValue1 < randomValue && outValue1 < outValue2)
						{
							if (randomValue < outValue2)	MakeTrue(outValue1, randomValue, outValue2);
							else							MakeTrue(outValue1, outValue2, randomValue);
						}
						else
						{
							if (randomValue < outValue1)	MakeTrue(outValue2, randomValue, outValue1);
							else							MakeTrue(outValue2, outValue1, randomValue);
						}
						break;
					}
					else	randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				}
			}
			
		}
	}
	
	// Set Color Top Plane
	for (int32 i = 0; i < 3; i++)
	{
		for (int32 j = 0; j < 3; j++)
		{
			int32 index = 45 + i * 3 + j;

			if (index % 2 == 0) // Even Number
			{
				int32 randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				int32 outValue;
				Plane[index]->SetMaterial(0, MainColor[randomValue]);

				while (true)
				{
					if (RandomColor(randomValue, outValue))
					{
						if (index == 46)		Plane[28]->SetMaterial(0, MainColor[outValue]);
						if (index == 48)		Plane[37]->SetMaterial(0, MainColor[outValue]);
						if (index == 50)		Plane[19]->SetMaterial(0, MainColor[outValue]);
						if (index == 52)		Plane[10]->SetMaterial(0, MainColor[outValue]);

						// randomValue != outValue
						if (randomValue < outValue)		MakeTrue(randomValue, outValue);
						else							MakeTrue(outValue, randomValue);

						break;
					}
					else	randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				}
			}
			else if (index % 2 == 1 && !(i == 1 && j == 1)) // Odd Number (5 Excluded)
			{
				int32 randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				int32 outValue1;
				int32 outValue2;
				Plane[index]->SetMaterial(0, MainColor[randomValue]);

				while (true)
				{
					if (RandomColor(randomValue, outValue1, outValue2))
					{
						if (index == 45)
						{
							Plane[36]->SetMaterial(0, MainColor[outValue1]);
							Plane[29]->SetMaterial(0, MainColor[outValue2]);
						}
						if (index == 47)
						{
							Plane[27]->SetMaterial(0, MainColor[outValue1]);
							Plane[20]->SetMaterial(0, MainColor[outValue2]);
						}
						if (index == 51)
						{
							Plane[9]->SetMaterial(0, MainColor[outValue1]);
							Plane[38]->SetMaterial(0, MainColor[outValue2]);
						}
						if (index == 53)
						{
							Plane[18]->SetMaterial(0, MainColor[outValue1]);
							Plane[11]->SetMaterial(0, MainColor[outValue2]);
						}

						// randomValue != outValue1 != outValue2
						if (randomValue < outValue1 && randomValue < outValue2)
						{
							if (outValue1 < outValue2)		MakeTrue(randomValue, outValue1, outValue2);
							else							MakeTrue(randomValue, outValue2, outValue1);
						}
						else if (outValue1 < randomValue && outValue1 < outValue2)
						{
							if (randomValue < outValue2)	MakeTrue(outValue1, randomValue, outValue2);
							else							MakeTrue(outValue1, outValue2, randomValue);
						}
						else
						{
							if (randomValue < outValue1)	MakeTrue(outValue2, randomValue, outValue1);
							else							MakeTrue(outValue2, outValue1, randomValue);
						}
						break;
					}
					else	randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
				}
			}
		}
	}

	// Set Color Midde Plane
	for (int32 i = 0; i < 4; i++)
	{
		int32 index = 9 * i + 14;

		int32 randomValue = UKismetMathLibrary::RandomIntegerInRange(0, 5);
		int32 outValue;

		Plane[index]->SetMaterial(0, MainColor[randomValue]);
		while (true)
		{
			if (RandomColor(randomValue, outValue))
			{
				if (index == 41)	Plane[12]->SetMaterial(0, MainColor[outValue]);
				else				Plane[index + 7]->SetMaterial(0, MainColor[outValue]);
				break;
			}
		}
	}
}

void AC_Cubic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AC_Cubic::RandomColor(int32 InValue, int32& OutValue)
{
	int32 rand = UKismetMathLibrary::RandomIntegerInRange(0, 3);

	if (InValue == 0)
		{
			if (rand == 0 && bCan_WB == true)			OutValue = 1;
			else if (rand == 1 && bCan_WR == true)		OutValue = 2;
			else if (rand == 2 && bCan_WG == true)		OutValue = 3;
			else if (rand == 3 && bCan_WO == true)		OutValue = 4;
			else return false;
		}
	if (InValue == 1)
		{
			if (rand == 0 && bCan_WB == true)			OutValue = 0;
			else if (rand == 1 && bCan_BR == true)		OutValue = 2;
			else if (rand == 2 && bCan_OB == true)		OutValue = 4;
			else if (rand == 3 && bCan_YB == true)		OutValue = 5;
			else return false;
		}
	if (InValue == 2)
		{
			if (rand == 0 && bCan_WR == true)			OutValue = 0;
			else if (rand == 1 && bCan_BR == true)		OutValue = 1;
			else if (rand == 2 && bCan_RG == true)		OutValue = 3;
			else if (rand == 3 && bCan_YR == true)		OutValue = 5;
			else return false;
		}
	if (InValue == 3)
		{
			if (rand == 0 && bCan_WG == true)			OutValue = 0;
			else if (rand == 1 && bCan_RG == true)		OutValue = 2;
			else if (rand == 2 && bCan_GO == true)		OutValue = 4;
			else if (rand == 3 && bCan_YG == true)		OutValue = 5;
			else return false;
		}
	if (InValue == 4)
		{
			if (rand == 0 && bCan_WO == true)			OutValue = 0;
			else if (rand == 1 && bCan_OB == true)		OutValue = 1;
			else if (rand == 2 && bCan_GO == true)		OutValue = 3;
			else if (rand == 3 && bCan_YO == true)		OutValue = 5;
			else return false;
		}
	if (InValue == 5)
		{
			if (rand == 0 && bCan_YB == true)			OutValue = 1;
			else if (rand == 1 && bCan_YR == true)		OutValue = 2;
			else if (rand == 2 && bCan_YG == true)		OutValue = 3;
			else if (rand == 3 && bCan_YO == true)		OutValue = 4;
			else return false;
		}
	return true;
}

bool AC_Cubic::RandomColor(int32 InValue, int32& OutValue1, int32& OutValue2)
{
	int32 rand = UKismetMathLibrary::RandomInteger64InRange(0, 3);

	if (InValue == 0)
	{
		if (rand == 0 && bCan_WBR == true)
		{
			OutValue1 = 1;
			OutValue2 = 2;
		}
		else if (rand == 1 && bCan_WRG == true)
		{
			OutValue1 = 2;
			OutValue2 = 3;
		}
		else if (rand == 2 && bCan_WGO == true)
		{
			OutValue1 = 3;
			OutValue2 = 4;
		}
		else if (rand == 3 && bCan_WOB == true)
		{
			OutValue1 = 4;
			OutValue2 = 1;
		}
		else
			return false;
	}
	if (InValue == 1)
	{
		if (rand == 0 && bCan_YBR == true)
		{
			OutValue1 = 5;
			OutValue2 = 2;
		}
		else if (rand == 1 && bCan_WBR == true)
		{
			OutValue1 = 0;
			OutValue2 = 2;
		}
		else if (rand == 2 && bCan_WOB == true)
		{
			OutValue1 = 5;
			OutValue2 = 4;
		}
		else if (rand == 3 && bCan_YOB == true)
		{
			OutValue1 = 0;
			OutValue2 = 4;
		}
		else
			return false;
	}
	if (InValue == 2)
	{
		if (rand == 0 && bCan_YRG == true)
		{
			OutValue1 = 5;
			OutValue2 = 3;
		}
		else if (rand == 1 && bCan_WRG == true)
		{
			OutValue1 = 0;
			OutValue2 = 3;
		}
		else if (rand == 2 && bCan_WBR == true)
		{
			OutValue1 = 0;
			OutValue2 = 1;
		}
		else if (rand == 3 && bCan_YBR == true)
		{
			OutValue1 = 5;
			OutValue2 = 1;
		}
		else
			return false;
	}
	if (InValue == 3)
	{
		if (rand == 0 && bCan_YGO == true)
		{
			OutValue1 = 5;
			OutValue2 = 4;
		}
		else if (rand == 1 && bCan_WGO == true)
		{
			OutValue1 = 0;
			OutValue2 = 4;
		}
		else if (rand == 2 && bCan_WRG == true)
		{
			OutValue1 = 0;
			OutValue2 = 2;
		}
		else if (rand == 3 && bCan_YRG == true)
		{
			OutValue1 = 5;
			OutValue2 = 2;
		}
		else
			return false;
	}
	if (InValue == 4)
	{
		if (rand == 0 && bCan_YOB == true)
		{
			OutValue1 = 5;
			OutValue2 = 1;
		}
		else if (rand == 1 && bCan_WOB == true)
		{
			OutValue1 = 0;
			OutValue2 = 1;
		}
		else if (rand == 2 && bCan_WGO)
		{
			OutValue1 = 0;
			OutValue2 = 3;
		}
		else if (rand == 3 && bCan_YGO)
		{
			OutValue1 = 5;
			OutValue2 = 3;
		}
		else
			return false;
	}
	if (InValue == 5)
	{
		if (rand == 0 && bCan_YBR == true)
		{
			OutValue1 = 1;
			OutValue2 = 2;
		}
		else if (rand == 1 && bCan_YRG == true)
		{
			OutValue1 = 2;
			OutValue2 = 3;
		}
		else if (rand == 2 && bCan_YGO == true)
		{
			OutValue1 = 3;
			OutValue2 = 4;
		}
		else if (rand == 3 && bCan_YOB == true)
		{
			OutValue1 = 4;
			OutValue2 = 1;
		}
		else
			return false;
	}
	return true;
}

void AC_Cubic::MakeTrue(int32 InValue1, int32 InValue2)
{
	if (InValue1 == 0)
	{
		if (InValue2 == 1)						bCan_WB = false;
		if (InValue2 == 2)						bCan_WR = false;
		if (InValue2 == 3)						bCan_WG = false;
		if (InValue2 == 4)						bCan_WO = false;
	}
	if (InValue1 == 1)
	{
		if (InValue2 == 2)						bCan_BR = false;
		if (InValue2 == 4)						bCan_OB = false;
		if (InValue2 == 5)						bCan_YB = false;

	}
	if (InValue1 == 2)
	{
		if (InValue2 == 3)						bCan_RG = false;
		if (InValue2 == 5)						bCan_YR = false;
	}
	if (InValue1 == 3)
	{
		if (InValue2 == 4)						bCan_GO = false;
		if (InValue2 == 5)						bCan_YG = false;
	}
	if (InValue1 == 4 && InValue2 == 5)			bCan_YO = false;
}

void AC_Cubic::MakeTrue(int32 InValue1, int32 InValue2, int32 InValue3)
{
	if (InValue1 == 0)
	{
		if (InValue2 == 1 && InValue3 == 2)		bCan_WBR = false;
		if (InValue2 == 1 && InValue3 == 4)		bCan_WOB = false;
		if (InValue2 == 2 && InValue3 == 3)		bCan_WRG = false;
		if (InValue2 == 3 && InValue3 == 4)		bCan_WGO = false;
	}
	if (InValue1 == 1)
	{
		if (InValue2 == 2 && InValue3 == 5)		bCan_YBR = false;
		if (InValue1 == 4 && InValue3 == 5)		bCan_YOB = false;
	}
	if (InValue1 == 2)							bCan_YRG = false;
	if (InValue1 == 3)							bCan_YGO = false;
}
