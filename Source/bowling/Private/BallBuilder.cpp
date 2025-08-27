#include "BallBuilder.h"

AActor* FBallBuilder::Build(UWorld* World)
{
	auto* Clss = LoadClass<APawn>(nullptr
		, TEXT("/Game/Blueprints/BP_Ball.BP_Ball_C"));
	auto Ball = World->SpawnActor(Clss,&BallPosition);
	if (!Ball) return nullptr;
	auto component = Ball->FindComponentByClass<UPrimitiveComponent>();
	//component->SetSimulatePhysics(true);
	component->SetMassOverrideInKg(NAME_Name,BallMass);
	return Ball;
}
