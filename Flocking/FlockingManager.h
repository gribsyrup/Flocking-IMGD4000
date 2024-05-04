// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Agent.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:
    GENERATED_BODY()

    void Init(UWorld* world, UStaticMeshComponent* mesh);
    void Flock();
    FVector rule1(AAgent*);
    FVector rule2(AAgent*);
    FVector rule3(AAgent*);
    FVector boundary(FVector);

private:
    UWorld* World;
    bool initialized;
    TArray<class AAgent*> Agents;
};