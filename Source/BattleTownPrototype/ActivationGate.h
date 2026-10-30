// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivationGate.generated.h"


// Added classes that were not present in the original default code
// Except for the last one. 
// They tell C++ that these classes exist. 
// Their actual definitions are provided by Unreal Engine.
class USceneComponent; // Provides a position, rotation, scale and ability to attach other components
class USTaticMeshComponent; // Represents a visible 3D mesh, with rendering and collision capabilities
class UBoxComponent; // Defines a box shaped collision volume
class UPrimitiveComponent; // This one is called in the OnTriggerEntered protected function
// It is the Common parent class of collision capable components, used in overlap event parameters

// In a second step
class APressurePlate;

UCLASS()
class BATTLETOWNPROTOTYPE_API AActivationGate : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActivationGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION() // Added lines
	void OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// That void function was set directly, I started to write it and it was proposed to be filled exactly like in the example, so I accepted it through the autocomplete/shift.

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// The stationary reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot; // USceneComponent*

	// Existing mesh, now attached to DoorHinge
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> GateMesh; // UStaticMeshComponent*

	// Existing box becomes the Side A trigger
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerBox; // UBoxComponent*

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
	float OpeningHeight = 300.0f; // The height to which the gate will open

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
	float OpeningSpeed = 150.0f; // The speed at which the gate opens

	// In a second step
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cooperative Puzzle")
	TObjectPtr<APressurePlate> PlateA; // APressurePlate*

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Cooperative Puzzle")
	TObjectPtr<APressurePlate> PlateB; // APressurePlate*

	// Unlike our PlayerController that was created at runtime, the gate is an Actor placed directly in the level.
	// Therefore, we can select the gate in the World Outliner and assign the two existing pressure plates through its Details panel.


private:
	// float CurrentHeight = 0.0f; // Current height of the gate // proposed by Copilot
	FVector ClosedPosition = FVector::ZeroVector; // The closed position of the gate

	bool bShouldOpen = false; // bIsOpening Whether the gate is currently opening
	bool bShouldOpen_i = false; // bIsOpening Whether the gate is currently opening


};
