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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	UBoxComponent* BoxTrigger;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Shift() override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UMaterialInstanceDynamic* DynamicPPMat;
	UMaterialInstanceDynamic* DynamicMat;

	void ShiftPostProcessMaterial(const FLinearColor& Black, const FLinearColor& White);

	void ShiftCoreMaterial(const FLinearColor& Black, const FLinearColor& White);

};
