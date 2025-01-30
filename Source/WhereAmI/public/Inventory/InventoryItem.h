// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "InventoryItem.generated.h"

USTRUCT(BlueprintType)
struct WHEREAMI_API FInventoryItem
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	AItem* ItemReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int32 Quantity;
	
	FInventoryItem();
	~FInventoryItem();

	FInventoryItem(AItem* ItemReference, int32 Quantity);
};
