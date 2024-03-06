// Fill out your copyright notice in the Description page of Project Settings.

#include "Dog.h"
// #include "Components/SkeletalMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADog::ADog()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// GetMesh()->SetSimulatePhysics(true);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void ADog::BeginPlay()
{
	Super::BeginPlay();

	TArray<USphereComponent *> Comps;
	GetComponents(Comps);

	for (USphereComponent *Comp : Comps)
	{
		MouseCollision = Comp;
		break;
	}

	if (MouseCollision)
	{
		MouseCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RigTongue1"));
		MouseCollision->OnComponentBeginOverlap.AddDynamic(this, &ADog::OnAttack);
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

void ADog::OnAttack(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetController(), this, DamageTypeClass);
	}
}

void ADog::StartAttacked()
{
	HasAttacked = true;
}

void ADog::UpdateWalkSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void ADog::FinishAttacked()
{
	HasAttacked = false;
}

void ADog::SetOffIsHit()
{
	IsHit = false;
}