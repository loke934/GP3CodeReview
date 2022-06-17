#include "T4MovingApple.h"

#include "Components/SphereComponent.h"
#include "GP3T4/Interfaces/IsPlayerCharacter.h"

AT4MovingApple::AT4MovingApple()
{
	PrimaryActorTick.bCanEverTick = true;

	AppleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppleMesh"));
	SetRootComponent(AppleMesh);

	AppleAggroRadius = CreateDefaultSubobject<USphereComponent>(TEXT("AggroRadius"));
	AppleAggroRadius->SetupAttachment(AppleMesh);

	AppleAggroRadius->OnComponentBeginOverlap.AddDynamic(this, &AT4MovingApple::StartMovingTowardsPlayer);
}

void AT4MovingApple::BeginPlay()
{
	Super::BeginPlay();
	
}

void AT4MovingApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bShouldFollowPlayer || PlayerActor == nullptr) { return;}

	//Stop following if we are too close to the player
	if (FVector::Distance(PlayerActor->GetActorLocation(), GetActorLocation()) < StopMovingRange)
	{
		ReceiveStopMoving();
		AppleMesh->SetSimulatePhysics(false);
		bShouldFollowPlayer = false;
		return;
	}

	auto DirToPlayer = PlayerActor->GetActorLocation() - GetActorLocation();
	DirToPlayer.Normalize();

	AppleMesh->AddForce(DirToPlayer * FollowSpeed, EName::None, true);	

}

void AT4MovingApple::StartMovingTowardsPlayer(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if (OtherActor && OtherActor->Implements<UIsPlayerCharacter>())
	{
		ReceiveStartMoving();
		PlayerActor = OtherActor;
		bShouldFollowPlayer = true;
		AppleMesh->SetSimulatePhysics(true);

		auto DirToPlayer = PlayerActor->GetActorLocation() - GetActorLocation();
		DirToPlayer.Normalize();
		AppleMesh->AddForce(DirToPlayer * FollowSpeed * 5, EName::None, true);
	}
}

