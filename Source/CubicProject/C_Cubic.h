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

};
