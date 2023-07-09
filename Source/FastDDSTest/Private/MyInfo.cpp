// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInfo.h"

#include "LocationRotationTestPubSubTypes.h"
#include "fastdds/dds/domain/DomainParticipantFactory.hpp"

using namespace eprosima::fastdds::dds;

AMyInfo::AMyInfo()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyInfo::BeginPlay()
{
	Super::BeginPlay();
	// LocationRotationPublisher mypub;
	//LocationRotationSubscriber mysub;
	//if (mysub.init())
	//{
	//	mysub.run();
	//	// run(count, sleep);
	//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Initialed and run", true);
	//}
	TypeSupport _type(new LocationRotationBeanPubSubType());
	DomainParticipantQos pqos;
	pqos.name("Participant_pub");
	DomainParticipant* participant_ = DomainParticipantFactory::get_instance()->create_participant(0, pqos);
	_type.register_type(participant_);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Initialed and run", true);
}

void AMyInfo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AMyInfo::Tick(float DeltaSeconds)
{
}
