// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shiftable.h"
#include "MoveMarker.h"
#include "SlideCube.generated.h"

/**
 * 
 */
UCLASS()
class CUBESHIFTER_API ASlideCube : public AShiftable
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere, Category = Target)
		UMoveMarker* MyTarget;

	FVector Start;

	bool AtStart = true;
	ASlideCube();

	void Shift() override;

protected:
	void BeginPlay() {
		Start = this->GetTransform().GetLocation();
	}
};
