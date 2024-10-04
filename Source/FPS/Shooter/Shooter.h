// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shooter.generated.h"

class UInputMappingContext;
class UInputAction;
class AGun;
class UHealthComponent;
class USceneComponent;
class AShooterPlayerController;
struct FInputActionValue;

UCLASS()
class FPS_API AShooter : public ACharacter
{
	GENERATED_BODY()

private:
	AShooterPlayerController *PlayerController;

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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AGun *Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	USceneComponent *DropPosition;

public:
	AShooter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	float GetHPPercent() const;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void OnShoot();

	FVector GetDropPosition();

	UFUNCTION(BlueprintCallable)
	UHealthComponent *GetHealthComponent()
	{
		return HealthComponent;
	}

private:
	void Move(const FInputActionValue &InputActionValue);
	void Look(const FInputActionValue &InputActionValue);
	void Shoot(const FInputActionValue &InputActionValue);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;
	void Die();
};
