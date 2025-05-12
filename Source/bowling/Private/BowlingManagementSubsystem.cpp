// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlingManagementSubsystem.h"

#include "BowlingComponent.h"
#include "StickStackComponent.h"
#include "Kismet/GameplayStatics.h"

void UBowlingManagementSubsystem::SetBallSize(int Value)
{
	BallSize = Value;
}

int UBowlingManagementSubsystem::GetBallSize() const
{
	return BallSize;
}

void UBowlingManagementSubsystem::SwapForceMode()
{
	if (!ActiveBowlingComponent) return;
	ActiveBowlingComponent->SwapForceMode();
	
}

void UBowlingManagementSubsystem::SwapRotationMode()
{
	if (!ActiveBowlingComponent) return;
	ActiveBowlingComponent->SwapRotationMode();
}

void UBowlingManagementSubsystem::SetRotation(FRotator Rotator)
{
	if (!ActiveBowlingComponent) return;
	ActiveBowlingComponent->SetRotation(Rotator);
}

void UBowlingManagementSubsystem::SetForceScale(float Value)
{
	if (!ActiveBowlingComponent) return;
	ActiveBowlingComponent->SetForceScale(Value);
}

void UBowlingManagementSubsystem::Move(float Value)
{
	if (!ActiveBowlingComponent) return;
	ActiveBowlingComponent->MoveRight(Value,1);
}

void UBowlingManagementSubsystem::Start()
{
	if (!ActiveBowlingComponent) return;
	ActiveBowlingComponent->Start();
	ActiveBowlingComponent->ShowIndicator(false);
	FTimerHandle Time;
	GetWorld()->GetTimerManager().SetTimer(
		Time, FTimerDelegate::CreateUObject(this, &UBowlingManagementSubsystem::ClearFieldAndGetScore), 10, false);
}

void UBowlingManagementSubsystem::ClearFieldAndGetScore()
{
	if (!ActiveBowlingComponent || !ActiveStickStackComponent) return;
	ActiveBowlingComponent->Clear();
	Score.Add(ActiveStickStackComponent->GetScore());
	auto clss = ActiveStickStackComponent->GetOwner()->GetClass();
	ActiveStickStackComponent->GetOwner()->Destroy();
	auto location = ActiveStickStackComponent->GetOwner()->GetActorLocation();
	auto rotation = ActiveStickStackComponent->GetOwner()->GetActorRotation();
	auto actor = GetWorld()->SpawnActor(clss,&location,&rotation);
	ActiveStickStackComponent = actor->FindComponentByClass<UStickStackComponent>();
	OnScoreChanged.Broadcast();
}
