#pragma once
#include "CoreMinimal.h"
#include "BallBuilder.generated.h"


USTRUCT()
struct FBallBuilder
{
	GENERATED_BODY()
public:
	void SetMass(int Mass)
	{
		BallMass = Mass;
	}

	void SetImpulse(float Impulse)
	{
		BallImpulse = Impulse;
	}
	

	AActor* Build(UWorld* World);
	float BallMass = 6; 
	float BallImpulse; 
	FVector BallPosition; 
	
};
