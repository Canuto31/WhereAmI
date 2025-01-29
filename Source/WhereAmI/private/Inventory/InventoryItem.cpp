// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryItem.h"

FInventoryItem::FInventoryItem()
{
	ItemName = TEXT("DefaultItem");
	Quantity = 1;
	MaxQuantity = 1;
	ItemClass = nullptr;
}

FInventoryItem::~FInventoryItem()
{
}
