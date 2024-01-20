// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	if (MuzzleFlash)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlash, Mesh, TEXT("b_gun_muzzleflash"), FVector(0.f), FRotator(90.0f), EAttachLocation::Type::KeepRelativeOffset, true);
	}

	Shoot();
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::Shoot()
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return;
	AController *OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
		return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector EndPoint = Location + Rotation.Vector() * MaxRange;

	FHitResult HitResult;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndPoint, ECC_GameTraceChannel1);
	if (bSuccess)
	{
		if (HitFlash)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitFlash, HitResult.Location);
		}
	}
}
