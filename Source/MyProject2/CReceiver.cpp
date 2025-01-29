// Fill out your copyright notice in the Description page of Project Settings.


#include "CReceiver.h"

 // Sets default values
 ACReceiver::ACReceiver()
 {
  	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
 	PrimaryActorTick.bCanEverTick = true;
 
 }
 
 // Called when the game starts or when spawned
 void ACReceiver::BeginPlay()
 {
 	Super::BeginPlay();
 	
 }
 
 // Called every frame
 void ACReceiver::Tick(float DeltaTime)
 {
 	Super::Tick(DeltaTime);
 
 	Event(DeltaTime);
 
    if (_emitters.Num() == 0)
    {
        _isEnabled = true;
        return;
    }

 	for (ACEmitter* emitter : _emitters)
 	{
 		if (emitter->_isTriggered == false)
 		{
 			_isEnabled = false;
 			return;
 		}
 	}
 	_isEnabled = true;
 }
 
 void ACReceiver::Event(float deltaTime)
 {

 }