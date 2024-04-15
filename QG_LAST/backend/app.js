// 引入 http 模块
import http from 'http';
import handleRoute from './routes/authRoutes';

// 创建服务器
const server = http.createServer((req, res) => {
  handleRoute(req,res);
});

// 监听端口
const port = 3000;
server.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});
