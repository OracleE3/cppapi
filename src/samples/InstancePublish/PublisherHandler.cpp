//******************************************************************************************************
//  PublisherHandler.cpp - Gbtc
//
//  Copyright � 2019, Grid Protection Alliance.  All Rights Reserved.
//
//  Licensed to the Grid Protection Alliance (GPA) under one or more contributor license agreements. See
//  the NOTICE file distributed with this work for additional information regarding copyright ownership.
//  The GPA licenses this file to you under the MIT License (MIT), the "License"; you may not use this
//  file except in compliance with the License. You may obtain a copy of the License at:
//
//      http://opensource.org/licenses/MIT
//
//  Unless agreed to in writing, the subject software distributed under the License is distributed on an
//  "AS-IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. Refer to the
//  License for the specific language governing permissions and limitations.
//
//  Code Modification History:
//  ----------------------------------------------------------------------------------------------------
//  03/27/2019 - J. Ritchie Carroll
//       Generated original version of source code.
//
//******************************************************************************************************

#include "PublisherHandler.h"

using namespace std;
using namespace sttp;
using namespace sttp::transport;

Mutex PublisherHandler::s_coutLock {};

PublisherHandler::PublisherHandler(string name) : 
    PublisherInstance(),
    m_name(std::move(name)),
    m_processCount(0L),
    m_publishTimer(Timer::NullPtr),
    m_metadataVersion(0)
{
}

void PublisherHandler::StatusMessage(const string& message)
{
    // TODO: Make sure these messages get logged to an appropriate location

    // Calls can come from multiple threads, so we impose a simple lock before write to console
    ScopeLock lock(s_coutLock);

    // For now, we just the base class to display to console:
    PublisherInstance::StatusMessage("[" + m_name + "] " + message);
}

void PublisherHandler::ErrorMessage(const string& message)
{
    // TODO: Make sure these messages get logged to an appropriate location

    // Calls can come from multiple threads, so we impose a simple lock before write to console
    ScopeLock lock(s_coutLock);

    // For now, we just the base class to display to console:
    PublisherInstance::ErrorMessage("[" + m_name + "] " + message);
}

void PublisherHandler::ClientConnected(const SubscriberConnectionPtr& connection)
{
    StatusMessage("Client \"" + connection->GetConnectionID() + "\" with subscriber ID " + ToString(connection->GetSubscriberID()) + " connected...\n\n");
}

void PublisherHandler::ClientDisconnected(const SubscriberConnectionPtr& connection)
{
    StatusMessage("Client \"" + connection->GetConnectionID() + "\" with subscriber ID " + ToString(connection->GetSubscriberID()) + " disconnected...\n\n");
}

MeasurementMetadataPtr NewMetadata(SignalKind kind, string id, string tag, string acronym, uint16_t index, uint16_t src_index, datetime_t timestamp)
{
    MeasurementMetadataPtr meta = NewSharedPtr<MeasurementMetadata>();
    meta->ID = id;
    meta->PointTag = tag;
    meta->SignalID = NewGuid();
    meta->DeviceAcronym = acronym;
    meta->Reference.Acronym = acronym;
    meta->Reference.Kind = kind;
    meta->Reference.Index = index;
    meta->PhasorSourceIndex = src_index;
    meta->UpdatedOn = timestamp;
    return meta;
}

