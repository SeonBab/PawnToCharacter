// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "DronePawn.generated.h"

/**
 * 
 */
UCLASS()
class PAWNTOCHARACTER_API ADronePawn : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
	void MoveStart(const FInputActionValue& Value);
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void MoveEnd(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void Roll(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float HoverSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float RollSpeed = 0.5f;
};
