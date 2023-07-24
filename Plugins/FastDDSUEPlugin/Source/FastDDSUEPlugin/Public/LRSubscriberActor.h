// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma warning(disable : 4668)
#pragma warning(disable : 4582)
#pragma warning(disable : 4265)
#pragma warning(disable : 4800)

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LRSubscriberActor.generated.h"

UCLASS()
class FASTDDSUEPLUGIN_API ALRSubscriberActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALRSubscriberActor();

	virtual ~ALRSubscriberActor() override;

	bool init();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


	
	eprosima::fastdds::dds::DomainParticipant* participant_;
	eprosima::fastdds::dds::Subscriber* subscriber_;
	eprosima::fastdds::dds::Topic* topic_;
	eprosima::fastdds::dds::DataReader* reader_;
	eprosima::fastdds::dds::TypeSupport type_;

	eprosima::fastdds::dds::DataReaderQos rqos;
	eprosima::fastdds::dds::DomainParticipantQos pqos;
	
	class SubListener : public eprosima::fastdds::dds::DataReaderListener
	{
	public:

		SubListener() = default;

		~SubListener() override = default;

		void on_data_available(
				eprosima::fastdds::dds::DataReader* reader) override;

		void on_subscription_matched(
				eprosima::fastdds::dds::DataReader* reader,
				const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;
		
		uint32_t samples = 0;
		bool matched = false;
		FString getStr;
		AGameModeBase* WGameModeBase;
	}
	listener_;
};
