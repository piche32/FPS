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

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeCollision();
	InitializeWidget();

	AShooterPlayerController *PlayerController = Cast<AShooterPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		PlayerController->PickupDelegate.BindUObject(this, &AItemBase::Pickup);
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
}

void AItemBase::Action()
{
	UE_LOG(LogTemp, Warning, TEXT("ItemBase->Action"));
}

void AItemBase::ReadyToPickup(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	Widget->SetVisibility(true);
	IsInRange = true;
}

void AItemBase::PreventToPickup(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	Widget->SetVisibility(false);
	IsInRange = false;
}
