// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInfo.h"

#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>

#include <fastrtps/types/DynamicDataFactory.h>

#include <fastrtps/xmlparser/XMLProfileManager.h>

#include <thread>

using namespace eprosima::fastdds::dds;

AMyInfo::AMyInfo()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyInfo::PubListener::on_publication_matched(eprosima::fastdds::dds::DataWriter* writer,
                                                  const eprosima::fastdds::dds::PublicationMatchedStatus& info)
{
	if (info.current_count_change == 1)
	{
		n_matched = info.total_count;
		firstConnected = true;
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,
		                                 "Publisher matched", true);
	}
	else if (info.current_count_change == -1)
	{
		n_matched = info.total_count;
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,
		                                 "Publisher unmatched", true);
	}
	else
	{
		FString s = FString::FromInt(info.current_count_change) +
			" is not a valid value for PublicationMatchedStatus current count change";
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, s, true);
	}
}

bool AMyInfo::init()
{
	mp_participant = nullptr;
	mp_publisher = nullptr;
	FString xmlFile = FPaths::Combine(FPaths::ProjectContentDir(), QOS_URL);
	if (eprosima::fastrtps::xmlparser::XMLP_ret::XML_OK !=
		eprosima::fastrtps::xmlparser::XMLProfileManager::loadXMLFile(TCHAR_TO_UTF8(*xmlFile)))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,
		                                 "Cannot open XML file \"helloworld_example_type_profile.xml\"."
		                                 " Please, run the publisher from the folder "
		                                 "that contatins this XML file.", true);
		return false;
	}

	eprosima::fastrtps::types::DynamicType_ptr dyn_type =
		eprosima::fastrtps::xmlparser::XMLProfileManager::getDynamicTypeByName(TCHAR_TO_UTF8(*TYPE_NAME))->build();
	TypeSupport m_type(new eprosima::fastrtps::types::DynamicPubSubType(dyn_type));
	m_Hello = eprosima::fastrtps::types::DynamicDataFactory::get_instance()->create_data(dyn_type);

	m_Hello->set_string_value("Hello DDS Dynamic World", 0);
	m_Hello->set_uint32_value(0, 1);
	eprosima::fastrtps::types::DynamicData* array = m_Hello->loan_value(2);
	array->set_uint32_value(10, array->get_array_index({0, 0}));
	array->set_uint32_value(20, array->get_array_index({1, 0}));
	array->set_uint32_value(30, array->get_array_index({2, 0}));
	array->set_uint32_value(40, array->get_array_index({3, 0}));
	array->set_uint32_value(50, array->get_array_index({4, 0}));
	array->set_uint32_value(60, array->get_array_index({0, 1}));
	array->set_uint32_value(70, array->get_array_index({1, 1}));
	array->set_uint32_value(80, array->get_array_index({2, 1}));
	array->set_uint32_value(90, array->get_array_index({3, 1}));
	array->set_uint32_value(100, array->get_array_index({4, 1}));
	m_Hello->return_loaned_value(array);

	DomainParticipantQos pqos;
	pqos.name("Participant_pub");
	mp_participant = DomainParticipantFactory::get_instance()->create_participant(0, pqos);

	if (mp_participant == nullptr)
	{
		return false;
	}

	//REGISTER THE TYPE
	m_type.get()->auto_fill_type_information(false);
	m_type.get()->auto_fill_type_object(true);

	m_type.register_type(mp_participant);

	//CREATE THE PUBLISHER
	mp_publisher = mp_participant->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

	if (mp_publisher == nullptr)
	{
		return false;
	}

	topic_ = mp_participant->create_topic("DDSDynHelloWorldTopic", "HelloWorld", TOPIC_QOS_DEFAULT);

	if (topic_ == nullptr)
	{
		return false;
	}

	// CREATE THE WRITER
	writer_ = mp_publisher->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &m_listener);

	if (writer_ == nullptr)
	{
		return false;
	}

	return true;
}

bool AMyInfo::publish(bool waitForListener)
{
	if (m_listener.firstConnected || !waitForListener || m_listener.n_matched > 0)
	{
		uint32_t index;
		m_Hello->get_uint32_value(index, 1);
		m_Hello->set_uint32_value(index + 1, 1);

		eprosima::fastrtps::types::DynamicData* array = m_Hello->loan_value(2);
		array->set_uint32_value(10 + index, array->get_array_index({0, 0}));
		array->set_uint32_value(20 + index, array->get_array_index({1, 0}));
		array->set_uint32_value(30 + index, array->get_array_index({2, 0}));
		array->set_uint32_value(40 + index, array->get_array_index({3, 0}));
		array->set_uint32_value(50 + index, array->get_array_index({4, 0}));
		array->set_uint32_value(60 + index, array->get_array_index({0, 1}));
		array->set_uint32_value(70 + index, array->get_array_index({1, 1}));
		array->set_uint32_value(80 + index, array->get_array_index({2, 1}));
		array->set_uint32_value(90 + index, array->get_array_index({3, 1}));
		array->set_uint32_value(100 + index, array->get_array_index({4, 1}));
		m_Hello->return_loaned_value(array);

		writer_->write(m_Hello.get());
		return true;
	}
	return false;
}

