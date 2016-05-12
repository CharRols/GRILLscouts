// Fill out your copyright notice in the Description page of Project Settings.

#include "CPPSpawnTest.h"
#include "SolidBlock.h"


// Sets default values
ASolidBlock::ASolidBlock(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	myBlock = PCIP.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("SolidBlock"));

	static ConstructorHelpers::FObjectFinder <UStaticMesh>StaticMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder <UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));

	myBlock->SetStaticMesh(StaticMesh.Object);
	myBlock->SetMaterial(0, Material.Object);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Spawn a blueprint defined actor when this c++ defined actor is spawned. **FObjectFinder MUST be used in a constructor
	static ConstructorHelpers::FObjectFinder<UBlueprint> stoneSphere(TEXT("Blueprint'/Game/StoneSphereBP.StoneSphereBP'"));
	if (stoneSphere.Object) {
		myStoneSphere = (UClass*)stoneSphere.Object->GeneratedClass;
	}

	UWorld* const World = GetWorld();
	if (World) {
		AActor* mySphere = World->SpawnActor<AActor>(myStoneSphere);


		FVector spawnLoc = FVector(90, 90, 210);
		mySphere->SetActorLocation(spawnLoc);
	}

}

// Called when the game starts or when spawned
void ASolidBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASolidBlock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

