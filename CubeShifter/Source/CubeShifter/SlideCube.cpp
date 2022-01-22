// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideCube.h"

ASlideCube::ASlideCube()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	MyTarget = CreateDefaultSubobject<UMoveMarker>(TEXT("Target"));
}

void ASlideCube::Shift()
{
	AtStart = !AtStart;
	switch (AtStart) {
	case true:
		Body->SetWorldLocation(MyTarget->GetComponentLocation());
		break;
	case false:
		Body->SetWorldLocation(Start);
		break;
	}
	return;
}
