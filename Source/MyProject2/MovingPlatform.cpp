// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_destination = 0;
	_progress = 0.0f;

    UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Moving Platform"));
    _box = BoxComponent;
	_box->InitBoxExtent(FVector(100, 100, 5));
	_box->bDynamicObstacle = true;
	_box->SetGenerateOverlapEvents(true);
	_box->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

    UStaticMeshComponent* BoxVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
    BoxVisual->SetupAttachment(BoxComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

    if (BoxVisualAsset.Succeeded())
    {
        BoxVisual->SetStaticMesh(BoxVisualAsset.Object);
        BoxVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -5.0f));
        BoxVisual->SetWorldScale3D(FVector(2.0f, 2.0f, 0.1f));
    }
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	for (FVector relativePos : _relativePosArray)
	{
		_locationArray.Add(relativePos + this->GetActorLocation());
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isEnabled)
		_isMoving = true;
	else
		_isMoving = false;
}

void AMovingPlatform::Event(float deltaTime)
{
	if (_isMoving == false)
		return;
	_progress += deltaTime / 2;

	if (FMath::Clamp(_progress, 0.0f, 1.0f) == 1)
	{
		_progress = 0.0f;
		_destination = (_destination + 1) % _locationArray.Num();
	}

	this->SetActorLocation(FMath::Lerp(_locationArray[_destination], _locationArray[(_destination + 1) % _locationArray.Num()], _progress));
}