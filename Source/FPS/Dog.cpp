// Fill out your copyright notice in the Description page of Project Settings.

#include "Dog.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ADog::ADog()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ADog::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetMesh()->OnComponentHit.AddDynamic(this, &ADog::OnHit);
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

float ADog::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Dog Health is %f"), Health);

	return DamageToApply;
}

void ADog::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, FVector NormalImpulse, const FHitResult &Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
}
