
//封装回调函数解决require同步和请求数据异步的矛盾
const getUser = (callback) =>{
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

// 执行数据库查询
    db.query(sqlStr, (error, results) => {
      if (error) {
        console.log("ERROR!!!");
        callback(error,null);
      } else {
        callback(null,results);
      }
    });
  }

  module.exports = getUser








