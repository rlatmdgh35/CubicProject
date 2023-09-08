#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Cubic.generated.h"

UCLASS()
class CUBICPROJECT_API AC_Cubic : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Cubic();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	bool RandomColor(int32 InValue, int32 &OutValue);
	bool RandomColor(int32 InValue, int32 &OutValue1, int32 &OutValue2);

	void MakeTrue(int32 InValue1, int32 InValue2);
	void MakeTrue(int32 InValue1, int32 InValue2, int32 InValue3);


private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* BlockMesh[27];

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Plane[54];

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterial* MainColor[7];
	/*
	MainColor[0] -> White
	MainColor[1] -> Blue
	MainColor[2] -> Red
	MainColor[3] -> Green
	MainColor[4] -> Orange
	MainColor[5] -> Yellow
	MainCOlor[6] -> Black
	*/

private:
	class UMaterial* Color[48];

private:
	bool bCan_WB = true;
	bool bCan_WR = true;
	bool bCan_WG = true;
	bool bCan_WO = true;
	bool bCan_YB = true;
	bool bCan_YR = true;
	bool bCan_YG = true;
	bool bCan_YO = true;
	bool bCan_BR = true;
	bool bCan_RG = true;
	bool bCan_GO = true;
	bool bCan_OB = true;
	bool bCan_WBR = true;
	bool bCan_WRG = true;
	bool bCan_WGO = true;
	bool bCan_WOB = true;
	bool bCan_YBR = true;
	bool bCan_YRG = true;
	bool bCan_YGO = true;
	bool bCan_YOB = true;
	



};
