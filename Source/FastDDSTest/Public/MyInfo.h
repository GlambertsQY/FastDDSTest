// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma warning(disable : 4668)
#pragma warning(disable : 4582)
#pragma warning(disable : 4265)


#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

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


private:



protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;
};
