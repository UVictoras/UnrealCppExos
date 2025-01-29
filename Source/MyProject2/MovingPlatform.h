// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CReceiver.h"
#include "MovingPlatform.generated.h"

UCLASS()
class MYPROJECT2_API AMovingPlatform : public ACReceiver
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();
	
	UPROPERTY(EditAnywhere)
	TArray<FVector> _relativePosArray;

	UPROPERTY(EditAnywhere)
	float _speed;

private:

	UPROPERTY()
	TArray<FVector> _locationArray;

	UPROPERTY()
	int64 _destination;

	UPROPERTY()
	float _progress;

	UPROPERTY()
	UBoxComponent* _box;

	UPROPERTY()
	bool _isMoving;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Event(float deltaTime) override;
};
