#pragma once

#include <enet/enet.h>
#include <thread>
#include <atomic>
#include <glm/glm.hpp>

#include <queue>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <mutex>
#include <condition_variable>

namespace MultiPlayer {

struct PlayerUpdate
{
  uint32_t playerID;
  glm::vec3 position;
  glm::vec3 front;
};

struct S3Task
{
  ENetPeer* peer;
  uint32_t playerID;
};

enum CHANNEL_TYPE
{
  PLAYER_UPDATE = 1

};

class Server
{
public:
  Server();
  ~Server();

  bool Start(int port);
  void Stop();
  void PollLoop();
  bool IsRunning();

private:
  ENetHost* server;
  std::atomic<bool> isRunning;
  std::thread pollThread;
  PlayerUpdate getPlayerUpdateFromEvent(ENetEvent&);
  void broadcastPlayerUpdate(PlayerUpdate);

  std::thread s3Thread;

  // S3 related members
  std::shared_ptr<Aws::S3::S3Client> s3Client;
  Aws::SDKOptions awsOptions;
  std::string bucketName;
  std::queue<S3Task> s3Tasks;
  std::mutex s3Mutex;
  std::condition_variable s3Condition;
};

}
