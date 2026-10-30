// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

// Added lines
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class BATTLETOWNPROTOTYPE_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

protected:
	// Called when the game starts or when spawned
	// virtual void BeginPlay() override; // We remove this function as well

	// Added lines
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PlateMesh; // UStaticMeshComponent*

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerBox; // UBoxComponent*

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PressurePlate")
	bool bIsActivated = false; // Whether the pressure plate is currently activated

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override; // For the first time I think we actually remove this one

	// Added lines
	UFUNCTION(BlueprintPure, Category = "PressurePlate")
	bool IsActivated() const; // Copilot proposes this that we don't use: { return bIsActivated; } // Returns whether the pressure plate is activated
	// This is a getter function that allows another Actor, such as our gate, to read the plate's state.
	// The const keyword means that the function promises not to modify the object's ordinary member state.
	// BlueprintPure also makes the function callable from Blueprint as a value, producing node without execution pins.

	// Adding now as a second step
	// These signatures are defined by Unreal's collision delegates. We must respect them for AddDynamic() to bind our functions correctly.
	UFUNCTION()
	void OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerExited(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
