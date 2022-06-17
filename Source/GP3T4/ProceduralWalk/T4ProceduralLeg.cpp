#include "T4ProceduralLeg.h"

AT4ProceduralLeg::AT4ProceduralLeg()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	LegSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SpiderLeg"));
	LegSkeletalMesh->SetupAttachment(RootComponent);

	LegPosComponent = CreateDefaultSubobject<USceneComponent>(TEXT("LegComponentPosition"));
	LegPosComponent->SetupAttachment(LegSkeletalMesh);

	LegTargetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("LegTargetPosition"));
	LegTargetComponent->SetupAttachment(RootComponent);	
}

void AT4ProceduralLeg::BeginPlay()
{
	Super::BeginPlay();
}

void AT4ProceduralLeg::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

