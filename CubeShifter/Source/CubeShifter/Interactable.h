// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class IInteractableInterface;

UCLASS()
class CUBESHIFTER_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	UPROPERTY(EditAnywhere, Category = "Interactable Interface")
	TScriptInterface<IInteractableInterface> Interactable;

	UFUNCTION(BlueprintCallable)
	bool TurnOnInteractable();

	UFUNCTION(BlueprintCallable)
	bool TurnOffInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	IInteractableInterface* GetInteractable() const;

};
