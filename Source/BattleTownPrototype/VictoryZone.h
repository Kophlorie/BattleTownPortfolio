// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VictoryZone.generated.h"

// Added lines
class USceneComponent;
class UBoxComponent;
class UPrimitiveComponent;
class ACharacter;

UCLASS()
class BATTLETOWNPROTOTYPE_API AVictoryZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVictoryZone();

	// Is the OTHER playable character inside?
	bool HasOtherCharacterInside(const AActor* RequestingCharacter) const;
	bool AreBothCharactersInside() const;

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override; // Commented for this classs

	// Added lines
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerBox;

	UFUNCTION() // CAREFUL! It is NOT UFONCTION!!! O to U !!!
	void OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerExited(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override; // Commented for this classs

	// Added lines
	TWeakObjectPtr<ACharacter> CharacterAInside;
	TWeakObjectPtr<ACharacter> CharacterBInside;
	bool bPuzzleCompleted = false;

	// A weak pointer, TWeakObjectPtr, is different from TObjectPtr : 
	// it references an object without keeping that object alive through garbage collection.
	// That's appropriate for a trigger zone temporarily remembering which characters are inside it.
	// IsValid() tells us whether its referenced character still exists.

};
