// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PickupTextUI.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "ShooterPlayerController.h"
#include "Shooter.h"

// Sets default values
AItemBase::AItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Mesh);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeCollision();
	InitializeWidget();
	InitializeMesh();

	AShooterPlayerController *PlayerController = Cast<AShooterPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		PlayerController->PickupDelegate.AddUObject(this, &AItemBase::Pickup);
	}
}

void AItemBase::InitializeCollision()
{
	if (Collision)
	{
		Collision->SetSphereRadius(PickupRange);
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::ReadyToPickup);
		Collision->OnComponentEndOverlap.AddDynamic(this, &AItemBase::PreventToPickup);
	}
}

void AItemBase::InitializeWidget()
{

	if (PickupTextUIClass && Widget)
	{
		Widget->SetWidgetSpace(EWidgetSpace::Screen);
		Widget->SetWidgetClass(PickupTextUIClass);
		Widget->InitWidget();
		Widget->SetVisibility(false);
	}

	UPickupTextUI *WidgetObject = Cast<UPickupTextUI>(Widget->GetWidget());
	if (WidgetObject)
	{
		WidgetObject->SetText(PickupText);
	}
}

void AItemBase::InitializeMesh()
{
	Mesh->SetSimulatePhysics(true);
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::Pickup(AShooterPlayerController *Controller)
{
	if (!IsInRange || !GetActorEnableCollision())
		return;

	Controller->PickupItem(this);

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	Mesh->SetSimulatePhysics(false);
}

void AItemBase::ReadyToPickup(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	AShooter *Shooter = Cast<AShooter>(OtherActor);
	if (Shooter && Cast<AShooterPlayerController>(Shooter->GetController()))
	{

		Widget->SetVisibility(true);
		IsInRange = true;
	}
}

void AItemBase::PreventToPickup(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	AShooter *Shooter = Cast<AShooter>(OtherActor);
	if (Shooter && Cast<AShooterPlayerController>(Shooter->GetController()))
	{
		Widget->SetVisibility(false);
		IsInRange = false;
	}
}

void AItemBase::Action()
{
	UE_LOG(LogTemp, Warning, TEXT("ItemBase->Action"));
}

void AItemBase::Drop(FVector DropLocation)
{
	bool bSuccess = SetActorLocation(DropLocation, false, nullptr, ETeleportType::TeleportPhysics);
	if (bSuccess)
		UE_LOG(LogTemp, Warning, TEXT("Success"));
	if (!bSuccess)
		UE_LOG(LogTemp, Warning, TEXT("Fail"));
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	Mesh->SetSimulatePhysics(true);
}
