// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInfo.h"

#include "LocationRotationPublisher.h"
#include "LocationRotationSubscriber.h"

using namespace eprosima::fastdds::dds;

AMyInfo::AMyInfo()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyInfo::BeginPlay()
{
	Super::BeginPlay();
	LocationRotationPublisher mypub; 
	if (mypub.init())
	{
		mypub.run();
		// run(count, sleep);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Initialed and run", true);
	}
}

void AMyInfo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AMyInfo::Tick(float DeltaSeconds)
{
}
