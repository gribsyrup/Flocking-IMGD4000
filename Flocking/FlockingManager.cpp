// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 50
#define XMIN -1000
#define XMAX 1000
#define ZMIN 30
#define ZMAX 1000
#define YMAX 1000
#define YMIN -1000
#define VLIMIT 3

void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
    UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

    World = world;

    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (World != nullptr) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin(incr * i) * 150.f;
            location.Z = FMath::Cos(incr * i) * 150.f;

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

void UFlockingManager::Flock() {
    FVector v1, v2, v3;
    FVector velocity;
    FVector location;
    //AAgent *agent;

    for (int i = 0; i < AGENT_COUNT; i++) {
        AAgent* agent = Agents[i];
        v1 = rule1(agent);
        v2 = rule2(agent);
        v3 = rule3(agent);

        velocity = agent->getVelocity() + v1 + v3 + v3;
        location = agent->GetActorLocation() + velocity;

        location.X = location.X + 20;
        location.Z = location.Z + 20;
        location.Y = location.Y + 20;

        // Additional tweak. Checking boundary
        location = boundary(location);

        agent->SetActorLocation(location);
        // Limit the speed
        velocity = (velocity / velocity.Size()) * VLIMIT;
        agent->setVelocity(velocity);
        UE_LOG(LogTemp, Warning, TEXT("Agent %d, %f, %f"), agent->getId(), location.X, location.Z);
    }
}

FVector UFlockingManager::rule1(AAgent* agent) {
    FVector v(FVector::ZeroVector);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (agent->getId() != Agents[i]->getId()) {
            v += Agents[i]->GetActorLocation();
        }
    }
    v = v / (AGENT_COUNT - 1);
    return (v - agent->GetActorLocation()) / 25;
    //return (v - agent->GetActorLocation());

}

FVector UFlockingManager::rule2(AAgent* agent) {
    FVector v(FVector::ZeroVector);
    float distance;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (agent->getId() != Agents[i]->getId()) {
            distance = FVector::Distance(Agents[i]->GetActorLocation(), agent->GetActorLocation());
            if (distance < 300) {
                v = v - (Agents[i]->GetActorLocation() - agent->GetActorLocation());
            }
        }
    }
    return v;
}

FVector UFlockingManager::rule3(AAgent* agent) {
    FVector v(FVector::ZeroVector);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (agent->getId() != Agents[i]->getId()) {
            v += Agents[i]->getVelocity();
        }
    }
    v = v / (AGENT_COUNT - 1);
    return (v - agent->getVelocity()) / 4;
}

FVector UFlockingManager::boundary(FVector loc) {
    FVector location = loc;

    if (location.X < XMIN)
        location.X = XMIN - location.X;
    else if (location.X > XMAX)
        location.X = location.X - XMAX;

    if (location.Z < ZMIN)
        location.Z = ZMIN - location.Z;
    else if (location.Z > ZMAX)
        location.Z = location.Z - ZMAX;

    if (location.Y > YMAX)
        location.Y = YMIN;

    return location;
}

