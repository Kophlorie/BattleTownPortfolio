// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "GameFramework/PlayerController.h" we are replacing this by the one below:
#include "BattleTownPrototypePlayerController.h" // so that's an actual new line
#include "BattleTownPlayerController.generated.h"

// Added line
class ACharacter;

/**
 * 
 */
UCLASS()
class BATTLETOWNPROTOTYPE_API ABattleTownPlayerController : public ABattleTownPrototypePlayerController // previouslyAPlayerController
{
	GENERATED_BODY()

	// All below are added lines

public:
	virtual void SetupInputComponent() override;

protected: 

	// we use EditInstanceOnly instead of EditAnywhere
	// because we want to assign references to 
	// specific Actors already placed in our Level, 
	// not choose character classes or create new instances.

	// The distinction between APawn* and TObjectPtr<APawn>  
	// comes down to whether we're storing a reference as part of an Unreal object's state 
	// or simply using it temporarily inside a function.
	// Here: An Unreal object pointer wrapper:
	// UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	// TObjectPtr<ACharacter> CharacterA;
	//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Character Switching")
	// Now we change EditInstanceOnly to VisibleInstanceOnly to make CharacterA visible in the editor but not editable, 
	// while still allowing it to be set in the Level Blueprint or through code.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Character Switching")
	TObjectPtr<ACharacter> CharacterA;
	/* Here, CharacterA is a member variable of our PlayerController.
	Unlike CurrentPawn, it needs to remain available across multiple function calls.
	The combination of UPROPERTY() and TObjectPtr<> allows Unreal's reflection and garbage collection systems to recognize and track this reference.
	Importantly, TObjectPtr<> by itself isn't a substitute for UPROPERTY() when you need a persistent, garbage-collector-tracked member reference.
	*/

	// UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Character Switching")
	// Similarly, we declare CharacterB as a UPROPERTY with VisibleInstanceOnly to make it visible in the editor but not editable.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Character Switching")
	TObjectPtr<ACharacter> CharacterB;

	// Added in the second step along with the VisibleInstanceOnly switch
	virtual void BeginPlay() override;

private:
	void SwitchCharacter();
};
