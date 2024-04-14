// routes/authRoutes.js
const url = require('url');



const { registerUser, loginUser } = require('../controllers/authController');

function handleRoute(req, res) {
  //注意，这里使用了对象属性的重命名，将 req.url 重命名为 reqUrl，避免和引入的 url 模块重名。
    const { method, url: reqUrl } = req;
    const parsedUrl = url.parse(reqUrl, true);
  // 设置响应头，允许跨域请求
  res.setHeader('Access-Control-Allow-Origin', 'http://127.0.0.1:5500');
  // 允许的请求头
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
 console.log(method,parsedUrl.pathname);
 //跨域请求  浏览器会发送一个 OPTIONS 请求作为预检请求（preflight request）
 if(method==='OPTIONS')
 {
  res.end();
 }
   if (method === 'GET' && parsedUrl.pathname === '/api/auth/login') {
        // 在这里处理登录逻辑
        // 如果登录成功，可以发送一个成功的响应
        res.end('Login successful');
        console.log('Login successful'); // 在控制台输出登录成功的信息
    } 
}

module.exports = handleRoute;
