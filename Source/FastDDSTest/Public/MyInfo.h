// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma warning(disable : 4668)
#pragma warning(disable : 4582)
#pragma warning(disable : 4265)


#include "JsonStrSubscriber.h"

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

	UPROPERTY()
	UJsonStrSubscriber* mysub;

	UPROPERTY()
	UJsonStrSubscriber* cppSub;


protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
