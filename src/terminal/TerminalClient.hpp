#ifndef __ET_TERMINAL_CLIENT__
#define __ET_TERMINAL_CLIENT__

#include "ClientConnection.hpp"
#include "CryptoHandler.hpp"
#include "Headers.hpp"
#include "LogHandler.hpp"
#include "ParseConfigFile.hpp"
#include "PortForwardHandler.hpp"
#include "PortForwardSourceHandler.hpp"
#include "RawSocketUtils.hpp"
#include "ServerConnection.hpp"
#include "SshSetupHandler.hpp"
#include "TcpSocketHandler.hpp"

#include <errno.h>
#include <pwd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>

#include "ETerminal.pb.h"

using namespace et;
namespace google {}
namespace gflags {}
using namespace google;
using namespace gflags;

class TerminalClient {
 public:
  // TerminalClient(shared_ptr<SocketHandler> socketHandler,  SocketEndpoint
  // socketEndpoint, string idpasskeypair)
  TerminalClient(std::shared_ptr<SocketHandler> _socketHandler,
                 const SocketEndpoint& _socketEndpoint, const string& id,
                 const string& passkey);
  void setUpTunnel(const string& tunnels);
  void setUpReverseTunnels(const string& reverseTunnels);
  void handleWindowChanged(winsize* win);
  // void handlePfwPacket(char packetType);
  void run(const string& command, const string& tunnels,
           const string& reverseTunnels);

 protected:
  shared_ptr<ClientConnection> globalClient;
  shared_ptr<PortForwardHandler> portForwardHandler;
  termios terminal_backup;
};
#endif  // __ET_TERMINAL_CLIENT__