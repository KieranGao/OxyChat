#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h" 
#include "global.h"
#include "singleton.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using message::GetVerifyReq;
using message::GetVerifyRsp;
using message::VerifyService;

class VerifyGrpcClient : public Singleton<VerifyGrpcClient> {
    friend class Singleton<VerifyGrpcClient>;
public:
    GetVerifyRsp getVerifyCode(const std::string& email) {
        GetVerifyReq request;
        GetVerifyRsp response;
        ClientContext context;
        request.set_email(email);
        
        Status status = stub_->GetVerifyCode(&context, request, &response);
        if (!status.ok()) {
            std::cerr << "RPC failed: " << status.error_message() << std::endl;
            response.set_error(static_cast<int32_t>(ErrorCodes::RPC_ERROR));
        }
        return response;
    }
private:
    VerifyGrpcClient() {
        std::shared_ptr<Channel> channel = grpc::CreateChannel("localhost:50051", 
            grpc::InsecureChannelCredentials());
        stub_ = VerifyService::NewStub(channel);
    }
    std::unique_ptr<VerifyService::Stub> stub_;
};
