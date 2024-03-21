// Fill out your copyright notice in the Description page of Project Settings.

#include "FakeWall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AFakeWall::AFakeWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AFakeWall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFakeWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
