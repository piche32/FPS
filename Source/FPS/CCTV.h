// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CCTV.generated.h"

class USphereComponent;
class UHealthComponent;
class USceneComponent;
class UNiagaraComponent;

UCLASS()
class FPS_API ACCTV : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACCTV();

	FVector GetViewPointLocation() const;
	FVector GetViewPointForward() const;

	void UpdateLaserEnd(FVector Target);

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

	// UFUNCTION(BlueprintCallable)
	// void RotateCamera(FVector LookAtTarget);

	void RotateToTarget(FVector LookAtTarget);

	void Rotate(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent *Collision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *BottomMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	float MaxRange = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	float Damage = 3.f;

	UPROPERTY(VisibleAnywhere, Category = "Attacking")
	UNiagaraComponent *LaserBeam;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const &DamageEvent,
		AController *EventInstigator,
		AActor *DamageCauser) override;

	UPROPERTY(VisibleAnywhere, Category = "Breaking")
	UNiagaraComponent *Smoke;

	FTimerHandle BrokenMotionTimer;
	UPROPERTY(EditDefaultsOnly, Category = "Breaking")
	float BrokenAngle = -90.f;

	void OnBreak();

	void UpdateBrokenMotion();

	UPROPERTY(EditAnywhere, Category = "Rotating")
	float DefaultPitchAngle = -20.f;

	UPROPERTY(EditAnywhere, Category = "Rotating")
	float RotatingVelocity = 50.f;

	UPROPERTY(EditAnywhere, Category = "Rotating")
	float MaxAngle = 45.f;

	UPROPERTY(EditAnywhere, Category = "Rotating")
	float RotatingInterPSpeed = 1.f;

};
