#include "verifygrpcclient.h"
#include "configmanager.h"

VerifyGrpcClient::VerifyGrpcClient() {
    ConfigManager& config = ConfigManager::getInstance();
    std::string host = config["VerifyServer"]["host"];
    std::string port = config["VerifyServer"]["port"];
    rpc_pool_ = std::make_unique<RPCConnectPool>(5, host, port);
}


GetVerifyRsp VerifyGrpcClient::getVerifyCode(const std::string& email) {
    GetVerifyReq request;
    GetVerifyRsp response;
    ClientContext context;
    request.set_email(email);
    auto stub = rpc_pool_->getStub();
    Status status = stub->GetVerifyCode(&context, request, &response);
    if (!status.ok()) {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
        response.set_error(static_cast<int32_t>(ErrorCodes::RPC_ERROR));
    }
    rpc_pool_->returnStub(std::move(stub));
    return response;
}