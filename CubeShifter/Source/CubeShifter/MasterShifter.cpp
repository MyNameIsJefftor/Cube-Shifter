// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterShifter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/BoxComponent.h"
//#include "Kismet/GameplayStatics.h"

AMasterShifter::AMasterShifter()
{
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	CollisionComp->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMasterShifter::OnCompHit);
	CollisionComp->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	MeshComp->SetupAttachment(CollisionComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Process Comp"));
	PostProcessComp->SetupAttachment(CollisionComp);
}

UStaticMeshComponent* AMasterShifter::GetMeshComp() const
{
	return this->MeshComp;
}

UBoxComponent* AMasterShifter::GetBoxComp() const
{
	return CollisionComp;
}

UPostProcessComponent* AMasterShifter::GetPostProcessComp() const
{
	return this->PostProcessComp;
}

void AMasterShifter::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		// Get post process material
		Material = Cast<UMaterialInterface>(PostProcessComp->Settings.WeightedBlendables.Array[0].Object);
		if (Material)
		{
			// Make new Dynamic Material instance for Post Process material
			UMaterialInstanceDynamic* dynMat = UMaterialInstanceDynamic::Create(Material, this);

			FWeightedBlendable newWeightedBlendable;
			newWeightedBlendable.Object = dynMat;
			newWeightedBlendable.Weight = 1;

			PostProcessComp->Settings.WeightedBlendables.Array.Add(newWeightedBlendable);

			FLinearColor faceColor;
			dynMat->GetVectorParameterValue(TEXT("Face Color"), faceColor);
			FLinearColor lineColor;
			dynMat->GetVectorParameterValue(TEXT("Line Color"), lineColor);

			const FLinearColor White(0.875f, 0.875f, 0.875f, 1.0f);
			const FLinearColor Black(0.04f, 0.04f, 0.04f, 1.0f);

			// if face is white and line is black
			if (faceColor.R > 0.5f && lineColor.R < 0.5f)
			{
				// Change face to Black
				dynMat->SetVectorParameterValue(TEXT("Face Color"), Black);
				// Change Line to White
				dynMat->SetVectorParameterValue(TEXT("Line Color"), White);

				PositiveState = false;
			}
			else
			{
				// Change face to White
				dynMat->SetVectorParameterValue(TEXT("Face Color"), White);
				// Change Line to Black
				dynMat->SetVectorParameterValue(TEXT("Line Color"), Black);

				PositiveState = true;
			}
		}

		// Get Material for Orb in Mesh
		Material = MeshComp->GetMaterial(1);
		if (Material)
		{
			// Make new Dynamic Material instance for Mesh material
			UMaterialInstanceDynamic* dynMat = UMaterialInstanceDynamic::Create(Material, this);

			FLinearColor faceColor;
			dynMat->GetVectorParameterValue(TEXT("Face Color"), faceColor);
			//FLinearColor lineColor;
			//dynMat->GetVectorParameterValue(TEXT("Line Color"), lineColor);

			const FLinearColor White(0.875f, 0.875f, 0.875f, 1.0f);
			const FLinearColor Black(0.04f, 0.04f, 0.04f, 1.0f);

			// if face is white
			if (faceColor.R > 0.5f/* && lineColor.R < 0.5f*/)
			{
				// Change face to Black
				dynMat->SetVectorParameterValue(TEXT("DiffuseColor"), Black);
				// Change Line to White
				//dynMat->SetVectorParameterValue(TEXT("Line Color"), White);

				PositiveState = true;
			}
			else
			{
				// Change face to White
				dynMat->SetVectorParameterValue(TEXT("DiffuseColor"), White);
				// Change Line to Black
				//dynMat->SetVectorParameterValue(TEXT("Line Color"), Black);

				PositiveState = false;
			}
		}

	}
}

void AMasterShifter::BeginPlay()
{
	// if level starts in Negative State
	if (!PositiveState)
	{
		// Get post process material
		Material = Cast<UMaterialInterface>(PostProcessComp->Settings.WeightedBlendables.Array[0].Object);
		// Change post process to be black instead of white
		if (Material)
		{
			// Make new Dynamic Material instance for Post Process material
			UMaterialInstanceDynamic* dynMat = UMaterialInstanceDynamic::Create(Material, this);

			FWeightedBlendable newWeightedBlendable;
			newWeightedBlendable.Object = dynMat;
			newWeightedBlendable.Weight = 1;

			PostProcessComp->Settings.WeightedBlendables.Array.Add(newWeightedBlendable);

			FLinearColor faceColor;
			dynMat->GetVectorParameterValue(TEXT("Face Color"), faceColor);
			FLinearColor lineColor;
			dynMat->GetVectorParameterValue(TEXT("Line Color"), lineColor);

			// if face is white and line is black
			if (faceColor.R > 0.5f && lineColor.R < 0.5f)
			{
				// Change face to Black
				dynMat->SetVectorParameterValue(TEXT("Face Color"), FLinearColor(0.04f, 0.04f, 0.04f, 1.0f));
				// Change Line to White
				dynMat->SetVectorParameterValue(TEXT("Line Color"), FLinearColor(0.875f, 0.875f, 0.875f, 1.0f));
			}
		}

		// Get Material for Orb in Mesh
		Material = MeshComp->GetMaterial(1);
		if (Material)
		{
			// Make new Dynamic Material instance for Mesh material
			UMaterialInstanceDynamic* dynMat = UMaterialInstanceDynamic::Create(Material, this);

			FLinearColor faceColor;
			dynMat->GetVectorParameterValue(TEXT("Face Color"), faceColor);
			//FLinearColor lineColor;
			//dynMat->GetVectorParameterValue(TEXT("Line Color"), lineColor);

			const FLinearColor White(0.875f, 0.875f, 0.875f, 1.0f);
			const FLinearColor Black(0.04f, 0.04f, 0.04f, 1.0f);

			// if face is Black
			if (faceColor.R < 0.5f/* && lineColor.R < 0.5f*/)
			{
				// Change face to White
				dynMat->SetVectorParameterValue(TEXT("Face Color"), White);
				// Change Line to Black
				//dynMat->SetVectorParameterValue(TEXT("Line Color"), Black);

				PositiveState = false;
			}
		}
	}
}
