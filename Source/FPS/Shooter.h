// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shooter.generated.h"

class UInputMappingContext;
class UInputAction;
class AGun;
class UHealthComponent;
struct FInputActionValue;

UCLASS()
class FPS_API AShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AGun *Gun;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void OnShoot();

private:
	APlayerController *PlayerController;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent *HealthComponent;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext *DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext *ShooterMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *ShootAction;

	void Move(const FInputActionValue &InputActionValue);
	void Look(const FInputActionValue &InputActionValue);
	void Shoot(const FInputActionValue &InputActionValue);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;
};
