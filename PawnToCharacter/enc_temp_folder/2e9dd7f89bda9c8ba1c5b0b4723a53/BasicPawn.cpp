// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPawn.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BasicPlayerController.h"

ABasicPawn::ABasicPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABasicPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ABasicPlayerController* PlayerController = Cast<ABasicPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction.Get(), ETriggerEvent::Triggered, this, &ABasicPawn::Move);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction.Get(), ETriggerEvent::Triggered, this, &ABasicPawn::Look);
			}
		}
	}

}

void ABasicPawn::Move(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	FVector2D MoveInput = Value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MoveInput.SizeSquared()))
	{
		MoveInput.Normalize();

		FVector MoveDirection(MoveInput, 0);

		float DeltaTime = GetWorld()->GetDeltaSeconds();

		AddActorLocalOffset(MoveDirection * Speed * DeltaTime);
	}
}

void ABasicPawn::Look(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	FVector2D LookInput = Value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(LookInput.X))
	{
		AddActorLocalRotation(FRotator(0, LookInput.X, 0), false);
	}
	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		SpringArmComp->AddLocalRotation(FRotator(LookInput.Y, 0, 0), false);
	}
}

