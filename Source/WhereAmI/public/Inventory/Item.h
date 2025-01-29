// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Key UMETA(DisplayName = "Key"),
	Herb UMETA(DisplayName = "Herb"),
	Ammo UMETA(DisplayName = "Ammo"),
	Weapon UMETA(DisplayName = "Weapon")
};

UCLASS()
class WHEREAMI_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FName ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int32 MaxStack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int32 Quantity;
	
	UFUNCTION(BlueprintCallable, Category="Item")
	virtual void Use(class APlayerCharacter* Player);

};
