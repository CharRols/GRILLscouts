// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SolidBlock.generated.h"

UCLASS()
class CPPSPAWNTEST_API ASolidBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	UStaticMeshComponent* myBlock;
	UStaticMeshComponent* myOtherBlock;

	// Sets default values for this actor's properties
	ASolidBlock(const FObjectInitializer & PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
