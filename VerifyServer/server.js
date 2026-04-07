const grpc = require('@grpc/grpc-js');
const emailModule = require('./email');
const const_module = require('./const');
const { messageProto: message_proto } = require('./proto');

// call = gprcrequest
// callback = gprcresponse
async function GetVerifyCode(call, callback) {
    console.log("email is ", call.request.email)
    try{
        const { v4: uuidv4 } = await import('uuid');
        uniqueId = uuidv4();
        console.log("uniqueId is ", uniqueId)
        let text_str =  'Your verify code is'+ uniqueId +' Please complete registration within three minutes'
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
    var server = new grpc.Server()
    server.addService(message_proto.VerifyService.service, { GetVerifyCode
    : GetVerifyCode
    
     })
    server.bindAsync('0.0.0.0:50051', grpc.ServerCredentials.createInsecure(), () => {
        // server.start()
        console.log('grpc server started')        
    })
}

main()