// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item.h"
#include "PlayerCharacter.h"

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemName = "DefaultItem";
	MaxStack = 1;
	Quantity = 1;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Use(APlayerCharacter* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Item used: %s"), *ItemName.ToString());
}



