// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WHEREAMI_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<FInventoryItem> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 MaxInventorySlots;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool RemoveItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool HasSpace() const;
};
