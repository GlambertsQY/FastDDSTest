// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInfo.h"

// #include "ObjectClassTest.h"

// #include "LocationRotationSubscriber.h"


// #include "LocationRotationPubSubTypes.h"
//
// #include <fastdds/dds/domain/DomainParticipantFactory.hpp>
// #include <fastdds/dds/subscriber/DataReader.hpp>
// #include <fastdds/dds/subscriber/SampleInfo.hpp>
// #include <fastdds/dds/subscriber/Subscriber.hpp>
// #include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>


// using namespace eprosima::fastdds::dds;

AMyInfo::AMyInfo()
{
	// participant_ = nullptr;
	// subscriber_ = nullptr;
	// topic_ = nullptr;
	// reader_ = nullptr;
	// type_ = new TypeSupport(new LocationRotationBeanPubSubType());
	PrimaryActorTick.bCanEverTick = true;
}

// bool AMyInfo::init()
// {
// 	//CREATE THE PARTICIPANT
// 	DomainParticipantQos pqos;
// 	pqos.name("FastDDSTestUE");
// 	participant_ = DomainParticipantFactory::get_instance()->create_participant(0, pqos);
// 	if (participant_ == nullptr)
// 	{
// 		return false;
// 	}
//
// 	//REGISTER THE TYPE
// 	//bUseRTTI = true;
// 	type_->register_type(participant_);
//
// 	//CREATE THE SUBSCRIBER
// 	subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
// 	if (subscriber_ == nullptr)
// 	{
// 		return false;
// 	}
//
// 	//CREATE THE TOPIC
// 	topic_ = participant_->create_topic(
// 		"myTopic",
// 		type_->get_type_name(),
// 		TOPIC_QOS_DEFAULT);
// 	if (topic_ == nullptr)
// 	{
// 		return false;
// 	}
//
// 	//CREATE THE READER
// 	DataReaderQos rqos = DATAREADER_QOS_DEFAULT;
// 	rqos.reliability().kind = RELIABLE_RELIABILITY_QOS;
// 	reader_ = subscriber_->create_datareader(topic_, rqos, &listener_);
// 	if (reader_ == nullptr)
// 	{
// 		return false;
// 	}
// 	return true;
// }
//
// void AMyInfo::SubListener::on_data_available(eprosima::fastdds::dds::DataReader* reader)
// {
// 	// Take data
// 	LocationRotationBean st;
// 	SampleInfo info;
//
// 	if (reader->take_next_sample(&st, &info) == ReturnCode_t::RETCODE_OK)
// 	{
// 		if (info.valid_data)
// 		{
// 			// Print your structure data here.
// 			++samples;
// 			FString s = st.LRJsonString().c_str();
// 			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, s, true);
// 			std::cout << "Sample received, count=" << samples << std::endl;
// 		}
// 	}
// }

// void AMyInfo::SubListener::on_subscription_matched(eprosima::fastdds::dds::DataReader* reader,
//                                                    const eprosima::fastdds::dds::SubscriptionMatchedStatus& info)
// {
// 	if (info.current_count_change == 1)
// 	{
// 		matched = info.total_count;
// 		std::cout << "Subscriber matched." << std::endl;
// 	}
// 	else if (info.current_count_change == -1)
// 	{
// 		matched = info.total_count;
// 		std::cout << "Subscriber unmatched." << std::endl;
// 	}
// 	else
// 	{
// 		std::cout << info.current_count_change
// 			<< " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
// 	}
// }

void AMyInfo::BeginPlay()
{
	Super::BeginPlay();
	// mysub = GetWorld()->SpawnActor<ALRSubscriberActor>(ALRSubscriberActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	mysub = NewObject<UObjectClassTest>();
	// mysub = NewObject<UObjectClassTest>();
	if(mysub->init())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "mysub Initialed and run", true);
	}
	cppSub = NewObject<UObjectClassTest>();
	cppSub->setParams(TEXT("Participant_Pub"), TEXT("LocationRotationTopic"));
	if(cppSub->init())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "cppSub Initialed and run", true);
	}
	// LocationRotationSubscriber mysub;
	// if (mysub.init())
	// {
	// 	mysub.run();
	// 	// run(count, sleep);
	// 	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Initialed and run", true);
	// }
	// if (init())
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Initialed and run", true);
	// }
}

void AMyInfo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// if (reader_ != nullptr)
	// {
	// 	subscriber_->delete_datareader(reader_);
	// }
	// if (topic_ != nullptr)
	// {
	// 	participant_->delete_topic(topic_);
	// }
	// if (subscriber_ != nullptr)
	// {
	// 	participant_->delete_subscriber(subscriber_);
	// }
	// DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

void AMyInfo::Tick(float DeltaSeconds)
{
	FString s1 = mysub->Message->c_str();
	FString s2 = cppSub->Message->c_str();
	UE_LOG(LogNet, Warning, TEXT("From Python: %s"), *s1);
	UE_LOG(LogNet, Warning, TEXT("From CPP: %s"), *s2);
	// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, mysub->Message, true);
}
