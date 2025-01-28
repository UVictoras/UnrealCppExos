// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

 // Sets default values
 APressurePlate::APressurePlate()
 {
  	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
 	PrimaryActorTick.bCanEverTick = true;
 
 	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Pressure Plate"));
 	_pressurePlate = BoxComponent;
 	_pressurePlate->SetBoxExtent(FVector(50.0f, 50.0f, 100.0f));
 	_pressurePlate->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
 	_pressurePlate->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
 	_pressurePlate->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
 	_pressurePlate->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap); // Overlap only with Pawns
 
 	// Bind the overlap events
 	_pressurePlate->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OverlapBegin);
 	_pressurePlate->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OverlapEnd);
 	
 	UStaticMeshComponent* BoxVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
 	BoxVisual->SetupAttachment(BoxComponent);
 	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
 
 	if (BoxVisualAsset.Succeeded())
 	{
 		BoxVisual->SetStaticMesh(BoxVisualAsset.Object);
 		BoxVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
 		BoxVisual->SetWorldScale3D(FVector(1.0f, 1.0f, 0.1f));
 	}
 }
 
 // Called when the game starts or when spawned
 void APressurePlate::BeginPlay()
 {
 	Super::BeginPlay();
 }
 
 // Called every frame
 void APressurePlate::Tick(float DeltaTime)
 {
 	Super::Tick(DeltaTime);
 
 }
 
 void APressurePlate::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
 {
 	_isTriggered = true;
 }
 
 void APressurePlate::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
 {
 	_isTriggered = false;
 }

