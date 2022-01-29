// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerButton.generated.h"

class USphereComponent;

UCLASS()
class CUBESHIFTER_API ATriggerButton : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Parent;

	UPROPERTY(EditAnywhere, Category = "Collider")
	USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* ButtonMesh;
	
public:	
	// Sets default values for this actor's properties
	ATriggerButton();

	UPROPERTY(EditAnywhere, Category = "Interactable Interface")
	TScriptInterface<class IInteractableInterface> Interactable;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
