// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePawn.h"
#include "EnhancedInputComponent.h"
#include "PawnPlayerController.h"

void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APawnPlayerController* PlayerController = Cast<APawnPlayerController>(GetController()))
		{
			if (PlayerController->HoverAction)
			{
				EnhancedInput->BindAction(PlayerController->HoverAction.Get(), ETriggerEvent::Triggered, this, &ADronePawn::Hover);
			}
		}
	}
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

void ADronePawn::Hover(const FInputActionValue& Value)
{

}
