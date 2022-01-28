// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shiftable.h"
#include "Components/BoxComponent.h"
#include "SlipperySlope.generated.h"

/**
 * 
 */
UCLASS()
class CUBESHIFTER_API ASlipperySlope : public AShiftable
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Parent)
		USceneComponent* parent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* posCube;

	UPROPERTY(VisibleDefaultsOnly, Category = SlipCollision)
		UBoxComponent* posBox;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* negCube;

	UPROPERTY(VisibleDefaultsOnly, Category = SlipCollision)
		UBoxComponent* negBox;

	UPROPERTY(EditAnywhere, Category = Slippery)
		bool posSlippery;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	bool Disable(USceneComponent* mesh) override;
	bool Enable(USceneComponent* mesh) override;

protected:

	void BeginPlay() override;

public:
	ASlipperySlope();

	void Shift() override;

	void WorldStateChange(bool worldState) override;
};
