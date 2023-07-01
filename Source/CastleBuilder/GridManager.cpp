// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "Components/BoxComponent.h"

// Sets default values
AGridManager::AGridManager()
{
    GridSizeX = 5;
    GridSizeY = 5;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent->Mobility = EComponentMobility::Static;

    SetRootComponent(RootComponent);

    UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->SetupAttachment(RootComponent);
    BoxComponent->OnClicked.AddDynamic(this, &AGridManager::OnGridClicked);
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
    BoxComponent->SetBoxExtent(FVector(GridSizeX * GridXOffset, GridSizeY * GridYOffset, 1.0f));


}

void AGridManager::OnGridClicked(UPrimitiveComponent *ClickedComp, FKey ButtonClicked)
{
    FHitResult HitResult;
    if(GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult))
    {
        HitResult.Location;
        UE_LOG(LogTemp, Warning, TEXT("Clicked on grid") , *HitResult.Location.ToString());
    }
}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();

	 // Spawn grid cells
    for (int32 X = 0; X < GridSizeX; ++X)
    {
        for (int32 Y = 0; Y < GridSizeY; ++Y)
        {
            FVector SpawnLocation(X * GridXOffset, Y * GridYOffset, 0.0f);
            FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
            FActorSpawnParameters SpawnParams;
            GetWorld()->SpawnActor<AGridCell>(GridCellClass, SpawnLocation, SpawnRotation, SpawnParams);
        }
    }
	
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

