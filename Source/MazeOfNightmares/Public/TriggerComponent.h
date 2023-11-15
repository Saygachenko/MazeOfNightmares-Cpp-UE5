// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class MAZEOFNIGHTMARES_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay();

	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag = "None";

private:
	AActor* GetAcceptableActor();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> ScreamerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ScreamerSound;

	void CheckOverlapping();

	FTimerHandle DestroyComponentTimer;

	UFUNCTION()
	void DestroyActorComponents(UUserWidget* ScreamerParam, USoundBase* ScreamerSoundParam);
};
