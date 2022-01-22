// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/BillboardComponent.h"
#include "MoveMarker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBESHIFTER_API UMoveMarker : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveMarker();

	UPROPERTY(EditAnywhere)
		UBillboardComponent* MyBill;
};
