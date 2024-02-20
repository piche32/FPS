// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dog.generated.h"

class USkeletalMeshComponent;
class UHealthComponent;

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

	UFUNCTION(BlueprintCallable)
	void SetOffIsHit();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	bool IsHit;

private:
	UPROPERTY(VisibleAnywhere)
	UHealthComponent *HealthComponent;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float Damage = 10.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OhterComp, FVector NormalImpulse, const FHitResult &Hit);
};
