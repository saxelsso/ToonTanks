// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CurrentVelocity = FVector::ZeroVector;
	CurrentRotationVelocity = FRotator::ZeroRotator;

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);

}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		
		RotateTurret(HitResult.ImpactPoint);	
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	TankPlayerController = Cast<APlayerController>(GetController());

}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	// X = Value * DeltaTime * Speed;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	//DeltaLocation.X = Value * DeltaTime * 200.f;
	//Smooth out movement for a very basic intertia simulation
	CurrentVelocity.X = FMath::FInterpTo(CurrentVelocity.X, FMath::Clamp(Value, -1.0f, 1.0f) * Speed, DeltaTime, 5.f);	

	AddActorLocalOffset(CurrentVelocity, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	//DeltaRotation.Yaw = Value * DeltaTime * 45.f;
	//Smooth out rotation for a very basic intertia simulation
	CurrentRotationVelocity.Yaw= FMath::FInterpTo(CurrentRotationVelocity.Yaw, FMath::Clamp(Value, -1.0f, 1.0f) * TurnRate, DeltaTime, 5.f);	

	AddActorLocalRotation(CurrentRotationVelocity, true);
}

