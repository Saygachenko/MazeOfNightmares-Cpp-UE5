// Fill out your copyright notice in the Description page of Project Settings.


#include "MONScreamer.h"

#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMONScreamer::AMONScreamer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void AMONScreamer::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMONScreamer::OnBoxBeginOverlap);
}

// Called every frame
void AMONScreamer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMONScreamer::OnBoxBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller)
	{
		UUserWidget* Screamer = CreateWidget(Controller, ScreamerClass);
		if (Screamer)
		{
			Screamer->AddToViewport();
			if (ScreamerSound)
			{
				UGameplayStatics::SpawnSoundAtLocation(this, ScreamerSound, GetActorLocation());
				
				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "RemoveSreamerComponents", Screamer);

				GetWorld()->GetTimerManager().SetTimer(SreamerHandle, Delegate, 4.5f, false);
			}
		}
	}
}

void AMONScreamer::RemoveSreamerComponents(UUserWidget* SreamerParams)
{
	SreamerParams->RemoveFromViewport();

	GetWorld()->GetTimerManager().ClearTimer(SreamerHandle);

	this->Destroy();
}