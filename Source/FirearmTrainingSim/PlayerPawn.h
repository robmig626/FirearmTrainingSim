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

	//class ACapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed = 600.f;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 1200.f;

	UPROPERTY(EditAnywhere)
	float GunReach = 1000.f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void WalkForward(float AxisValue);
	void WalkRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void ToggleSprint();
	void ToggleAim();
	void Reload();
	void FireGun();

private:
	bool bIsWalkingRight = false;
	bool bIsWalkingForward = false;
	bool bIsAiming = false;

	int LoadedAmmo = 0;
	int StoredAmmo = 12;
	int GunCapacity = 6;

	float ActiveWalkSpeed = BaseWalkSpeed;

	FHitResult LineOfFireHitResult;
};
