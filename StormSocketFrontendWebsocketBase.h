#pragma once

#include "StormSocketFrontendBase.h"
#include "StormSocketConnectionWebsocket.h"
#include "StormWebsocketMessageWriter.h"
#include "StormWebsocketMessageReader.h"

namespace StormSockets
{
  class StormSocketFrontendWebsocketBase : public StormSocketFrontendBase
  {
  protected:

    bool m_UseMasking;
    StormSocketContinuationMode::Index m_ContinuationMode;

  public:

    StormSocketFrontendWebsocketBase(const StormSocketFrontendWebsocketSettings & settings, StormSocketBackend * backend);

    StormWebsocketMessageWriter CreateOutgoingPacket(StormSocketWebsocketDataType::Index type, bool final);
    void FinalizeOutgoingPacket(StormWebsocketMessageWriter & writer);
    void FreeIncomingPacket(StormWebsocketMessageReader & reader);

  protected:

    StormWebsocketMessageWriter CreateOutgoingPacket(StormWebsocketOp::Index mode, bool final);
    bool ProcessWebsocketData(StormSocketConnectionBase & connection, StormWebsocketConnectionBase & ws_connection, StormSocketConnectionId connection_id);

    void CleanupConnection(StormWebsocketConnectionBase & ws_connection);
  };
}
