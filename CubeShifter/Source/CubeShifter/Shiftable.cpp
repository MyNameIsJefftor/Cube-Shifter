// Fill out your copyright notice in the Description page of Project Settings.


#include "Shiftable.h"

// Sets default values
AShiftable::AShiftable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PositiveState = true;
}

AShiftable::AShiftable(bool StartState)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PositiveState = StartState;
}

void AShiftable::BeginPlay()
{
	Super::BeginPlay(); 

	if (!PositiveState) Shift();
}

bool AShiftable::GetPositiveState() const
{
	return PositiveState;
}

void AShiftable::Shift()
{

}

void AShiftable::WorldStateChange(bool posState)
{
}

bool AShiftable::Disable(USceneComponent* Component)
{
	return false;
}

bool AShiftable::Enable(USceneComponent* Component)
{
	return false;
}
