// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETypeObject : uint8
{
	Consumibles,
	Arma,
	Municion,
	Key
};

UENUM(BlueprintType)
enum class EOptionsDoIt : uint8
{
	Usar,
	Tirar,
	Equipar,
	Recargar,
	Combinar,
	Examinar
};

USTRUCT(BlueprintType)
struct FInputInfoStruct
{
	GENERATED_BODY()
	UItemDataAsset* Info;
	int quantity;
};

UCLASS()
class WHEREAMI_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETypeObject ObjectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> SpawnedEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EOptionsDoIt> Options;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMesh;
};
