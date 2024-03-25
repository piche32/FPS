// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor_Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
// Sets default values
AActor_Item::AActor_Item()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	Mesh->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AActor_Item::BeginPlay()
{
	Super::BeginPlay();

	if (Collision)
	{
		// Colliision->OnComponentBeginOverlap.AddDynamic(this, &A)
	}
}

void AActor_Item::UseItem()
{
}

void AActor_Item::GetItem()
{
}

// Called every frame
void AActor_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
