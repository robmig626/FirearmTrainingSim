// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class FIREARMTRAININGSIM_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void WalkForward(float AxisValue);
	void WalkRight(float AxisValue);
	void ToggleSprint();

private:

	bool bIsWalkingRight = false;
	bool bIsWalkingForward = false;

	float BaseWalkSpeed = 600.f;
	float SprintSpeed = 1200.f;
	float ActiveWalkSpeed = BaseWalkSpeed;
};
