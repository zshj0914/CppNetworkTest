// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class CPPNETWORKTEST_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	FVector GetAirResistane();
	FVector GetRollingResistane();

	void UpdateLocationFromVelocity(float DeltaTime);

	void ApplyRotation(float DeltaTime);

	UPROPERTY(EditAnywhere)	// The mass of the car (kg)
	float Mass = 1000;

	UPROPERTY(EditAnywhere)	// The force applied to the car when the throttle is fully down (N)
	float MaxDrivingForce = 10000;

	UPROPERTY(EditAnywhere)	// Minimum radius of the car turning circle at full lock (m)
	float MinTurningRadius = 10;

	UPROPERTY(EditAnywhere)	// Higher means more drag
	float DragCoefficient = 16;

	UPROPERTY(EditAnywhere) // Higher means more rolling resistance
	float RollingResistanceCoefficient = 0.015;

	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveForward(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRight(float Value);

	FVector Velocity;

	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedTransform)
	FTransform ReplicatedTransform;

	UFUNCTION()
	void OnRep_ReplicatedTransform();
	
	UPROPERTY(Replicated)
	FRotator ReplicatedRotation;

	float Throttle;
	float SteeringThrow;

};
