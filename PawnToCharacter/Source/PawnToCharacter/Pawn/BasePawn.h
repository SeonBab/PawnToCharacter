// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class PAWNTOCHARACTER_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void SetIsHover(const bool bNewIsHover);

	float GetGravity() const;

private:
	void Fall(const float DeltaTime);

protected:
	// Ãæµ¹ ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCapsuleComponent> CapsuleComp;

	// ½ºÄÌ·¹Å» ¸Þ½Ã ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;

	// Ä«¸Þ¶ó ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float Speed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float AirControllSpeed = 0.5f;

	bool bIsHover = false;
	bool bIsAir = false;

	float Gravity = 980.f;
	float ZVelocity = 0.f;
};
