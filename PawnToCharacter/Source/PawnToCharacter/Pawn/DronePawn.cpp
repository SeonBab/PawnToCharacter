// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePawn.h"
#include "EnhancedInputComponent.h"
#include "DronePlayerController.h"

void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ADronePlayerController* PlayerController = Cast<ADronePlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction.Get(), ETriggerEvent::Started, this, &ADronePawn::MoveStart);

				EnhancedInput->BindAction(PlayerController->MoveAction.Get(), ETriggerEvent::Triggered, this, &ADronePawn::Move);

				EnhancedInput->BindAction(PlayerController->MoveAction.Get(), ETriggerEvent::Completed, this, &ADronePawn::MoveEnd);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction.Get(), ETriggerEvent::Triggered, this, &ADronePawn::Look);
			}

			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(PlayerController->RollAction.Get(), ETriggerEvent::Triggered, this, &ADronePawn::Roll);
			}
		}
	}
}

void ADronePawn::MoveStart(const FInputActionValue& Value)
{
	FVector MoveInput = Value.Get<FVector>();

	SetIsHover(true);
}

void ADronePawn::Move(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	FVector MoveInput = Value.Get<FVector>();

	if (!FMath::IsNearlyZero(MoveInput.SizeSquared()))
	{
		MoveInput.Normalize();

		float DeltaTime = GetWorld()->GetDeltaSeconds();
		MoveInput.X *= CurMoveSpeed * DeltaTime;
		MoveInput.Y *= CurMoveSpeed * DeltaTime;
		MoveInput.Z *= (GetGravity() + HoverSpeed) * DeltaTime;

		AddActorLocalOffset(MoveInput, true);
	}
}

void ADronePawn::MoveEnd(const FInputActionValue& Value)
{
	SetIsHover(false);
}

void ADronePawn::Look(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	FVector2D LookInput = Value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(LookInput.SizeSquared()))
	{
		AddActorLocalRotation(FRotator(LookInput.Y, LookInput.X, 0), false);
	}
}

void ADronePawn::Roll(const FInputActionValue& Value)
{
	float RollInput = Value.Get<float>();
	if (!FMath::IsNearlyZero(RollInput))
	{
		AddActorLocalRotation(FRotator(0, 0, RollInput * RollSpeed), false);
	}
}
