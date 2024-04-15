// 导入mysql模块
const mysql = require('mysql');

// 建立联系
const db = mysql.createPool({
  host: '127.0.0.1',
  user: 'root',
  password: 'admin123',
  database: 'qg',
});

// 查询users表中所有数据
const sqlStr = 'SELECT * FROM users';

// 定义异步函数来执行数据库查询
async function getUsersFromDatabase() {
  return new Promise((resolve, reject) => {
    db.query(sqlStr, (err, results) => {
      if (err) {
        reject(err);
      } else {
        resolve(results);
      }
    });
  });
}

// 调用异步函数，获取查询结果后再导出
getUsersFromDatabase().then(users => {

//APP.js
// 引入 http 模块
const http = require('http');
const url = require('url');

// 创建服务器
const server = http.createServer((req, res) => {
  handleRoute(req,res);
});

// 监听端口
const port = 3000;
server.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});

// routes/authRoutes.js
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
}


 // controllers/authController.js

// 导入所需的模块
const User = require('../models/User');
// 数据库中的用户数据
// 注册新用户
function registerUser  (req, res)  {
  let body = '';
  req.on('data',(chunk)=>{
    body += chunk.toString();
  });
  req.on('end',()=>{
        const { username, password,usertype } = JSON.parse(body);
     // 检查用户是否已存在
    const existingUser = users.find(user => user.username === username&&user.usertype === usertype);
    let status
    if(usertype===1){
     status  = '用户'
    }else{
status = '管理员'
    }
    if (existingUser) {
            res.writeHead(401, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify({ message: `该${status}已存在噢` }));           
    } else {
        // 创建新用户并保存到数据库中
        const newUser = new User(username, password,usertype);
        //定义执行的SQL语句
        const sqlStr = 'insert into users set ?'
        db.query(sqlStr,newUser,(err,results)=>{
          if(err) return console.log(err.message);
          if(results.affectedRows === 1){
            console.log('插入成功');
          }
        })
        users.push(newUser);
        res.writeHead(202,{'Content-Type':'application/json'})
        res.end(JSON.stringify({message:`注册成功,欢迎尊敬的${status}：${username}`}))
    }       
  })
};

// 用户登录
function loginUser (req, res) {
    let body = '';
    req.on('data', (chunk) => {
      // 在 HTTP 请求的场景中，chunk 参数通常是一个 Buffer 对象，代表了请求体数据的一部分。通过调用 toString() 方法，将这部分数据转换为字符串
        body += chunk.toString();
    });
    req.on('end', () => {
        const { username, password,usertype } = JSON.parse(body);
        let status;
        if(usertype==='1'){
     status = '用户'
    }else{
status = '管理员'
    }
    console.log(status,username,password,usertype);
        // 检查用户是否存在并验证密码
        const user = users.find(user => user.username === username && user.password === password && user.usertype === usertype);
        const userExist = users.find(user=>user.username===username&&user.usertype === usertype);
        if (user) {
            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify({ message: `登录成功，欢迎回来尊敬的${status}：${username}` }));
        } else {
          if(userExist){
            res.writeHead(401, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify({ message: `${status}存在，密码错误` }));            
          }
          else{ res.writeHead(402, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify({ message: `该${status}还未注册，请先完成注册` }));}
        }
    });
};

console.log(users);
}).catch(err => {
  console.error(err.message);
});
