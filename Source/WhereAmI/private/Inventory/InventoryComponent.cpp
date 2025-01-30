// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxInventorySlots = 8;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

bool UInventoryComponent::AddItem(AItem* Item)
{
	if (!Item || !HasSpace()) return false;

	for (FInventoryItem& InventoryItem : Inventory)
	{
		if (InventoryItem.Quantity < InventoryItem.ItemReference->MaxStack)
		{
			int32 SpaceLeft = InventoryItem.ItemReference->MaxStack - InventoryItem.Quantity;
			int32 AmountToAdd = FMath::Min(SpaceLeft, Item->Quantity);

			InventoryItem.Quantity += AmountToAdd;
			Item->Quantity -= AmountToAdd;

			if (Item->Quantity <= 0)
			{
				Item->Destroy();
			}
			return true;
		}
	}

	if (Inventory.Num() < MaxInventorySlots)
	{
		Inventory.Add(FInventoryItem(Item, Item->Quantity));
		Item->Destroy();
		return true;
	}

	return false;
}

bool UInventoryComponent::RemoveItem(AItem* Item)
{
	if (!Item) return false;

	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemReference && Inventory[i].ItemReference->ItemName == Item->ItemName)
		{
			Inventory.RemoveAt(i);
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::HasSpace() const
{
	return Inventory.Num() < MaxInventorySlots;
}

