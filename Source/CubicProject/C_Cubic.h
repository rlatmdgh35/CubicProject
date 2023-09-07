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
	int32 RandomColor(int32 InValue);


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
	bool bCan_WB;
	bool bCan_WR;
	bool bCan_WG;
	bool bCan_WO;
	bool bCan_YB;
	bool bCan_YR;
	bool bCan_YG;
	bool bCan_YO;
	bool bCan_BR;
	bool bCan_RG;
	bool bCan_GO;
	bool bCan_OB;
	bool bCan_WBR;
	bool bCan_WRG;
	bool bCan_WGO;
	bool bCan_WOB;
	bool bCan_YBR;
	bool bCan_YRG;
	bool bCan_YGO;
	bool bCan_YOB;
	



};
