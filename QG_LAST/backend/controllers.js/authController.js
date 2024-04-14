// controllers/authController.js

// 导入所需的模块
const User = require('../models/User');

// 数据库中的用户数据

let users = require('../../database/seeds/usersSeed')
console.log(users);
// getUsers.then(users => {
// users.map(user=>console.log(user.username,user.password,user.usertype))
// }).catch(err => {
//   console.error(err);
// });

// 注册新用户
function registerUser  (req, res)  {
  let body = '';
  req.on('data',(chunk)=>{
    body += chunk.toString();
  });
  req.on('end',()=>{
        const { username, password,usertype } = JSON.parse(body);
     // 检查用户是否已存在
    const existingUser = users.find(user => user.username === username);
    if (existingUser) {
            res.writeHead(201, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify({ message: '该用户已存在噢' }));           
    } else {
        // 创建新用户并保存到模拟数据库中
        const newUser = new User(username, password,usertype);
        users.push(newUser);
        res.writeHead(202,{'Content-Type':'application/json'})
        res.end(JSON.stringify({message:`注册成功,欢迎您${username}`}))
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
        // 检查用户是否存在并验证密码
        const user = users.find(user => user.username === username && user.password === password && user.usertype === usertype);
        const userExist = users.find(user=>user.username===username);
        if (user) {
            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify({ message: `登录成功，欢迎回来${username}` }));
        } else {
          if(userExist){
            res.writeHead(201, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify({ message: '用户存在，密码错误' }));            
          }
          else{ res.writeHead(202, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify({ message: '该用户还未注册，请先完成注册' }));}
        }
    });
};
module.exports = {loginUser,registerUser}