// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CapsuleComp);
	CapsuleComp->SetSimulatePhysics(false);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);
	SkeletalMeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Fall(DeltaTime);

}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::SetIsHover(const bool bNewIsHover)
{
	bIsHover = bNewIsHover;
}

float ABasePawn::GetGravity() const
{
	return Gravity;
}

float ABasePawn::GetCurMoveSpeed() const
{
	return CurMoveSpeed;
}

void ABasePawn::Fall(float DeltaTime)
{
	// 현재 속도로 낙하
	FVector AddVector(0.f, 0.f, -ZVelocity * DeltaTime);
	FHitResult HitResult;
	AddActorWorldOffset(AddVector, true, &HitResult);

	// 낙하 중 충돌이 발생한 경우
	if (HitResult.GetActor())
	{
		// 공중에 떠있지 않음
		bIsAir = false;

		// 이동 속도 복구
		CurMoveSpeed = MaxMoveSpeed;
		// ZVelocity 초기화
		ZVelocity = 0.f;
	}
	else
	{
		// 충돌한 오브젝트가 없고, ZVelocity가 0이 아니라 낙하 중에 공중에 떠있는 경우
		if (!FMath::IsNearlyZero(ZVelocity))
		{
			bIsAir = true;

			// 공중 이동속도 수정
			CurMoveSpeed = MaxMoveSpeed * AirControllSpeed;
		}

		if (!bIsHover)
		{
			// 중력에 의해 낙하하는 속도 증가
			ZVelocity = ZVelocity + Gravity * DeltaTime;
		}
	}
}

