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
	int ret = 0;
	TArray<UStaticMeshComponent*> components;
	GetOwner()->GetComponents<UStaticMeshComponent>(components);
	for (auto component:components)
	{
		const auto rotation = component->GetComponentRotation();
		const auto broken =  FMath::Abs(rotation.Pitch) + FMath::Abs(rotation.Roll) > 90 || component->GetComponentLocation().Z < -250;
		ret += broken?1:0;
	}
	return ret;
	
}
