#define ENET_IMPLEMENTATION
#include "Server.h"
#include <unistd.h>

int
main()
{
  auto server = MultiPlayer::Server();
  server.Start(1234);
  while(true) {
    sleep(5);
  }
}
