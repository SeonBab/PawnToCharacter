// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.h"
#include "DronePawn.generated.h"

/**
 * 
 */
UCLASS()
class PAWNTOCHARACTER_API ADronePawn : public APlayerPawn
{
	GENERATED_BODY()
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
	virtual void Look(const FInputActionValue& Value) override;
	UFUNCTION()
	virtual void Hover(const FInputActionValue& Value);
};
