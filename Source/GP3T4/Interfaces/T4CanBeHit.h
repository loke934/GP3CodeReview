// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include"T4CanBeHit.generated.h"

UINTERFACE()
class GP3T4_API UT4CanBeHit : public UInterface
{
	GENERATED_BODY()
};

class GP3T4_API IT4CanBeHit
{
	GENERATED_BODY()
	
public:
	virtual void GotHit(AActor* OtherActor);
};
