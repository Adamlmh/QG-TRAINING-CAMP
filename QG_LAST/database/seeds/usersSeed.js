// 导入mysql模块
import mysql from 'mysql';

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

export default getUsersFromDatabase;
