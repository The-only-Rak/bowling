#include "BallBuilder.h"

AActor* FBallBuilder::Build(UWorld* World)
{
	auto* clss = LoadClass<APawn>(nullptr
		, TEXT("/Game/Blueprints/BP_Ball.BP_Ball_C"));
	auto ball = World->SpawnActor(clss,&BallPosition);
	if (!ball) return nullptr;
	auto component = ball->FindComponentByClass<UPrimitiveComponent>();
	//component->SetSimulatePhysics(true);
	component->SetMassOverrideInKg(NAME_Name,BallMass);
	return ball;
}
