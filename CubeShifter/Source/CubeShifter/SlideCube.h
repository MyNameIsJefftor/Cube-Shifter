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

	UPROPERTY(VisibleAnywhere, Category = Parent)
		USceneComponent* parent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* posCube;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* negCube;

	//UPROPERTY(EditAnywhere, Category = Target)
	//	UMoveMarker* MyTarget;

	FVector Start;

	bool isPositve = true;
	ASlideCube();

	void Shift() override;
	void WorldStateChange(bool worldState) override;

protected:
	void BeginPlay() {
		if (!PositiveState) { Shift(); }
		else { disable(negCube); }
	}
private:
	void disable(UStaticMeshComponent* mesh);
	void enable(UStaticMeshComponent* mesh);

public:
};
