// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "LevelDoor.generated.h"

class UBoxComponent;

UCLASS()
class CUBESHIFTER_API ALevelDoor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Parent;

	UPROPERTY(EditAnywhere, Category = "Collider")
	UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* DoorFrameMesh;
	
public:	
	// Sets default values for this actor's properties
	ALevelDoor();

	bool OpenDoor();
	bool CloseDoor();

	// implement Interactable Interface
	virtual bool TurnOn() override;
	virtual bool TurnOff() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
