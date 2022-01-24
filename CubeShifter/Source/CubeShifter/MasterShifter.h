// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shiftable.h"
#include "MasterShifter.generated.h"

class UStaticMeshComponent;
class UPostProcessComponent;
class UBoxComponent;

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

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetMeshComp() const;

	UFUNCTION(BlueprintCallable)
	UBoxComponent* GetBoxComp() const;

	UFUNCTION(BlueprintCallable)
	UPostProcessComponent* GetPostProcessComp() const;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay();

private:
	UMaterialInterface* Material;

};
