// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryItem.h"

FInventoryItem::FInventoryItem()
{
	ItemReference = nullptr;
	Quantity = 1;
}

FInventoryItem::~FInventoryItem()
{
}

FInventoryItem::FInventoryItem(AItem* ItemReference, int32 Quantity)
{
	this->ItemReference = ItemReference;
	this->Quantity = Quantity;
}
