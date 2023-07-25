// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma warning(disable : 4668)
#pragma warning(disable : 4582)
#pragma warning(disable : 4265)


// #include <fastdds/dds/domain/DomainParticipant.hpp>
// #include <fastdds/dds/subscriber/DataReader.hpp>
// #include <fastdds/dds/subscriber/DataReaderListener.hpp>
// #include <fastdds/dds/subscriber/Subscriber.hpp>
// #include "FastDDSUEPlugin/Public/LocationRotationSubscriber.h"
#include "..\..\..\Plugins\FastDDSUEPlugin\Source\FastDDSUEPlugin\Public\JsonStrSubscriber.h"

#include "CoreMinimal.h"
// #include "LRSubscriberActor.h"
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

	UPROPERTY()
	UJsonStrSubscriber* mysub;

	UPROPERTY()
	UJsonStrSubscriber* cppSub;
	 
	// bool init();
	


private:

	// UPROPERTY()
	// UObjectClassTest* mysub;
	// LocationRotationSubscriber mysub;
// 	eprosima::fastdds::dds::DomainParticipant* participant_;
// 	eprosima::fastdds::dds::Subscriber* subscriber_;
// 	eprosima::fastdds::dds::Topic* topic_;
// 	eprosima::fastdds::dds::DataReader* reader_;
// 	eprosima::fastdds::dds::TypeSupport* type_;
//
// 	class SubListener : public eprosima::fastdds::dds::DataReaderListener
// 	{
// 	public:
//
// 		SubListener() = default;
//
// 		~SubListener() override = default;
//
// 		void on_data_available(
// 				eprosima::fastdds::dds::DataReader* reader) override;
//
// 		void on_subscription_matched(
// 				eprosima::fastdds::dds::DataReader* reader,
// 				const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;
//
// 		int matched = 0;
// 		uint32_t samples = 0;
// 	}
// 	listener_;


protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;
};
