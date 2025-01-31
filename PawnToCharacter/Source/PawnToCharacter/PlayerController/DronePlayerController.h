// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "DronePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PAWNTOCHARACTER_API ADronePlayerController : public ABasePlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> RollAction;
};
