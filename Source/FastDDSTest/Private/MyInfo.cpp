// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInfo.h"

AMyInfo::AMyInfo()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyInfo::BeginPlay()
{
	Super::BeginPlay();
	mysub = NewObject<UJsonStrSubscriber>();
	if (mysub->init())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "mysub Initialed and run", true);
	}
	cppSub = NewObject<UJsonStrSubscriber>();
	cppSub->setParams(TEXT("Participant_Pub"), TEXT("LocationRotationTopic"));
	if (cppSub->init())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "cppSub Initialed and run", true);
	}
	mypub = NewObject<UJsonStrPublisher>();
	mypub->setParams(TEXT("Participant_Pub"), TEXT("UE2Python"));
	if (mypub->init())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "mypub Initialed and run", true);
	}
}

void AMyInfo::Tick(float DeltaSeconds)
{
	FString s1 = mysub->Message->c_str();
	FString s2 = cppSub->Message->c_str();
	UE_LOG(LogNet, Warning, TEXT("From Python: %s"), *s1);
	UE_LOG(LogNet, Warning, TEXT("From CPP: %s"), *s2);
	mypub->SendMessage("From UE");
	// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, mysub->Message, true);
}