void AMyInfo::run(uint32_t samples, uint32_t sleep)
{
	stop = false;
	std::thread thread(&AMyInfo::runThread, this, samples, sleep);
	if (samples == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Publisher running. "
		                                 "Please press enter to stop the Publisher at any time.", true);
		stop = true;
	}
	else
	{
		FString s = "Publisher running  " + FString::FromInt(samples) + " samples.";
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, s, true);
	}
	thread.join();
}

void AMyInfo::runInTick(uint32_t samples)
{
	for (uint32_t s = 0; s < samples; ++s)
	{
		if (!publish())
		{
			--s;
		}
		else
		{
			std::string message;
			m_Hello->get_string_value(message, 0);
			uint32_t index;
			m_Hello->get_uint32_value(index, 1);
			std::string aux_array = "[";
			eprosima::fastrtps::types::DynamicData* array = m_Hello->loan_value(2);
			for (uint32_t i = 0; i < 5; ++i)
			{
				aux_array += "[";
				for (uint32_t j = 0; j < 2; ++j)
				{
					uint32_t elem;
					array->get_uint32_value(elem, array->get_array_index({i, j}));
					aux_array += std::to_string(elem) + (j == 1 ? "]" : ", ");
				}
				aux_array += (i == 4 ? "]" : "], ");
			}
			m_Hello->return_loaned_value(array);
			std::cout << "Message: " << message << " with index: " << index
				<< " array: " << aux_array << " SENT" << std::endl;
		}
		// std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
	}
}

void AMyInfo::runThread(uint32_t samples, uint32_t sleep)
{
	if (samples == 0)
	{
		while (!stop)
		{
			if (publish(false))
			{
				std::string message;
				m_Hello->get_string_value(message, 0);
				uint32_t index;
				m_Hello->get_uint32_value(index, 1);
				std::string aux_array = "[";
				eprosima::fastrtps::types::DynamicData* array = m_Hello->loan_value(2);
				for (uint32_t i = 0; i < 5; ++i)
				{
					aux_array += "[";
					for (uint32_t j = 0; j < 2; ++j)
					{
						uint32_t elem;
						array->get_uint32_value(elem, array->get_array_index({i, j}));
						aux_array += std::to_string(elem) + (j == 1 ? "]" : ", ");
					}
					aux_array += (i == 4 ? "]" : "], ");
				}
				m_Hello->return_loaned_value(array);
				std::cout << "Message: " << message << " with index: " << index
					<< " array: " << aux_array << " SENT" << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
		}
	}
	else
	{
		for (uint32_t s = 0; s < samples; ++s)
		{
			if (!publish())
			{
				--s;
			}
			else
			{
				std::string message;
				m_Hello->get_string_value(message, 0);
				uint32_t index;
				m_Hello->get_uint32_value(index, 1);
				std::string aux_array = "[";
				eprosima::fastrtps::types::DynamicData* array = m_Hello->loan_value(2);
				for (uint32_t i = 0; i < 5; ++i)
				{
					aux_array += "[";
					for (uint32_t j = 0; j < 2; ++j)
					{
						uint32_t elem;
						array->get_uint32_value(elem, array->get_array_index({i, j}));
						aux_array += std::to_string(elem) + (j == 1 ? "]" : ", ");
					}
					aux_array += (i == 4 ? "]" : "], ");
				}
				m_Hello->return_loaned_value(array);
				std::cout << "Message: " << message << " with index: " << index
					<< " array: " << aux_array << " SENT" << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
		}
	}
}

void AMyInfo::BeginPlay()
{
	Super::BeginPlay();

	int count = 1;
	int sleep = 100;
	if (init())
	{
		// run(count, sleep);
		initialed = true;
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Initialed and run", true);
	}
}

void AMyInfo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (writer_ != nullptr)
	{
		mp_publisher->delete_datawriter(writer_);
	}
	if (mp_publisher != nullptr)
	{
		mp_participant->delete_publisher(mp_publisher);
	}
	if (topic_ != nullptr)
	{
		mp_participant->delete_topic(topic_);
	}
	if (DomainParticipantFactory::get_instance() != nullptr && mp_participant != nullptr)
	{
		DomainParticipantFactory::get_instance()->delete_participant(mp_participant);	
	}
}

void AMyInfo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (initialed && tickCounts < tickSamples)
	{
		if (!publish())
		{
			--tickCounts;
		}
		else
		{
			std::string message;
			m_Hello->get_string_value(message, 0);
			uint32_t index;
			m_Hello->get_uint32_value(index, 1);
			std::string aux_array = "[";
			eprosima::fastrtps::types::DynamicData* array = m_Hello->loan_value(2);
			for (uint32_t i = 0; i < 5; ++i)
			{
				aux_array += "[";
				for (uint32_t j = 0; j < 2; ++j)
				{
					uint32_t elem;
					array->get_uint32_value(elem, array->get_array_index({i, j}));
					aux_array += std::to_string(elem) + (j == 1 ? "]" : ", ");
				}
				aux_array += (i == 4 ? "]" : "], ");
			}
			m_Hello->return_loaned_value(array);
			std::cout << "Message: " << message << " with index: " << index
				<< " array: " << aux_array << " SENT" << std::endl;
		}
		++tickCounts;
		// std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
	}
}
