// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <fastdds/dds/domain/DomainParticipant.hpp>
// #include <fastdds/dds/subscriber/DataReader.hpp>

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

private:
	eprosima::fastdds::dds::DomainParticipant* participant_;
};
