// Fill out your copyright notice in the Description page of Project Settings.

#include "CPPSpawnTest.h"
#include "CPPSpawnTestGameMode.h"
#include "SolidBlock.h"


void ACPPSpawnTestGameMode::BeginPlay() {
	Super::BeginPlay();
	UWorld* const World = GetWorld();

	if (World) {

		//Spawn C++ Defined Actor
		ASolidBlock* myBlock = World->SpawnActor<ASolidBlock>(ASolidBlock::StaticClass());

		//Set Location, Rotation, and Scale
		FRotator rotation = FRotator(40, 40, 40);
		FVector scale3D = FVector(2, 2, 2);
		FVector location = FVector(0, 0, 210);

		myBlock->SetActorScale3D(scale3D);
		//myBlock->SetActorLocation(location); 
		//myBlock->SetActorRotation(rotation);
		myBlock->SetActorLocationAndRotation(location, rotation);


		//Spawn a Blueprint-Defined Actor
		//AStoneSphere mySphere = World->SpawnActor<AStoneSphere>(AStoneSphere::StaticClass());

		//static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/StoneSphere.StoneSphere'"));
		//if (ItemBlueprint.Object) {
		//TSubclassOf<AActor> MyItemBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
		//}

		//FRotator spawnRot = FRotator(40, 40, 40);
		//FVector spawnLoc = FVector(90, 90, 210);
		//AActor* mySphere = SpawnBP<AActor>(World, StoneSphere, spawnLoc, spawnRot);


	}//end if(World)


}

