// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCTV.generated.h"

class USphereComponent;

UCLASS()
class FPS_API ACCTV : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACCTV();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent *Collision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *TopMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *BottomMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float MaxRange = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float Damage = 3.f;
};
