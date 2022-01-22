// Fill out your copyright notice in the Description page of Project Settings.


#include "Shiftable.h"

// Sets default values
AShiftable::AShiftable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WhiteState = true;
}

AShiftable::AShiftable(bool StartState)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WhiteState = StartState;
}

void AShiftable::Shift()
{
	return;
}
