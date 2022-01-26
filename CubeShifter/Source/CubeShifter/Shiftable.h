// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shiftable.generated.h"

UCLASS()
class CUBESHIFTER_API AShiftable : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category=PosNeg)
	bool PositiveState;

public:	
	// Sets default values for this actor's properties
	AShiftable();
	AShiftable(bool StartState);
 
	void BeginPlay() override;

	bool GetPositiveState() const;

	void virtual Shift();

	void virtual WorldStateChange(bool posState);

	virtual bool Disable(USceneComponent* Component);
	virtual bool Enable(USceneComponent* Component);
};
