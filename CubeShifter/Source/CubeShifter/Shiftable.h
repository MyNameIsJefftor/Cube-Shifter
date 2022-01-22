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

	bool WhiteState = false;

public:	

	// Sets default values for this actor's properties
	AShiftable();
	AShiftable(bool StartState);

	void virtual Shift();
};
