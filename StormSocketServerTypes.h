#pragma once

#include <StormSockets\StormMessageWriter.h>
#include <StormSockets\StormWebsocketMessageReader.h>
#include <StormSockets\StormHttpResponseReader.h>
#include <StormSockets\StormHttpRequestReader.h>

#include <thread>
#include <algorithm>

namespace StormSockets
{
  namespace StormSocketEventType
  {
    enum Index
    {
      ClientConnected,
      ClientHandShakeCompleted,
      Disconnected,
      Data,
    };
  }

  namespace StormSocketContinuationMode
  {
    enum Index
    {
      Combine,
      DeliverImmediately,
      WaitForCompletion,
    };
  }

  struct StormSocketEventInfo
  {
    StormSocketEventType::Index Type;
    StormSocketConnectionId ConnectionId;

    uint32_t RemoteIP;
    uint16_t RemotePort;

    StormWebsocketMessageReader & GetWebsocketReader() { return *((StormWebsocketMessageReader *)ReaderBuffer); }
    StormHttpResponseReader & GetHttpResponseReader() { return *((StormHttpResponseReader *)ReaderBuffer); }
    StormHttpRequestReader & GetHttpRequestReader() { return *((StormHttpRequestReader *)ReaderBuffer); }

  private:

    uint8_t ReaderBuffer[std::max(std::max(sizeof(StormWebsocketMessageReader), sizeof(StormHttpResponseReader)), sizeof(StormHttpRequestReader))];
  };

  struct StormSocketInitSettings
  {
    int NumIOThreads = std::thread::hardware_concurrency();
    int NumSendThreads = std::thread::hardware_concurrency();
    int MaxConnections = 256;

    int HeapSize = 10 * 1024 * 1024; // 10 megs
    int BlockSize = 4096 - sizeof(StormFixedBlockHandle); // The default page size

    int MaxPendingOutgoingPacketsPerConnection = 32;
    int MaxPendingFreeingPacketsPerConnection = 32;
    int MaxPendingIncomingPacketsPerConnection = 32;
    int MaxSendQueueElements = 32;
  };

  struct StormSocketServerSSLSettings
  {
    const char * CertificateFile = nullptr;
    const char * PrivateKeyFile = nullptr;
  };

  struct StormSocketListenData
  {
    uint16_t Port = 9001;
    const char * LocalInterface = "0.0.0.0";
  };

  struct StormSocketFrontendSettings
  {
    int MessageQueueSize = 128;
    int MaxConnections = 256;
  };

  struct StormSocketFrontendWebsocketSettings : public StormSocketFrontendSettings
  {
    bool UseMasking = false;
    StormSocketContinuationMode::Index ContinuationMode = StormSocketContinuationMode::Combine;
  };

  struct StormSocketFrontendHttpSettings : public StormSocketFrontendSettings
  {

  };

  struct StormSocketClientFrontendHttpSettings : public StormSocketFrontendHttpSettings
  {

  };

  struct StormSocketClientFrontendWebsocketSettings : public StormSocketFrontendWebsocketSettings
  {

  };

  struct StormSocketServerFrontendWebsocketSettings : public StormSocketFrontendWebsocketSettings
  {
    StormSocketServerSSLSettings SSLSettings;
    StormSocketListenData ListenSettings;

    const char * Protocol = nullptr;

    bool UseMasking = false;
    StormSocketContinuationMode::Index ContinuationMode = StormSocketContinuationMode::Combine;
  };

  struct StormSocketServerFrontendHttpSettings : public StormSocketFrontendHttpSettings
  {
    StormSocketServerSSLSettings SSLSettings;
    StormSocketListenData ListenSettings;
  };
}

