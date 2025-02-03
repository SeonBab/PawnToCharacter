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
	// ���� �ӵ��� ����
	FVector AddVector(0.f, 0.f, -ZVelocity * DeltaTime);
	FHitResult HitResult;
	AddActorWorldOffset(AddVector, true, &HitResult);

	// �浹�� �߻��� ���
	if (HitResult.GetActor())
	{
		// ���߿� ������ ����
		bIsAir = false;

		CurMoveSpeed = MaxMoveSpeed;
		// ZVelocity �ʱ�ȭ
		ZVelocity = 0.f;
	}
	else
	{
		// ���߿� ������
		bIsAir = true;

		CurMoveSpeed = MaxMoveSpeed * AirControllSpeed;

		if (!bIsHover)
		{
			// �߷¿� ���� �����ϴ� �ӵ� ����
			ZVelocity = ZVelocity + Gravity * DeltaTime;
		}
	}
}

