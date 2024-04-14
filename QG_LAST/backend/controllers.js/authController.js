// controllers/authController.js

// 导入所需的模块
const User = require('../models/User');

// 模拟数据库中的用户数据
let users = [];

// 注册新用户
exports.registerUser = (req, res) => {
    const { username, password } = req.body;
    // 检查用户是否已存在
    const existingUser = users.find(user => user.username === username);
    if (existingUser) {
        res.status(400).json({ message: 'User already exists' });
    } else {
        // 创建新用户并保存到模拟数据库中
        const newUser = new User(username, password);
        users.push(newUser);
        res.status(201).json({ message: 'User registered successfully' });
    }
};

// 用户登录
exports.loginUser = (req, res) => {
    const { username, password } = req.body;
    // 检查用户是否存在并验证密码
    const user = users.find(user => user.username === username && user.password === password);
    if (user) {
        res.status(200).json({ message: 'Login successful' });
    } else {
        res.status(401).json({ message: 'Invalid username or password' });
    }
};
