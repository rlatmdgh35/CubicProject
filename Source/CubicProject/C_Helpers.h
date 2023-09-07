#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

// ----------------------------------------------------------------------
// Macros
#define CheckNull(p) { if ((p) == nullptr) return; }
#define CheckNullResult(p, result) { if ((p) == nullptr) return result; }

#define CheckTrue(p) { if ((p) == true) return; }
#define CheckTrueResult(p, result) { if ((p) == true) return result; }

#define CheckFalse(p) { if ((p) == false) return; }
#define CheckFalseResult(p, result) { if ((p) == false) return result; }
// ----------------------------------------------------------------------



// ----------------------------------------------------------------------
// C_Helpers
class CUBICPROJECT_API C_Helpers
{
public:
	template<typename T>
	static void GetAsset(T** OutAsset, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> Asset(*InPath);
		verifyf(Asset.Succeeded(), L"Asset Not Found");

		*OutAsset = Asset.Object;
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"Class Not Found");
		*OutClass = asset.Class;
	}




	template<typename T>
	static void AssetDynamic(T** OutAsset, FString InPath)
	{
		// Create Dynamic Material
		T* Asset = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
		verifyf(!!Asset, L"Is Not Valid");

		*OutAsset = Asset;
	}




public:
	template<typename T>
	static void CreateSceneComponent(AActor* InActor, T** OutComp, FName InName, USceneComponent* InParent = nullptr)
	{
		*OutComp = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*OutComp)->SetupAttachment(InParent);
		}
		else
		{
			InActor->SetRootComponent(*OutComp);
		}
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComp, FName InName)
	{
		*OutComp = InActor->CreateDefaultSubobject<T>(InName);
	}

	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}



};

// ----------------------------------------------------------------------
