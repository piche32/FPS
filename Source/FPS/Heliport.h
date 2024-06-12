// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Heliport.generated.h"

class UWidgetComponent;
class UDisplayInfoUI;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class FPS_API AHeliport : public AActor,
						  public IInteractInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent *Widget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UDisplayInfoUI> UDisplayInfoUIClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	FText ActionText = FText::FromString(TEXT("Call Helicopter"));

	UPROPERTY(EditAnywhere, Category = "UI")
	FText FailedMessage = FText::FromString(TEXT("기밀 문서를 찾아와야 할 것 같다."));

	bool IsInRange = false;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent *Collision;

public:
	// Sets default values for this actor's properties
	AHeliport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(APlayerController *Controller) override;

	UFUNCTION()
	virtual void CollisionEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	virtual void CollisionExit(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void InitializeCollision();
	void InitializeWidget();
};
