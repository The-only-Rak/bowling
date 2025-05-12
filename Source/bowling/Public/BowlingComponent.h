// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BallBuilder.h"
#include "BowlingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnForceScaleChanged,float,Value);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWLING_API UBowlingComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBowlingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY()
	FVector Location {};
	AActor* ActorBall;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void MoveRight(float AxisValue,float Delta);
	void ShowIndicator(bool bShow);
	void SetRotation(FRotator Rotator);
	void SetForceScale(float Value);
	void SwapRotationMode();
	void SwapForceMode();
	void Clear();
	void Start();
	void SetComponentActive();
	FORCEINLINE FVector GetLocation() const { return Location; }
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	void InitPos();
	void ClearBall();

	UPROPERTY(VisibleInstanceOnly)
	float ForceScale {0};
	UPROPERTY(EditAnywhere)
	float Distance {};
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Indicator {};
	UPROPERTY(EditAnywhere)
	float ControlSensitivity;
	UPROPERTY()
	uint8 bIsRotationMode = false;
	UPROPERTY()
	uint8 bIsForceMode = false;
	UPROPERTY()
	uint8 bForceUp = true;
	UPROPERTY()
	uint8 bRotationUp = true;
	UPROPERTY(BlueprintReadWrite,BlueprintCallable,BlueprintAssignable)
	FOnForceScaleChanged OnForceScaleChanged;

	
};




