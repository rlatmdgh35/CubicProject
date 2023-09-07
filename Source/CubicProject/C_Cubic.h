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
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* BlockMesh[27];

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Plane[54];

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterial* White;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterial* Red;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterial* Green;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterial* Blue;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterial* Orange;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterial* Yellow;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterial* Black;





private:
	class UMaterial* Color[48];

private:
	float Serface;

	



};
