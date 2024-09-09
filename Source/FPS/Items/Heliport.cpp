// Fill out your copyright notice in the Description page of Project Settings.

#include "Heliport.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "../UI/DisplayInfoUI.h"
#include "../Shooter/ShooterPlayerController.h"
#include "../Components/InventoryManagerComponent.h"
#include "ItemBase.h"
#include "../Levels/MainLevelScriptActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHeliport::AHeliport()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Mesh);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AHeliport::BeginPlay()
{
	Super::BeginPlay();
	InitializeCollision();
	InitializeWidget();
}

void AHeliport::Interact(APlayerController *Controller)
{
	if (AShooterPlayerController *ShooterPlayerController = Cast<AShooterPlayerController>(Controller))
	{
		if (AItemBase *Document = ShooterPlayerController->GetInventoryManager()->GetItem(FText::FromString("Confidential Document")))
		{
			ShooterPlayerController->UseItem(Document);
			Widget->SetVisibility(false);

			if (AMainLevelScriptActor *Main = Cast<AMainLevelScriptActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMainLevelScriptActor::StaticClass())))
			{
				Main->PlayEndingSequence();
			}
		}
		else
		{
			ShooterPlayerController->SetInfoText(FailedMessage);
		}
	}
}

void AHeliport::CollisionEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	APawn *OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn || !OtherPawn->IsPlayerControlled())
	{
		return;
	}

	IsInRange = true;

	Widget->SetVisibility(true);
}

void AHeliport::CollisionExit(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	APawn *OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn || !OtherPawn->IsPlayerControlled())
	{
		return;
	}

	IsInRange = false;
	Widget->SetVisibility(false);
}

// Called every frame
void AHeliport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeliport::InitializeCollision()
{
	if (Collision)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AHeliport::CollisionEnter);
		Collision->OnComponentEndOverlap.AddDynamic(this, &AHeliport::CollisionExit);
	}
}

void AHeliport::InitializeWidget()
{
	if (UDisplayInfoUIClass && Widget)
	{
		Widget->SetWidgetSpace(EWidgetSpace::Screen);
		Widget->SetWidgetClass(UDisplayInfoUIClass);
		Widget->InitWidget();
		Widget->SetVisibility(false);
	}

	if (UDisplayInfoUI *DisplayInfoUI = Cast<UDisplayInfoUI>(Widget->GetWidget()))
	{
		DisplayInfoUI->SetAction(ActionText);
	}
}
