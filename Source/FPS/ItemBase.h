// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "ItemBase.generated.h"

class USphereComponent;
class UPickupTextUI;
class UWidgetComponent;

UCLASS()
class FPS_API AItemBase : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Info")
	FText Name = FText::FromString(TEXT("ItemBase"));

	UPROPERTY(EditAnywhere, Category = "Info")
	FText PickupText = Name;

	UPROPERTY(EditAnywhere, Category = "Info")
	FText ActionText = FText::FromString(TEXT("Use"));

	UPROPERTY(EditAnywhere, Category = "Info")
	UTexture2D *Thumbnail;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPickupTextUI> PickupTextUIClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent *Widget;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float PickupRange = 250.f;

	bool IsInRange = false;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Item")
	UStaticMeshComponent *Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	USphereComponent *Collision;

	UPROPERTY(EditAnywhere, Category = "Info")
	FText Detail = FText::FromString(TEXT("Detail"));

	bool bConsumable = true;

public:
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	FText GetName() const
	{
		return Name;
	}

	UFUNCTION(BlueprintPure)
	FText GetPickupText() const
	{
		return PickupText;
	}

	UFUNCTION(BlueprintPure)
	FText GetActionText() const
	{
		return ActionText;
	}

	UFUNCTION(BlueprintPure)
	UTexture2D *GetThumbnail() const
	{
		return Thumbnail;
	}

	bool IsConsumable()
	{
		return bConsumable;
	}
	UFUNCTION(BlueprintCallable)
	void ReadyToPickup(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION(BlueprintCallable)
	void PreventToPickup(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void Action();
	virtual void Drop(FVector DropLocation);

private:
	void InitializeCollision();
	void InitializeWidget();

	virtual void Pickup(class AShooterPlayerController *Controller);
};

// USTRUCT(Atomic, BlueprintType)
// struct FItemStruct
// {
// 	GENERATED_BODY()

// public:
// 	UPROPERTY()
// 	AItemBase *Item;
// 	UPROPERTY()
// 	UTexture2D *Thumbnail;
// 	UPROPERTY()
// 	FText PickupText;
// 	UPROPERTY()
// 	FText ActionText;
// };