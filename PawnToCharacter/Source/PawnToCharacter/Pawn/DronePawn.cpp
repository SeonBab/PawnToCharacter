// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePawn.h"

ADronePawn::ADronePawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADronePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

