// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dog.generated.h"

class UHealthComponent;
class USphereComponent;

UCLASS()
class FPS_API ADog : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool IsHit;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool HasAttacked = false;

	UFUNCTION(BlueprintCallable)
	void SetOffIsHit();

	UFUNCTION(BlueprintCallable)
	void FinishAttacked();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void StartAttacked();

	void UpdateWalkSpeed(float Speed);

private:
	UPROPERTY(VisibleAnywhere)
	UHealthComponent *HealthComponent;

	UPROPERTY(VisibleAnywhere)
	USphereComponent *MouseCollision;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float ChaseSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float PatrolSpeed = 120.f;

	UFUNCTION()
	void OnAttack(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
