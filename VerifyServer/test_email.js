const emailModule = require('./email');

async function testEmail() {
    console.log('开始测试邮件发送...');

    const mailOptions = {
        from: 'a2556469280@163.com',
        to: 'Gazy0906@outlook.com',
        subject: '测试邮件',
        text: '这是一封测试邮件，如果您收到此邮件，说明SMTP配置正确。',
    };

    try {
        const result = await emailModule.SendMail(mailOptions);
        console.log('邮件发送成功！结果：', result);
    } catch (error) {
        console.error('邮件发送失败：', error);
    }
}

testEmail();
