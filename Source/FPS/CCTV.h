// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CCTV.generated.h"

class USphereComponent;
class UHealthComponent;
class USceneComponent;

UCLASS()
class FPS_API ACCTV : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACCTV();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *TopMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent *ViewPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent *HealthComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void RotateCamera(FVector LookAtTarget);

	UFUNCTION(BlueprintCallable)
	void Search();

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent *Collision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *BottomMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float MaxRange = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float Damage = 3.f;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;
};
