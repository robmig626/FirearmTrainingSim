// Fill out your copyright notice in the Description page of Project Settings.

#define DEBUG_LOG(text) GEngine->AddOnScreenDebugMessage(-1,1,FColor::Cyan, text)

#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("WalkForward", this, &APlayerPawn::WalkForward);
	PlayerInputComponent->BindAxis("WalkRight", this, &APlayerPawn::WalkRight);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &APlayerPawn::ToggleSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &APlayerPawn::ToggleSprint);
}

void APlayerPawn::WalkForward(float AxisValue)
{
	if (abs(AxisValue) > 0.001)
	{
		bIsWalkingRight ? AddActorWorldOffset(GetActorForwardVector() * ActiveWalkSpeed / sqrt(2) * AxisValue * GetWorld()->GetDeltaSeconds()) : AddActorWorldOffset(GetActorForwardVector() * ActiveWalkSpeed * AxisValue * GetWorld()->GetDeltaSeconds());
		bIsWalkingForward = true;
		
	}
	else
	{
		bIsWalkingForward = false;
	}
}

void APlayerPawn::WalkRight(float AxisValue)
{
	if (abs(AxisValue) > 0.001)
	{
		bIsWalkingForward ? AddActorWorldOffset(GetActorRightVector() * ActiveWalkSpeed / sqrt(2) * AxisValue * GetWorld()->GetDeltaSeconds()) : AddActorWorldOffset(GetActorRightVector() * ActiveWalkSpeed * AxisValue * GetWorld()->GetDeltaSeconds());
		bIsWalkingRight = true;

	}
	else
	{
		bIsWalkingRight = false;
	}
}

void APlayerPawn::ToggleSprint()
{
	if (ActiveWalkSpeed > (BaseWalkSpeed + 1.f)){ActiveWalkSpeed = BaseWalkSpeed;}
	else{ActiveWalkSpeed = SprintSpeed;}
}
