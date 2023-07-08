// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma warning(disable : 4668)
#pragma warning(disable : 4582)
#pragma warning(disable : 4265)


#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "MyInfo.generated.h"

/**
 * 
 */
UCLASS()
class FASTDDSTEST_API AMyInfo : public AInfo
{
	GENERATED_BODY()

public:
	AMyInfo();

	//!Initialize
	bool init();

	//!Publish a sample
	bool publish(
		bool waitForListener = true);

	//!Run for number samples
	void run(
		uint32_t number,
		uint32_t sleep);

	void runInTick(uint32_t samples);

	uint32_t tickCounts = 0;
	uint32_t tickSamples = 1;
	bool initialed = false;

private:
	FString QOS_URL = FString("Connext/helloworld_example_type_profile.xml");
	FString TYPE_NAME = FString("HelloWorld");
	eprosima::fastrtps::types::DynamicData_ptr m_Hello;
	eprosima::fastdds::dds::DomainParticipant* mp_participant;
	eprosima::fastdds::dds::Publisher* mp_publisher;
	eprosima::fastdds::dds::Topic* topic_;
	eprosima::fastdds::dds::DataWriter* writer_;
	bool stop;

	class PubListener : public eprosima::fastdds::dds::DataWriterListener
	{
	public:
		PubListener()
			: n_matched(0)
			  , firstConnected(false)
		{
		}

		~PubListener() override
		{
		}

		void on_publication_matched(
			eprosima::fastdds::dds::DataWriter* writer,
			const eprosima::fastdds::dds::PublicationMatchedStatus& info) override;
		int n_matched;

		bool firstConnected;
	} m_listener;

	void runThread(
		uint32_t number,
		uint32_t sleep);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;
};