void PublisherHandler::DefineMetadata()
{
    // This sample just generates random Guid measurement and device identifiers - for a production system,
    // these Guid values would need to persist between runs defining a permanent association between the
    // defined metadata and the identifier...

    DeviceMetadataPtr device1Metadata = NewSharedPtr<DeviceMetadata>();
    const datetime_t timestamp = UtcNow();

    // Add a device
    device1Metadata->Name = "Test PMU";
    device1Metadata->Acronym = ToUpper(Replace(device1Metadata->Name, " ", "", false));
    device1Metadata->UniqueID = NewGuid();
    device1Metadata->Longitude = 300;
    device1Metadata->Latitude = 200;
    device1Metadata->FramesPerSecond = 30;
    device1Metadata->ProtocolName = "STTP";
    device1Metadata->UpdatedOn = timestamp;
    StatusMessage(
        "\nNew Device: " +
        ToString(device1Metadata->Name) + " " +
        ToString(device1Metadata->Acronym) + " " +
        ToString(device1Metadata->UniqueID) + " " +
        "\n"
    );

    m_deviceMetadata.emplace_back(device1Metadata);

    const string& pointTagPrefix = device1Metadata->Acronym + ".";
    const string& measurementSource = "PPA:";
    int runtimeIndex = 1;

    // for (int i = 0; i < 4096; ++i)
    // {
    //     SignalKind kind = SignalKind::Unknown;
    //     string prefix = "";
    //     switch (i % 4)
    //     {
    //         case 0:
    //             // Add a frequency measurement
    //             kind = SignalKind::Frequency;
    //             prefix = pointTagPrefix + "FREQ";
    //             break;
    //         case 1:
    //             // Add a dF/dt measurement
    //             kind = SignalKind::DfDt;
    //             prefix = pointTagPrefix + "DFDT";
    //             break;
    //         case 2:
    //             // Add a phase angle measurement
    //             kind = SignalKind::Angle;
    //             prefix = pointTagPrefix + "VPHA";
    //             break;
    //         case 3:
    //             // Add a phase magnitude measurement
    //             kind = SignalKind::Magnitude;
    //             prefix = pointTagPrefix + "VPHM";
    //             break;
    //     }
    //     m_measurementMetadata.emplace_back(NewMetadata(
    //         kind,
    //         measurementSource + ToString(i),
    //         prefix,
    //         device1Metadata->Acronym,
    //         i, i,
    //         timestamp
    //     ));
    // }
    m_measurementMetadata.emplace_back(NewMetadata(
        SignalKind::Frequency,
        measurementSource + ToString(runtimeIndex++),
        pointTagPrefix + "FREQ",
        device1Metadata->Acronym,
        0, 0,
        timestamp
    ));
    m_measurementMetadata.emplace_back(NewMetadata(
        SignalKind::DfDt,
        measurementSource + ToString(runtimeIndex++),
        pointTagPrefix + "DFDT",
        device1Metadata->Acronym,
        0, 0,
        timestamp
    ));
    m_measurementMetadata.emplace_back(NewMetadata(
        SignalKind::Angle,
        measurementSource + ToString(runtimeIndex++),
        pointTagPrefix + "VPHA",
        device1Metadata->Acronym,
        1, 1,
        timestamp
    ));
    m_measurementMetadata.emplace_back(NewMetadata(
        SignalKind::Magnitude,
        measurementSource + ToString(runtimeIndex++),
        pointTagPrefix + "VPHM",
        device1Metadata->Acronym,
        1, 1,
        timestamp
    ));

    // Add a phasor
    PhasorMetadataPtr phasor1Metadata = NewSharedPtr<PhasorMetadata>();
    phasor1Metadata->DeviceAcronym = device1Metadata->Acronym;
    phasor1Metadata->Label = device1Metadata->Name + " Voltage Phasor";
    phasor1Metadata->Type = "V";      // Voltage phasor
    phasor1Metadata->Phase = "+";     // Positive sequence
    phasor1Metadata->SourceIndex = 1; // Phasor number 1
    phasor1Metadata->UpdatedOn = timestamp;

    m_phasorMetadata.emplace_back(phasor1Metadata);

    m_metadataVersion++;

    // Pass meta-data to publisher instance for proper conditioning
    PublisherInstance::DefineMetadata(m_deviceMetadata, m_measurementMetadata, m_phasorMetadata, m_metadataVersion);
}

bool PublisherHandler::Start(uint16_t port, bool ipV6)
{
    if (!PublisherInstance::Start(port, ipV6))
        return false;

    static float64_t randMax = static_cast<float64_t>(RAND_MAX);
    static constexpr uint64_t interval = 1000;

    const int32_t maxConnections = GetMaximumAllowedConnections();
    StatusMessage("\nListening on port: " + ToString(GetPort()) + ", max connections = " + (maxConnections == -1 ? "unlimited" : ToString(maxConnections)) + "...\n");

    // Setup meta-data
    DefineMetadata();

    // Setup data publication timer - for this publishing sample we send
    // data type reasonable random values every 33 milliseconds
    m_publishTimer = NewSharedPtr<Timer>(33, [this](const TimerPtr&, void*)
    {
        // If metadata can change, the following integer should not be static:
        static uint32_t count = ConvertUInt32(m_measurementMetadata.size());
        const int64_t timestamp = RoundToSubsecondDistribution(ToTicks(UtcNow()), 30);
        vector<MeasurementPtr> measurements;

        size_t totalMeasurements = GetTotalMeasurementsSent();
        StatusMessage(
            "Creating new set of " +
            to_string(count) +
            " measurements - total published " +
            to_string(totalMeasurements)
        );

        measurements.reserve(count);

        // Create new measurement values for publication
        for (size_t i = 0; i < count; i++)
        {
            const MeasurementMetadataPtr metadata = m_measurementMetadata[i];
            MeasurementPtr measurement = NewSharedPtr<Measurement>();

            measurement->SignalID = metadata->SignalID;
            measurement->Timestamp = timestamp;

            const float64_t randFraction = rand() / randMax;
            const float64_t sign = randFraction > 0.5 ? 1.0 : -1.0;
            float64_t value;

            switch (metadata->Reference.Kind)
            {
                case SignalKind::Frequency:
                    value = 60.0 + sign * randFraction * 0.1;
                    break;
                case SignalKind::DfDt:
                    value = sign * randFraction * 2;
                    break;
                case SignalKind::Magnitude:
                    value = 500 + sign * randFraction * 50;
                    break;
                case SignalKind::Angle:
                    value = sign * randFraction * 180;
                    break;
                default:
                    value = sign * randFraction * UInt32::MaxValue;
                    break;
            }

            measurement->Value = value;

            measurements.push_back(measurement);
        }

        // Publish measurements
        PublishMeasurements(measurements);

        // Display a processing message every few seconds
        const bool showMessage = m_processCount + count >= (m_processCount / interval + 1) * interval && GetTotalMeasurementsSent() > 0;
        m_processCount += count;

        // if (showMessage)
            StatusMessage(ToString(GetTotalMeasurementsSent()) + " measurements published so far...\n");
    },
    true);

    // Start data publication
    m_publishTimer->Start();

    return true;
}

void PublisherHandler::Stop()
{
    PublisherInstance::Stop();

    if (m_publishTimer != nullptr)
        m_publishTimer->Stop();
}
