// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEmitter.h"
#include "CReceiver.generated.h"

UCLASS()
class MYPROJECT2_API ACReceiver : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere)
	TArray<ACEmitter*> _emitters;

	// Sets default values for this actor's properties
	ACReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	bool _isEnabled;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Event(float deltaTime);
};
