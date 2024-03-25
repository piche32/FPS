// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Item.generated.h"

class USphereComponent;

UCLASS()
class FPS_API AActor_Item : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActor_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent *Collision;

	virtual void UseItem();
	virtual void GetItem();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
