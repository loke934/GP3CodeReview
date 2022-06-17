#include "T4ProceduralApple.h"

#include "T4ProceduralLeg.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GP3T4/Interfaces/IsPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


AT4ProceduralApple::AT4ProceduralApple()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	AppleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppleMesh"));
	AppleMesh->SetupAttachment(RootComponent);

	//Cursed leg shit
	LegsParent = CreateDefaultSubobject<USceneComponent>(TEXT("LegsParent"));
	LegsParent->SetupAttachment(RootComponent);

	FrontLeftLeg = CreateDefaultSubobject<UChildActorComponent>(TEXT("FrontLeftLeg"));
	FrontLeftLeg->SetupAttachment(LegsParent);

	FrontRightLeg = CreateDefaultSubobject<UChildActorComponent>(TEXT("FrontRightLeg"));
	FrontRightLeg->SetupAttachment(LegsParent);

	BackLeftLeg = CreateDefaultSubobject<UChildActorComponent>(TEXT("BackLeftLEg"));
	BackLeftLeg->SetupAttachment(LegsParent);

	BackRightLeg = CreateDefaultSubobject<UChildActorComponent>(TEXT("BackRightLeg"));
	BackRightLeg->SetupAttachment(LegsParent);

	LegPositions = CreateDefaultSubobject<USceneComponent>(TEXT("LegPositions"));
	LegPositions->SetupAttachment(LegsParent);	
}

void AT4ProceduralApple::BeginPlay()
{
	Super::BeginPlay();	

	//This has to be done otherwise the legs don't spawn in scenes that has >ever< had world partitioning on...
	if (LegBP)
	{
		FrontLeftLeg->SetChildActorClass(LegBP);
		FrontRightLeg->SetChildActorClass(LegBP);
		BackLeftLeg->SetChildActorClass(LegBP);
		BackRightLeg->SetChildActorClass(LegBP);
	}

	SetupSpiderLegs();
	Player = UGameplayStatics::GetPlayerCharacter(this, 0);
}

void AT4ProceduralApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player == nullptr) { return;}

	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Location = GetActorLocation();	

	if (FVector::Distance(PlayerLocation, Location) <= MinDistFromPlayer)
	{
		bAtMinDistance = true;
		StopAggro(PlayerLocation, Location);
	}
	else if(bAtMinDistance)
	{
		bAtMinDistance = false;
		StartAggro();
	}	

	if (!bShouldFollowPlayer || Player == nullptr) { return; }

	//Move towards player
	const FVector DirToPlayer = (PlayerLocation - Location).GetSafeNormal();
	AddActorWorldOffset(DirToPlayer * FollowSpeed * DeltaTime);
	SetActorRotation(DirToPlayer.Rotation());
}

void AT4ProceduralApple::StartAggro()
{
	bShouldFollowPlayer = true;
	ReceiveStartMoving();
}

void AT4ProceduralApple::StopAggro(FVector PlayerLocation, FVector Location)
{
	//Continue rotating the apple even if we stop moving towards the player
	const FVector DirToPlayer = (PlayerLocation - Location).GetSafeNormal();
	SetActorRotation(DirToPlayer.Rotation());
	
	bShouldFollowPlayer = false;
	ReceiveStopMoving();
}

void AT4ProceduralApple::SetupSpiderLegs()
{
	//Cuuuursed
	//Todo all the spider stuff needs to be in its own component. Maybe make it more procedural as well so you can have X amount of legs..
	FrontLeftLegCast = Cast<AT4ProceduralLeg>(FrontLeftLeg->GetChildActor());
	FrontRightLegCast = Cast<AT4ProceduralLeg>(FrontRightLeg->GetChildActor());
	BackLeftLegCast = Cast<AT4ProceduralLeg>(BackLeftLeg->GetChildActor());
	BackRightLegCast = Cast<AT4ProceduralLeg>(BackRightLeg->GetChildActor());

	if (FrontLeftLegCast != nullptr && FrontRightLegCast != nullptr && BackLeftLegCast != nullptr && BackRightLegCast != nullptr)
	{		
		FrontLeftLegCast->OppositeLeg = FrontRightLegCast;
		FrontRightLegCast->OppositeLeg = FrontLeftLegCast;
		BackLeftLegCast->OppositeLeg = BackRightLegCast;
		BackRightLegCast->OppositeLeg = BackLeftLegCast;

		FrontLeftLegCast->bIsFrontLeg = true;
		FrontRightLegCast->bIsFrontLeg = true;
		
		FrontLeftLegCast->bIsGrounded = true;
		BackRightLegCast->bIsGrounded = true;

	}
}