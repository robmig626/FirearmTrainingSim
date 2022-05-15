// Fill out your copyright notice in the Description page of Project Settings.

#define DEBUG_LOG(text) GEngine->AddOnScreenDebugMessage(-1,1,FColor::Cyan, text)

#include "PlayerPawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	PlayerInputComponent->BindAxis("LookUp", this, &APlayerPawn::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerPawn::LookRight);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &APlayerPawn::ToggleSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &APlayerPawn::ToggleSprint);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &APlayerPawn::ToggleAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &APlayerPawn::ToggleAim);

	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &APlayerPawn::Reload);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &APlayerPawn::FireGun);
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

void APlayerPawn::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerPawn::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
	SetActorRotation(FRotator(0.f, GetController()->GetControlRotation().Yaw, 0.f));
}

void APlayerPawn::ToggleSprint()
{
	if (ActiveWalkSpeed > (BaseWalkSpeed + 1.f)){ActiveWalkSpeed = BaseWalkSpeed;}
	else{ActiveWalkSpeed = SprintSpeed;}
}

void APlayerPawn::ToggleAim()
{
	bIsAiming ? bIsAiming = false : bIsAiming = true;
	bIsAiming ? DEBUG_LOG(TEXT("true")) : DEBUG_LOG(TEXT("false"));
	//TODO: implement aiming behaviour
}

void APlayerPawn::Reload()
{
	DEBUG_LOG(TEXT("Reloading"));
	//TODO: implement reloading behaviour
	if ((StoredAmmo > 0) && (LoadedAmmo < GunCapacity))
	{
		if (StoredAmmo > (GunCapacity - LoadedAmmo))
		{
			StoredAmmo -= (GunCapacity - LoadedAmmo);
			LoadedAmmo += (GunCapacity - LoadedAmmo);
		}
		else
		{
			LoadedAmmo += StoredAmmo;
			StoredAmmo = 0;
		}
	}
	DEBUG_LOG(FString::Printf(TEXT("Ammo: %d / %d \nStored Ammo: %d"), LoadedAmmo, GunCapacity, StoredAmmo));
}
void APlayerPawn::FireGun()
{
	if (bIsAiming)
	{
		if (LoadedAmmo > 0)
		{
			DEBUG_LOG(TEXT("Bang!!!"));
			//TODO: implement firing behaviour
			if (GetWorld()->LineTraceSingleByChannel(
				LineOfFireHitResult,
				GetActorLocation(),
				GetActorLocation() + GetControlRotation().Vector() * GunReach,
				ECollisionChannel::ECC_Visibility
			))
			{
				DEBUG_LOG(LineOfFireHitResult.GetActor()->GetName());
			}
			DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetControlRotation().Vector() * GunReach, FColor::Red, true, 3.f);
			LoadedAmmo--;
		}
		else
		{
			DEBUG_LOG(TEXT("Out of Ammo!!!"));
		}
	}
}