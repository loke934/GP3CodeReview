#include "T4StretchyCorridor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AT4StretchyCorridor::AT4StretchyCorridor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AT4StretchyCorridor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetBackWallPosition();
	OnReceiveTick();
}

void AT4StretchyCorridor::BeginPlay()
{
	Super::BeginPlay();
	const float StartYaw = GetActorRotation().Yaw;
	const int OddOrEven = static_cast<int>(abs(StartYaw) / 90);
	bRotatedForward = static_cast<bool>(OddOrEven % 2);
	Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	StretchyLocation = GetActorLocation();
	StretchyRight = GetActorRightVector();
	SetBackWallPosition();
	OnReceiveBeginPlay();
}

bool AT4StretchyCorridor::IsPlayerInside()
{
	const FVector DirectionToPlayer = (Player->GetActorLocation() - StretchyLocation).GetSafeNormal();
	return FVector::DotProduct(StretchyRight, DirectionToPlayer) > 0;
}

void AT4StretchyCorridor::SetBackWallPosition()
{
	if (Player == nullptr) {return;}
	
	const float DistToPlayer = FVector::Distance(StretchyLocation, Player->GetActorLocation());
	const float ModifiedDist = FMath::Clamp(sqrt(DistToPlayer) * MulWithSqrt, MinDist, MaxDist);
	BackWallPosition = StretchyLocation + (StretchyRight * ModifiedDist);
}

