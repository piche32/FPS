// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryManagerComponent.h"
#include "ItemBase.h"
// Sets default values for this component's properties
UInventoryManagerComponent::UInventoryManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AItemBase *UInventoryManagerComponent::GetItem(const int ItemIndex)
{
	return InventoryList[ItemIndex];
}

AItemBase *UInventoryManagerComponent::GetItem(const FText Value)
{
	for (int i = 0; i < InventoryList.Num(); i++)
	{
		if (InventoryList[i]->GetName().EqualTo(Value))
		{
			return InventoryList[i];
		}
	}
	return nullptr;
}

void UInventoryManagerComponent::AddItem(AItemBase *Item)
{
	InventoryList.Add(Item);
}

void UInventoryManagerComponent::RemoveItemByIndex(const int Index)
{
	InventoryList.RemoveAt(Index);
}

void UInventoryManagerComponent::RemoveItemByName(const FText Value)
{

	for (int i = 0; i < InventoryList.Num(); i++)
	{
		if (InventoryList[i]->GetName().EqualTo(Value))
		{
			RemoveItemByIndex(i);
			return;
		}
	}
}

// Called when the game starts
void UInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UInventoryManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
