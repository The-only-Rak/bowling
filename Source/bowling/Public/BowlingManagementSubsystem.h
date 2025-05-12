// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BowlingManagementSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreDelegate);

class UBowlingComponent;
class UStickStackComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class BOWLING_API UBowlingManagementSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY(Getter,Setter)
	int32 BallSize{};
	UPROPERTY()
	UBowlingComponent* ActiveBowlingComponent;
	UStickStackComponent*  ActiveStickStackComponent;
	
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<int> Score;
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetActiveBowlingComponent(UBowlingComponent* component)
	{
		ActiveBowlingComponent = component;
	}

	FORCEINLINE void SetActiveStickStackComponent(UStickStackComponent* component)
	{
		ActiveStickStackComponent = component;
	}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBowlingComponent* GetActiveBowlingComponent()
	{
		return ActiveBowlingComponent;
	}

	UFUNCTION(BlueprintCallable)
	void SetBallSize(int32 Value);
	
	UFUNCTION(BlueprintCallable)
	int32 GetBallSize() const;
	
	UFUNCTION(BlueprintCallable)
	void SwapForceMode();
	
	UFUNCTION(BlueprintCallable)
	void SwapRotationMode();
	
	UFUNCTION(BlueprintCallable)
	void SetRotation(FRotator Rotator);
	
	UFUNCTION(BlueprintCallable)
	void SetForceScale(float Value);

	UFUNCTION(BlueprintCallable)
	void Move(float Value);

	UFUNCTION(BlueprintCallable)
	void Start();

	UFUNCTION(BlueprintCallable)
	void ClearFieldAndGetScore();

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FScoreDelegate OnScoreChanged;
	
};
