// Fill out your copyright notice in the Description page of Project Settings.


#include "T4AIColliderEvent.h"

#include "T4AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "GP3T4/GP3T4Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AT4AIColliderEvent::AT4AIColliderEvent()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AT4AIColliderEvent::OnBeginOverlap);
	//BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AT4AIColliderEvent::OnEndOverlap); Disabled for now

	TriggerName = ("bDisabledMovement");
}

// Called when the game starts or when spawned
void AT4AIColliderEvent::BeginPlay()
{
	Super::BeginPlay();
	
}

void AT4AIColliderEvent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(AGP3T4Character* Player = Cast<AGP3T4Character>(OtherActor))
	{
		TArray<AActor*> AIFound;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIClass, AIFound);
		
		for (AActor* Found : AIFound)
		{
			AT4AIBaseCharacter* Character = Cast<AT4AIBaseCharacter>(Found);
			AT4AIController* Controller = Cast<AT4AIController>(Character->GetController());
			Controller->GetBlackboardComponent()->SetValueAsBool(TriggerName, bBoolValue);
		}
	}
}

void AT4AIColliderEvent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if(AGP3T4Character* Player = Cast<AGP3T4Character>(OtherActor))
	{
		TArray<AActor*> AIFound;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIClass, AIFound);

		for (AActor* Found : AIFound)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "Enabling movement");
			AT4AIBaseCharacter* Character = Cast<AT4AIBaseCharacter>(Found);
			AT4AIController* Controller = Cast<AT4AIController>(Character->GetController());
			Controller->GetBlackboardComponent()->SetValueAsBool(TriggerName, bBoolValue);
		}
	}*/
}

