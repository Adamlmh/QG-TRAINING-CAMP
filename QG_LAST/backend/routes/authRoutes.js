// routes/authRoutes.js
import url from 'url';
import {loginUser,registerUser} from '../controllers/authController.js'
function handleRoute(req, res) {
  const { method, url: reqUrl } = req;
  const parsedUrl = url.parse(reqUrl, true);
  // 设置响应头，允许跨域请求
  res.setHeader("Access-Control-Allow-Origin", "http://127.0.0.1:5500");
  // 允许的请求头
  res.setHeader("Access-Control-Allow-Headers", "Content-Type");
  //跨域请求  浏览器会发送一个 OPTIONS 请求作为预检请求（preflight request）
  if (method === "OPTIONS") {
    res.end();
  }
  if (method === "POST" && parsedUrl.pathname === "/api/auth/login") {
    loginUser(req, res);
  } 
  else if (method === "POST" && parsedUrl.pathname === "/api/auth/register") {
       registerUser(req, res);
  } 
  // else {
  //   res.writeHead(404, { "Content-Type": "text/plain" });
  //   res.end("Not Found");
  // }
}
export default handleRoute;

