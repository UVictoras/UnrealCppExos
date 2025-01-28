// Fill out your copyright notice in the Description page of Project Settings.


#include "CEmitter.h"

// Sets default values
ACEmitter::ACEmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEmitter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACEmitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEmitter::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_isTriggered = true;
}

void ACEmitter::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (_isLocked == false)
	{
		_isTriggered = false;
	}
}