// 引入 http 模块
const http = require('http');
const url = require('url');
const handleRoute = require('./routes/authRoutes')

// 创建服务器
const server = http.createServer((req, res) => {
  handleRoute(req,res);
});

// 监听端口
const port = 3000;
server.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});
