// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveDoor.generated.h"

class UBoxComponent;

UCLASS()
class FPS_API AInteractiveDoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractiveDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent *Collision;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *DoorFrame;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Door;

	FTimerHandle OpenTimer;
	FTimerHandle CloseTimer;

	bool RotatingForward;

	UPROPERTY(EditAnywhere, Category = "Rotating")
	float TargetAngle = 90.f;

	UPROPERTY(EditAnywhere, Category = "Rotating")
	float RotatingSpeed = 1.f;

	UFUNCTION()
	void OnOpen(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnClose(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	void Opening();
	void Closing();
};
