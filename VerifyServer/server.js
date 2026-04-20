const grpc = require('@grpc/grpc-js');
const emailModule = require('./email');
const const_module = require('./const');
const redis_module = require('./redis');
const { messageProto: message_proto } = require('./proto');

// call = gprcrequest
// callback = gprcresponse
async function GetVerifyCode(call, callback) {
    console.log("email is ", call.request.email)
    try{
        let redis_res = await redis_module.GetRedis(const_module.code_prefix+call.request.email);
        console.log("redis_res is ", redis_res);
        let uniqueId = redis_res;
        if(redis_res == null) {
            const {v4: uuidv4} = await import('uuid');
            uniqueId = uuidv4();
            if(uniqueId.length > 4) {
                uniqueId = uniqueId.substring(0,4);
            } 
            let set_res = await redis_module.SetRedisExpire(const_module.code_prefix+call.request.email, uniqueId, 180);
            if(!set_res) {
                callback(null, {
                    email : call.request.email,
                    error : const_module.Errors.RedisError
                });
                return;
            }
        }
        console.log("uniqueId is ", uniqueId)
        let text_str =  'Your verify code is '+ uniqueId +' Please complete registration within three minutes'
        //发送邮件
        let mailOptions = {
            from: 'a2556469280@163.com',
            to: call.request.email,
            subject: 'Verify Code',
            text: text_str,
        };
        // 因为 sendmail函数是一个异步函数，所以需要使用await等待它的结果，才能保证在发送邮件完成后再进行下一步操作
        // await转异步函数为同步，等待promise对象的结果
        let send_res = await emailModule.SendMail(mailOptions);
        console.log("send res is ", send_res)

        callback(null, { email:  call.request.email,
            error:const_module.Errors.Success
        }); 
    }catch(error){
        console.log("catch error is ", error)

        callback(null, { email:  call.request.email,
            error:const_module.Errors.Exception
        }); 
    }

}

function main() {
    var server = new grpc.Server();
    server.addService(message_proto.VerifyService.service, { GetVerifyCode: GetVerifyCode});

    server.bindAsync('127.0.0.1:50051', grpc.ServerCredentials.createInsecure(), () => {
        // server.start()
        console.log('grpc server started')        
    });
}

main() 