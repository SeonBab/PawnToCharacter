// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (IMC)
			{
				SubSystem->AddMappingContext(IMC, 0);
			}
		}
	}
}
