// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        // Get the player controller and very that it is not null
        if (Tank->GetTankPlayerController())
        {
            // Disable input on Tank
            Tank->DisableInput(Tank->GetTankPlayerController());
            Tank->GetTankPlayerController()->bShowMouseCursor = false;
        }
    }
    // Attempt to cast to ATower, will return nullptr/false if cast fails
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
    }

}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));


}