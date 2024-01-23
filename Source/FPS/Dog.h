// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dog.generated.h"

class USkeletalMeshComponent;

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Info")
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Demage = 10.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, FVector NormalImpulse, const FHitResult &Hit);
};
