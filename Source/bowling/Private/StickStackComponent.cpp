// Fill out your copyright notice in the Description page of Project Settings.


#include "StickStackComponent.h"

#include "BowlingManagementSubsystem.h"

// Sets default values

void UStickStackComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UBowlingManagementSubsystem>()->SetActiveStickStackComponent(this);
}

int UStickStackComponent::GetScore()
{
	int Ret = 0;
	TArray<UStaticMeshComponent*> components;
	GetOwner()->GetComponents<UStaticMeshComponent>(components);
	for (auto component:components)
	{
		const auto Rotation = component->GetComponentRotation();
		const auto Broken =  FMath::Abs(Rotation.Pitch) + FMath::Abs(Rotation.Roll) > 90 || component->GetComponentLocation().Z < -250;
		Ret += Broken?1:0;
	}
	return Ret;
	
}
