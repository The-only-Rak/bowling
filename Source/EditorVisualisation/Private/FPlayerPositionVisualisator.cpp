#include "FPlayerPositionVisualisator.h"
#include "BowlingComponent.h"


void FPlayerPositionComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
	FComponentVisualizer::DrawVisualization(Component, View, PDI);
	const UBowlingComponent* bowling = Cast<UBowlingComponent>(Component);
	if (bowling)
	{
		PDI->DrawPoint(bowling->Distance * bowling->GetRightVector() + bowling->GetComponentLocation(),FColor::Red,10.0f,SDPG_Foreground);
		PDI->DrawPoint(bowling->Distance * -bowling->GetRightVector() + bowling->GetComponentLocation(),FColor::Red,10.0f,SDPG_Foreground);
		PDI->DrawLine(bowling->Distance * bowling->GetRightVector() + bowling->GetComponentLocation(),
			bowling->Distance * -bowling->GetRightVector() + bowling->GetComponentLocation(),FColor::Blue,5.0f,SDPG_World);
	}
}
