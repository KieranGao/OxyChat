#ifndef STATUSGRPCCLIENT_H
#define STATUSGRPCCLIENT_H

#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h" 
#include "global.h"
#include "singleton.h"
#include "rpcconnectpool.h"
#include "configmanager.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::StatusService;

class StatusGrpcClient : public Singleton<StatusGrpcClient> {
    friend class Singleton<StatusGrpcClient>;
public:
    GetChatServerRsp getChatServer(int uid);
private:
    std::unique_ptr<StatusConnectPool> rpc_pool_;
    StatusGrpcClient();
};




#endif /* STATUSGRPCCLIENT_H */
