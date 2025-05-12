// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlingComponent.h"

#include "BowlingManagementSubsystem.h"

// Sets default values for this component's properties
UBowlingComponent::UBowlingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UBowlingComponent::BeginPlay()
{
	Super::BeginPlay();
	Indicator = GetChildComponent(0);
	InitPos();
	// ...
	
}


// Called every frame
void UBowlingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsRotationMode)
	{
		Indicator->AddWorldRotation(FRotator(0, 10 * DeltaTime * (bRotationUp?1:-1),0));
		if (Indicator->GetRelativeRotation().Yaw >= 45 && bRotationUp) bRotationUp = false;
		if (Indicator->GetRelativeRotation().Yaw <= -45 && !bRotationUp) bRotationUp = true;
	}
	if (bIsForceMode)
	{
		SetForceScale(ForceScale + DeltaTime * (bForceUp?1:-1));
		if (ForceScale >= 1 && bForceUp) bForceUp = false;
		if (ForceScale <= 0 && !bForceUp) bForceUp = true;
		OnForceScaleChanged.Broadcast(ForceScale);
	}
	// ...
}



void UBowlingComponent::MoveRight(float AxisValue, float Delta)
{
	FVector vec = GetRightVector();
	vec.Normalize();
	Location += vec * ControlSensitivity * Delta * AxisValue;
	FVector Max = GetComponentLocation()-GetRightVector() * Distance;
	FVector Min = GetComponentLocation() + GetRightVector() * Distance;
	Location.X = FMath::Clamp(Location.X,FMath::Min(Min.X,Max.X),FMath::Max(Min.X,Max.X));
	Location.Y = FMath::Clamp(Location.Y,FMath::Min(Min.Y,Max.Y),FMath::Max(Min.Y,Max.Y));
	Location.Z = FMath::Clamp(Location.Z,FMath::Min(Min.Z,Max.Z),FMath::Max(Min.Z,Max.Z));
	
	Indicator->SetWorldLocation(Location);
}

void UBowlingComponent::ShowIndicator(bool bShow)
{
	Indicator->SetVisibility(bShow);
}

void UBowlingComponent::SetRotation(FRotator Rotator)
{
    Indicator->SetWorldRotation(Rotator);
}

void UBowlingComponent::SetForceScale(float Value)
{
	ForceScale = Value;
	OnForceScaleChanged.Broadcast(Value);
}

void UBowlingComponent::SwapRotationMode()
{
	bIsRotationMode = !bIsRotationMode;
}

void UBowlingComponent::SwapForceMode()
{
	bIsForceMode = !bIsForceMode;
}

void UBowlingComponent::Clear()
{
	Indicator->SetWorldRotation(FRotator(0,0,0));
	ClearBall();
	InitPos();
}


void UBowlingComponent::Start()
{
	ClearBall();
	FBallBuilder Ball;
	Ball.BallImpulse = ForceScale * 1000 + 500;
	Ball.BallMass = GetWorld()->GetSubsystem<UBowlingManagementSubsystem>()->GetBallSize();
	Ball.BallPosition = Location;
	ActorBall = Ball.Build(GetWorld());
	if (!ActorBall)
	{
		UE_LOG(LogTemp,Warning,TEXT("Ball not spawned"));
		return;
	}
	auto primitive = ActorBall->FindComponentByClass<UPrimitiveComponent>();
	if (IsValid(primitive) && primitive->IsSimulatingPhysics())
	{
		primitive->AddImpulse(Indicator->GetForwardVector() * Ball.BallImpulse, NAME_None, true);
	} 
}

void UBowlingComponent::InitPos()
{
	Location = GetComponentLocation();
	Indicator->SetWorldLocation(Location);
}

void UBowlingComponent::ClearBall()
{
	if (ActorBall)
	{
		ActorBall->Destroy();
		ActorBall = nullptr;
	}
}

inline void UBowlingComponent::SetComponentActive()
{
	GetWorld()->GetSubsystem<UBowlingManagementSubsystem>()->SetActiveBowlingComponent(this);
	
}
