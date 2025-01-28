// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoors.h"

// Sets default values
ASlidingDoors::ASlidingDoors()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the scene component and set it as the root
	_sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	_sceneComponent->SetRelativeLocation(FVector::ZeroVector); // Ensure it's at the actor's origin
	RootComponent = _sceneComponent;

	// Left Door
	_leftDoor = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Door"));
	_leftDoor->InitBoxExtent(FVector(10, 10, 15));
	_leftDoor->bDynamicObstacle = true;
	_leftDoor->SetGenerateOverlapEvents(true);
	_leftDoor->SetupAttachment(_sceneComponent);
	_leftDoor->SetRelativeLocation(FVector(0.0f, -100.0f, 0.0f)); // Left of the origin

	UStaticMeshComponent* BoxVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh Left"));
	BoxVisual->SetupAttachment(_leftDoor);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (BoxVisualAsset.Succeeded())
	{
		BoxVisual->SetStaticMesh(BoxVisualAsset.Object);
		BoxVisual->SetRelativeLocation(FVector::ZeroVector); // Center mesh in box component
		BoxVisual->SetWorldScale3D(FVector(0.3f, 2.0f, 5.0f));
	}

	// Right Door
	_rightDoor = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Door"));
	_rightDoor->InitBoxExtent(FVector(10, 10, 15));
	_rightDoor->bDynamicObstacle = true;
	_rightDoor->SetGenerateOverlapEvents(true);
	_rightDoor->SetupAttachment(_sceneComponent);
	_rightDoor->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f)); // Right of the origin

	UStaticMeshComponent* BoxVisual2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh Right"));
	BoxVisual2->SetupAttachment(_rightDoor);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset2(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (BoxVisualAsset2.Succeeded())
	{
		BoxVisual2->SetStaticMesh(BoxVisualAsset2.Object);
		BoxVisual2->SetRelativeLocation(FVector::ZeroVector); // Center mesh in box component
		BoxVisual2->SetWorldScale3D(FVector(0.3f, 2.0f, 5.0f));
	}

	_progress = 0.0f;
	_doorCooldownTime = 3.0f;
	_doorDistance = 150.0f;

	_isOpening = false;
	_isOpened = false;
	_isDoorOnCooldown = false;

	_leftStartPos = _leftDoor->GetRelativeLocation();
	_leftEndPos = _leftStartPos + _leftDoor->GetRightVector() * _doorDistance * -1.0f;

	_rightStartPos = _rightDoor->GetRelativeLocation();
	_rightEndPos = _rightStartPos + _rightDoor->GetRightVector() * _doorDistance;
}



// Called when the game starts or when spawned
void ASlidingDoors::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlidingDoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OpenDoor(DeltaTime); 
}

void ASlidingDoors::OpenDoor(float deltaTime)
{
	_deltaTime = deltaTime;

	if (_isDoorOnCooldown)
	{
		_doorCooldownTime -= _deltaTime;
		if (_doorCooldownTime <= 0.0f)
		{
			_isOpening = false;
			_isOpened = false;
			_isDoorOnCooldown = false;
		}
	}

	if (_isOpening)
	{
		_progress = FMath::Clamp(_progress + _deltaTime, 0.0f, 1.0f); 
	}
	else
	{
		_progress = FMath::Clamp(_progress - _deltaTime, 0.0f, 1.0f); 
	}

	_leftDoor->SetRelativeLocation(FMath::Lerp(_leftStartPos, _leftEndPos, _progress));
	_rightDoor->SetRelativeLocation(FMath::Lerp(_rightStartPos, _rightEndPos, _progress));

	if (_isOpening && _progress >= 1.0f)
	{
		_isOpened = true;
		_isDoorOnCooldown = true;  
	}
	else if (!_isOpening)
	{
		_isDoorOnCooldown = false; 
		_doorCooldownTime = 3.0f;  
	}
}