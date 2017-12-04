// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float Throttle;

	UPROPERTY()
	float SteeringThrow;

	UPROPERTY()
	float DeltaTime;

	UPROPERTY()
	float Time;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPNETWORKTEST_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove Move);

	FVector GetVelocity() { return Velocity; };
	void SetVelocity(FVector Val) { Velocity = Val; };

	float GetThrottle() { return Throttle; };
	void SetThrottle(float Val) { Throttle = Val; };

	float GetSteeringThrow() { return SteeringThrow; };
	void SetSteeringThrow(float Val) { SteeringThrow = Val; };

	FGoKartMove GetLastMove() { return LastMove; };

private:
	FGoKartMove CreateMove(float DeltaTime);

	FVector GetAirResistane();
	FVector GetRollingResistane();

	void UpdateLocationFromVelocity(float DeltaTime);

	void ApplyRotation(float DeltaTime, float SteeringThrow);

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
	
	FVector Velocity; // local client velocity

	float Throttle;
	float SteeringThrow;

	FGoKartMove LastMove;

};
