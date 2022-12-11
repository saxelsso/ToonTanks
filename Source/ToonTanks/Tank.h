// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components" )
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components" )
	class UCameraComponent* Camera; 

	void Move(float Value);
	void Turn(float Value);


	UPROPERTY(EditAnywhere, Category = "Movement" )
	float Speed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Movement" )
	float TurnRate = 2.f;

	FVector CurrentVelocity;
	FRotator CurrentRotationVelocity;

	APlayerController* PlayerControllerRef;

};
