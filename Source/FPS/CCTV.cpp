// Fill out your copyright notice in the Description page of Project Settings.

#include "CCTV.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Color.h"
#include "NiagaraComponent.h"

// Sets default values
ACCTV::ACCTV()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	BottomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomMesh"));
	BottomMesh->SetupAttachment(Collision);

	TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMesh"));
	TopMesh->SetupAttachment(BottomMesh, TEXT("CameraConnectPoint"));

	Smoke = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Smoke"));
	Smoke->SetupAttachment(TopMesh);

	ViewPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ViewPoint"));
	ViewPoint->SetupAttachment(TopMesh, TEXT("ViewPoint"));

	LaserBeam = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LaserBeam"));
	LaserBeam->SetupAttachment(ViewPoint);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health componentComponent"));
}

// Called when the game starts or when spawned
void ACCTV::BeginPlay()
{
	Super::BeginPlay();

	if (Smoke)
	{
		Smoke->Deactivate();
	}
}

// Called every frame
void ACCTV::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCTV::RotateCamera(FVector LookAtTarget)
{
	// FVector ToTarget = LookAtTarget - TopMesh->GetComponentLocation();
	// FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw + 90.f, 0.f);

	// TopMesh->SetWorldRotation(LookAtRotation);

	FVector ToTarget = LookAtTarget - TopMesh->GetComponentLocation();
	FRotator OriginalRotation = TopMesh->GetComponentRotation();

	// Z - Z'

	FRotator LookAtRotation = FRotator(OriginalRotation.Pitch, ToTarget.Rotation().Yaw + 90.f, ToTarget.Rotation().Roll - 20.f);

	UE_LOG(LogTemp, Warning, TEXT("TopMesh: %s, LookAtTarget: %s, ToTarget: %s"), *TopMesh->GetComponentLocation().ToString(), *LookAtTarget.ToString(), *ToTarget.ToString());

	TopMesh->SetWorldRotation(LookAtRotation);
}

void ACCTV::Rotate(float DeltaTime)
{
	FRotator Original = TopMesh->GetRelativeRotation();
	float TargetYaw = Original.Yaw + RotatingVelocity * DeltaTime;
	FRotator Target(Original.Pitch, TargetYaw, DefaultPitchAngle); // Pitch, Yaw, Roll

	TopMesh->SetRelativeRotation(FMath::RInterpTo(Original, Target, DeltaTime, RotatingInterPSpeed));

	if (-MaxAngle <= TargetYaw && TargetYaw <= MaxAngle)
		return;

	if ((TargetYaw > 0 && RotatingVelocity > 0) || (TargetYaw < 0 && RotatingVelocity < 0))
	{
		RotatingVelocity *= -1.f;
	}
}

float ACCTV::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (HealthComponent)
	{
		HealthComponent->DamageTaken(DamageAmount);
	}

	if (HealthComponent->IsDead())
	{
		OnBreak();
	}

	return DamageAmount;
}

void ACCTV::OnBreak()
{
	GetWorldTimerManager().SetTimer(BrokenMotionTimer, this, &ACCTV::UpdateBrokenMotion, GetWorld()->GetDeltaSeconds(), true);
	if (Smoke)
	{
		Smoke->Activate();
	}
	if (LaserBeam)
	{
		LaserBeam->Deactivate();
	}

	DetachFromControllerPendingDestroy();
}

void ACCTV::UpdateBrokenMotion()
{
	FRotator Original = TopMesh->GetRelativeRotation();
	FRotator Target(Original.Pitch, Original.Yaw, BrokenAngle);

	TopMesh->SetRelativeRotation(FMath::RInterpTo(Original, Target, GetWorld()->GetDeltaSeconds(), 1.f));

	float Result = TopMesh->GetRelativeRotation().Roll;
	if (BrokenAngle - 3.f <= Result && Result <= BrokenAngle + 3.f)
	{
		GetWorldTimerManager().ClearTimer(BrokenMotionTimer);
	}
}
