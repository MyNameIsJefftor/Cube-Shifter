// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CubeShifterHUD.generated.h"

UCLASS()
class ACubeShifterHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACubeShifterHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

