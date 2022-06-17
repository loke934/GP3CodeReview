#include "T4Planet.h"

AT4Planet::AT4Planet()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = Root;
	Planets.Empty();
}

void AT4Planet::BeginPlay()
{
	Super::BeginPlay();

	if (bIsSun) {Sun = this;}
	Planets.Add(this);
	const FVector PlanetLocation = GetActorLocation();
	WorldHeight = PlanetLocation.Z;
}

void AT4Planet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSun)
	{
		ExitCondition();
		return;
	}
	if (Sun == nullptr)
	{return;}
	
	if (!bIsHit)
	{
		RotateAroundSun(DeltaTime); 
	}
	else
	{
		SimulateGravity(DeltaTime);
	}
	TimeSinceStart += DeltaTime;
}

void AT4Planet::GotHit(AActor* OtherActor)
{
	bIsHit = true;
	Velocity = (GetActorLocation() - OtherActor->GetActorLocation()).GetSafeNormal() * 100;
}

void AT4Planet::ExitCondition()
{
	if (Planets.Num() == 1)
	{
		ReceiveOnExit();
		Planets.Remove(this);
	}
}

void AT4Planet::RotateAroundSun(const float DeltaTime)
{
	if (!HasSetStartValues)
	{
		DistanceFromSun = FVector::Dist2D(GetActorLocation(), Sun->GetActorLocation());
		FVector SunToPlanet = GetActorLocation() - Sun->GetActorLocation();
		SunToPlanet.Normalize();
		StartAngle = atan2(SunToPlanet.Y, SunToPlanet.X);
		UE_LOG(LogTemp, Warning, TEXT("%f"), StartAngle);
		HasSetStartValues = true;
	}

	FRotator PlanetRotation = GetActorRotation();
	PlanetRotation.Yaw += AxisLapsPerSecond * DeltaTime * 360;
	SetActorRotation(PlanetRotation);
	
	const float RotationSpeed = SunLapsPerSecond * PI * 2;
	const float CurrentAngle = RotationSpeed * TimeSinceStart + StartAngle;
	const FVector2d VectorToSun2d = FVector2d(cos(CurrentAngle), sin (CurrentAngle)) * DistanceFromSun;
	const FVector VectorToSun = FVector(VectorToSun2d, WorldHeight - Sun->GetActorLocation().Z);
	SetActorLocation(VectorToSun + Sun->GetActorLocation());
}

void AT4Planet::SimulateGravity(const float DeltaTime)
{
	const FVector CurrentLocation = GetActorLocation();
    for (size_t i = 0; i < Planets.Num(); i++)
    {
    	const AT4Planet* OtherPlanet = Planets[i];
    	if (OtherPlanet == this) {continue;}
    	const FVector OtherLocation = OtherPlanet->GetActorLocation();
    	const FVector FromCurrentToOther = OtherLocation - CurrentLocation;
    	const float DistanceSqr = pow(FromCurrentToOther.Size(), 2);
    	const float GravityForce = GravityConstant * (Mass * OtherPlanet->Mass / DistanceSqr);
    	Velocity += (GravityForce / Mass * DeltaTime) * FromCurrentToOther.GetSafeNormal();
    	FHitResult Hit;
    	AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);
    	if (Hit.bBlockingHit)
    	{
    		DeathHit = Hit;
    		Velocity = FVector::Zero();
    		ReceiveOnDestroy();
            if (Hit.GetActor()->Implements<UT4CanBeHit>())
            {
	            IT4CanBeHit* HittableObject = Cast<IT4CanBeHit>(Hit.GetActor());
            	//might be destroyed when got hit gets called?!?!
            	HittableObject->GotHit(this);
            }
    		Planets.Remove(this);
    		this->Destroy();
    	}
    }
}


