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
		UStaticMeshComponent* WhiteCube;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* BlackCube;

	//UPROPERTY(EditAnywhere, Category = Target)
	//	UMoveMarker* MyTarget;

	FVector Start;

	bool IsWhite = true;
	ASlideCube();

	void Shift() override;

protected:
	void BeginPlay() {
		Start = this->GetTransform().GetLocation();
		disable(BlackCube);
	}
private:
	void disable(UStaticMeshComponent* mesh);
	void enable(UStaticMeshComponent* mesh);
};
