# KedayaChat 即时通信系统

KedayaChat 是一个基于 C++/Qt 的桌面即时通信项目，包含 Qt 客户端和多服务后端。项目实现了用户注册、登录、密码重置、好友管理、聊天会话、用户状态路由、邮箱验证码、MySQL 持久化、Redis 缓存以及基于 gRPC 的服务间通信。

## 功能特性

- Qt 桌面客户端：登录、注册、密码重置、联系人列表、聊天窗口
- 网关服务：提供 HTTP 接入和请求转发
- 聊天服务：负责 TCP 会话管理、消息接收与分发
- 状态服务：维护用户在线状态和聊天服务路由
- 验证码服务：基于 Node.js 发送邮箱验证码
- 数据存储：MySQL 保存用户、好友和消息相关数据
- 缓存能力：Redis 保存验证码和在线状态等临时数据
- 服务通信：使用 Protobuf 和 gRPC 完成后端服务间调用

## 技术栈

- 客户端：C++、Qt 5、qmake
- 后端服务：C++、Boost.Asio、gRPC、Protobuf、MySQL Connector/C++、Redis
- 验证码服务：Node.js、gRPC、ioredis、nodemailer
- 数据库：MySQL、Redis

## 项目结构

```text
client/kedayachat/      Qt 桌面客户端
server/GateServer/      网关服务
server/ChatServer/      聊天服务实例 1
server/ChatServer2/     聊天服务实例 2
server/StatusServer/    状态服务
server/VarifyServer/    Node.js 邮箱验证码服务
sql备份/llfc.sql         MySQL 数据库备份脚本
```

## 配置说明

运行配置文件不会提交到 Git，因为其中通常包含数据库密码、Redis 密码和邮箱授权码。

验证码服务可以从示例配置复制本地配置：

```bash
cp server/VarifyServer/config.example.json server/VarifyServer/config.json
```

C++ 后端服务需要在各自服务目录下创建本地 `config.ini`，并根据实际环境填写 MySQL、Redis、服务地址和端口等配置。

## 运行方式

### 启动验证码服务

```bash
cd server/VarifyServer
npm install
npm run serve
```

### 构建后端 C++ 服务

使用 Visual Studio 打开对应解决方案并编译：

- `server/GateServer/GateServer.sln`
- `server/StatusServer/StatusServer.sln`
- `server/ChatServer/ChatServer.sln`
- `server/ChatServer2/ChatServer.sln`

启动后端服务前，需要先准备好 MySQL 和 Redis 环境。

### 构建 Qt 客户端

使用 Qt Creator 打开：

```text
client/kedayachat/kedayachat.pro
```

配置 Qt 5 环境后即可编译并运行客户端。

## 数据库

项目提供 MySQL 备份脚本：

```text
sql备份/llfc.sql
```

可以根据该脚本初始化本地数据库，再在各服务的本地配置文件中填写数据库连接信息。

## 版本管理说明

- `build/`、`bin/`、`x64/`、`.vs/` 等构建产物和 IDE 临时文件已通过 `.gitignore` 排除。
- 真实的 `config.ini` 和 `config.json` 不应提交到仓库。
- `config.example.json` 只保留字段结构，方便其他环境快速配置。
