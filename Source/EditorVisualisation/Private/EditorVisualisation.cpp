#include "EditorVisualisation.h"

#include "FPlayerPositionVisualisator.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#define LOCTEXT_NAMESPACE "FEditorVisualisationModule"
#include "BowlingComponent.h"
#include "FPlayerPositionVisualisator.h"
void FEditorVisualisationModule::StartupModule()
{
    if (GUnrealEd != nullptr)
    {
        TSharedPtr<FPlayerPositionComponentVisualizer> Visualizer = MakeShareable(new FPlayerPositionComponentVisualizer);
        GUnrealEd->RegisterComponentVisualizer(UBowlingComponent::StaticClass()->GetFName(),Visualizer);
        Visualizer->OnRegister();
    }
}

void FEditorVisualisationModule::ShutdownModule()
{
    if (GUnrealEd != nullptr)
    {
        GUnrealEd->UnregisterComponentVisualizer(UBowlingComponent::StaticClass()->GetFName());
    }
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FEditorVisualisationModule, EditorVisualisation)