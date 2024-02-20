// Fill out your copyright notice in the Description page of Project Settings.

#include "Dog.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

// Sets default values
ADog::ADog()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetSimulatePhysics(true);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void ADog::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->OnComponentHit.AddDynamic(this, &ADog::OnHit);

	if (HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dog Health"));
	}
}

// Called every frame
void ADog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADog::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ADog::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (HealthComponent)
	{
		HealthComponent->DamageTaken(DamageAmount);
	}

	if (HealthComponent->IsDead())
	{
		DetachFromControllerPendingDestroy();
	}

	else
	{
		IsHit = true;
	}

	return DamageAmount;
}

void ADog::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, FVector NormalImpulse, const FHitResult &Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));

	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetController(), this, DamageTypeClass);
	}
}

void ADog::SetOffIsHit()
{
	IsHit = false;
}