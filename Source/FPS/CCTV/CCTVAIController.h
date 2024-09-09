// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CCTVAIController.generated.h"

UCLASS()
class FPS_API ACCTVAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn *InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree *AIBehavior;

	class ACCTV *CCTV;

	UPROPERTY(EditAnywhere, Category = "Checking Player Location")
	float SightRadius = 700.f;

	UPROPERTY(EditAnywhere, Category = "Checking Player Location")
	float TraceSphereRadius = 20.f;

	UPROPERTY(EditAnywhere, Category = "Checking Player Location")
	float SearchPlayerTime = 1.f;

	FTimerHandle SearchPlayerTimer;

	void CheckPlayerLocation();
	void UpdateLaserEnd();
	void SetSearchPlayerTimer();
	void ClearPlayerLocationAndCanAttack();

};
