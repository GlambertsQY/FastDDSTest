// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include <fastdds/dds/domain/DomainParticipant.hpp>
// #include <fastdds/dds/subscriber/DataReader.hpp>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class FASTDDSTEST_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	// eprosima::fastdds::dds::DomainParticipant* participant_;
	// eprosima::fastdds::dds::Subscriber* subscriber_;
	// eprosima::fastdds::dds::Topic* topic_;
	// eprosima::fastdds::dds::DataReader* reader_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
