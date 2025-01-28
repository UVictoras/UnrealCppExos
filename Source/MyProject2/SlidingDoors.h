// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SlidingDoors.generated.h"

UCLASS()
class MYPROJECT2_API ASlidingDoors : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* _sceneComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* _leftDoor;
	UPROPERTY(EditAnywhere)
	UBoxComponent* _rightDoor;

	UPROPERTY()
	float _deltaTime;
	UPROPERTY()
	float _progress;
	UPROPERTY()
	float _doorDistance;
	UPROPERTY()
	float _doorCooldownTime;
	

	UPROPERTY()
	bool _isOpened;
	UPROPERTY()
	bool _isDoorOnCooldown;

	UPROPERTY()
	FVector _leftStartPos;
	UPROPERTY()
	FVector _leftEndPos;
	UPROPERTY()
	FVector _rightStartPos;
	UPROPERTY()
	FVector _rightEndPos;
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool _isOpening;

public:

	// Sets default values for this actor's properties
	ASlidingDoors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "OpenDoor"))
	void OpenDoor(float deltaTime);

};
