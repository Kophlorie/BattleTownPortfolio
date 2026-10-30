// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveGate.generated.h"

// Added classes that were not present in the original default code
// Except for the last one, these created for the protected functions that should appear in Blueprints it seems
class USceneComponent;
class USTaticMeshComponent;
class UBoxComponent;
class UPrimitiveComponent; // This one is called in the OnTriggerEntered protected function

// Third step: making it dependent on a condition
class AVictoryZone;

UCLASS()
class BATTLETOWNPROTOTYPE_API AInteractiveGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION() // Added lines
	void OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// That void function was set directly, I started to write it and it was proposed to be filled exactly like in the example, so I accepted it through the autocomplete/shift.

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Third step making the condition option activable or not depending on the needs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Escape Puzzle")
	bool ActivatePuzzle = true;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot; // USceneComponent*

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> GateMesh; // UStaticMeshComponent*

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerBox; // UBoxComponent*

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
	float OpeningHeight = 300.0f; // The height to which the gate will open

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
	float OpeningSpeed = 150.0f; // The speed at which the gate opens

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Escape Puzzle")
	TObjectPtr<AVictoryZone> VictoryZone;
private:
	// float CurrentHeight = 0.0f; // Current height of the gate // proposed by Copilot
	FVector ClosedPosition = FVector::ZeroVector; // The closed position of the gate
	bool bShouldOpen = false; // bIsOpening Whether the gate is currently opening

};
