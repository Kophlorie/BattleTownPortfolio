// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class UStaticMeshComponent; // Added element for out platform

UCLASS()
class BATTLETOWNPROTOTYPE_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Added elements for out platform. The rest came as it was.
// UPROPERTY(...) exposes properties to Unreal's systems. 
// With EditAnywhere, you'll be able to change 
// Amplitude and Speed directly from the editor without recompiling.
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PlatformMesh;
	// TObjectPtr<UStaticMeshComponent> is Unreal's object-reference 
	// wrapper for reflected UObject pointers. 
	// The -> operator, then, accesses members of the referenced object, 
	// just as with ordinary C++ pointers.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ZAmplitude = 500.0f; // Over Z: the amplitude up and down

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float XAmplitude = -400.0f; // Over X: the amplitude east and west

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 1.0f; // Notice that Speed is an angular speed, not centimetres per second. 
						// Increasing it makes the oscillation faster.
	
private:
	FVector InitialLocation = FVector::ZeroVector;
	//float ElapsedTime = 0.0f; // Basically this is replaced by PhaseTime: don't panic!
	float PhaseTime = 0.0f;
	int32 Phase = 0;  // 0=Up, 1=Left, 2=Return, 3=Down

};
