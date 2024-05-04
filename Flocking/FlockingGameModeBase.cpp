// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingGameModeBase.h"

AFlockingGameModeBase::AFlockingGameModeBase() {
    AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>("AgentMesh");
    PrimaryActorTick.bCanEverTick = true;
}

void AFlockingGameModeBase::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BEGINPLAY()"));
    Manager = NewObject<UFlockingManager>();
    Manager->Init(GetWorld(), AgentMesh);
}

void AFlockingGameModeBase::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    Manager->Flock();
};
// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingGameModeBase.h"

