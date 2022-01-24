// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shiftable.h"
#include "MasterShifter.generated.h"

class UStaticMeshComponent;
class UPostProcessComponent;
class UBoxComponent;
class URotatingMovementComponent;

UCLASS()
class CUBESHIFTER_API AMasterShifter : public AShiftable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Collider")
	UBoxComponent* CollisionComp;

public: 
	AMasterShifter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Post Process")
	UPostProcessComponent* PostProcessComp;

	UPROPERTY(EditAnywhere, Category = "Rotating Movement")
	URotatingMovementComponent* RotatingMovementComp;

	//UFUNCTION()
	//void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void Shift() override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	//UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicPPMat;
	UMaterialInstanceDynamic* DynamicMat;

};
