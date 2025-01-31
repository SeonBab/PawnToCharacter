// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePawn.h"
#include "EnhancedInputComponent.h"

void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

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
