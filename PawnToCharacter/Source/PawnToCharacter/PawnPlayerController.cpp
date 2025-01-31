// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPlayerController.h"
#include "EnhancedInputSubsystems.h"

void APawnPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!IMC.IsNull())
			{
				SubSystem->AddMappingContext(IMC, 0);
			}
		}
	}
}
