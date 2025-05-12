// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StickStackComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWLING_API UStickStackComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	UFUNCTION()
	int GetScore();


};
