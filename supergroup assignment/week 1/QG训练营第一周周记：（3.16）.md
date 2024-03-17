# QG训练营第一周周记：（3.16）

- ## 生活随记 

  - ### 💪坚持，进QG！

  - 任务列表

    - 大组作业

      - [x] 实现单链表ADT

      - [x] 实现双向链表ADT

      （创建链表 销毁链表 插入节点 删除节点 遍历链表 打印链表 查找链表）

      1.单链表奇偶调换（例： input: 1 -> 2 -> 3 -> 4 ，output: 2 -> 1 -> 4 -> 3 ）

      2.找到单链表的中点

      3.判断链表是否成环

      4.反转链表（递归和非递归）

    - 小组作业

      - [ ] 学习代码规范
      - [ ] 学习git，markdown
      - [x] 新建仓库推送到git

    - 课外学习

      - [ ] jQury学习
      - [ ] node.js

- ## 一周总结

  + 提交git

    + 1.创建github仓库

    + 2.克隆仓库

      `git clone <repository_url>`

    + 添加文件到Git

      `git add .`

    + 提交文件

      `git commit -m "Add my Typora Markdown file"`

    + 推送到github

      `git push origin master`

  + 销毁链表函数中 需要传入的是二维指针

    + review：函数传参进去的是指针的副本 因此为了要修改指针的内容需要传入指针的指针    
    + &升维 *降维

- ## 存在问题

  - GitHub网络连接问题：

    - 尝试用ping github.com 试探是否为网络层问题 ----请求超时

    - 解决办法：

      - 修改host文件：打开 C:\Windows\System32\drivers\etc\hosts，文件末尾添加如下内容：

        ```#github IP地址
        199.232.69.194 github.global.ssl.fastly.net
        140.82.113.3 github.com
        140.82.112.4 www.github.com
        185.199.108.153 assets-cdn.github.com
        185.199.109.153 assets-cdn.github.com
        185.199.110.153 assets-cdn.github.com
        185.199.111.153 assets-cdn.github.com
        185.199.108.153 documentcloud.github.com
        185.199.109.153 documentcloud.github.com
        185.199.110.153 documentcloud.github.com
        185.199.111.153 documentcloud.github.com
        140.82.114.3 gist.github.com
        185.199.108.153 help.github.com
        185.199.109.153 help.github.com
        185.199.110.153 help.github.com
        185.199.111.153 help.github.com
        140.82.112.9 nodeload.github.com
        199.232.68.133 raw.github.com
        140.82.112.18 status.github.com
        140.82.113.18 training.github.com
        199.232.68.133 raw.githubusercontent.com
        199.232.68.133 user-images.githubusercontent.com
        199.232.68.133 avatars1.githubusercontent.com
        199.232.68.133 avatars2.githubusercontent.com
        199.232.68.133 avatars3.githubusercontent.com
        199.232.68.133 cloud.githubusercontent.com
        140.82.113.6 api.github.com```
        ```

    

- ## 下周规划