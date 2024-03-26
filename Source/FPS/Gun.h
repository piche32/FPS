// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UNiagaraSystem;

UCLASS()
class FPS_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *Mesh;

	UPROPERTY(EditAnywhere, Category = "Firing")
	UNiagaraSystem *MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere, Category = "Firing")
	UNiagaraSystem *HitFlash;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float BulletRadius = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float BulletStrength = 1000.f;

	
	void Shoot();
};
