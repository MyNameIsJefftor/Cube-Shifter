// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "InteractableInterface.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

IInteractableInterface* AInteractable::GetInteractable() const
{
	IInteractableInterface* i = nullptr;
	if (Interactable && Interactable.GetObject()->Implements<UInteractableInterface>())
	{
		i = Cast<IInteractableInterface>(Interactable.GetObject());
		if (i) return i;
	}

	return i;
}

bool AInteractable::TurnOnInteractable()
{
	return GetInteractable()->TurnOn();
}

bool AInteractable::TurnOffInteractable()
{
	return GetInteractable()->TurnOff();
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

