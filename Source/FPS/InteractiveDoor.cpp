// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractiveDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInteractiveDoor::AInteractiveDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	SetRootComponent(DoorFrame);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame, TEXT("DoorPoint"));

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(DoorFrame);
}

// Called when the game starts or when spawned
void AInteractiveDoor::BeginPlay()
{
	Super::BeginPlay();

	if (Collision)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveDoor::OnOpen);
		Collision->OnComponentEndOverlap.AddDynamic(this, &AInteractiveDoor::OnClose);
	}
}

// Called every frame
void AInteractiveDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractiveDoor::OnOpen(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	APawn *OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn || !OtherPawn->IsPlayerControlled())
	{
		return;
	}

	FVector Direction = Door->GetComponentLocation() - OtherPawn->GetActorLocation();
	RotatingForward = UKismetMathLibrary::Vector_HeadingAngle(Direction) < 0;
	TargetAngle = RotatingForward ? abs(TargetAngle) : -abs(TargetAngle);

	if (CloseTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(CloseTimer);
	}
	GetWorldTimerManager().SetTimer(
		OpenTimer,
		this,
		&AInteractiveDoor::Opening,
		GetWorld()->GetDeltaSeconds(),
		true);
}

void AInteractiveDoor::OnClose(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	APawn *OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn || !OtherPawn->IsPlayerControlled())
	{
		return;
	}

	if (OpenTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(OpenTimer);
	}

	GetWorldTimerManager().SetTimer(
		CloseTimer,
		this,
		&AInteractiveDoor::Closing,
		GetWorld()->GetDeltaSeconds(),
		true);
}

void AInteractiveDoor::Opening()
{
	FRotator Target(0.f, TargetAngle, 0.f);
	Door->SetRelativeRotation(
		FMath::RInterpTo(
			Door->GetRelativeRotation(),
			Target,
			GetWorld()->GetDeltaSeconds(),
			RotatingSpeed));

	if (abs(Target.Yaw - Door->GetRelativeRotation().Yaw) < 1)
	{
		GetWorldTimerManager().ClearTimer(OpenTimer);
	}
}

void AInteractiveDoor::Closing()
{
	Door->SetRelativeRotation(
		FMath::RInterpTo(
			Door->GetRelativeRotation(),
			FRotator(0.f, 0.f, 0.f),
			GetWorld()->GetDeltaSeconds(),
			RotatingSpeed));

	if (abs(Door->GetRelativeRotation().Yaw) < 1)
	{
		GetWorldTimerManager().ClearTimer(CloseTimer);
	}
}
