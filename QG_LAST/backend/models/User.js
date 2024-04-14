// models/User.js

// 用户模型
class User {
    constructor(username, password,usertype) {
        this.username = username;
        this.password = password;
        this.usertype = usertype;
    }
}

module.exports = User;
