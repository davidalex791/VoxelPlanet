// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VoxelPlanetHUD.generated.h"

UCLASS()
class AVoxelPlanetHUD : public AHUD
{
	GENERATED_BODY()

public:
	AVoxelPlanetHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

