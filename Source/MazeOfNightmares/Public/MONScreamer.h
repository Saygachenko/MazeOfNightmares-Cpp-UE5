// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MONScreamer.generated.h"

UCLASS()
class MAZEOFNIGHTMARES_API AMONScreamer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMONScreamer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ScreamerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ScreamerSound;

	FTimerHandle SreamerHandle;

	UFUNCTION()
	void RemoveSreamerComponents(UUserWidget* SreamerParams);
};
