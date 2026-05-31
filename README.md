# KedayaChat

KedayaChat is a C++/Qt instant messaging system with a desktop client and a multi-service backend. The project covers account registration, login, friend management, chat sessions, status routing, verification code delivery, MySQL persistence, Redis caching and gRPC-based service communication.

## Features

- Qt desktop client with login, registration, password reset, contact list and chat UI
- Gateway service for HTTP entry points
- Chat services for TCP session management and message dispatch
- Status service for user and server state routing
- Node.js verification service for email verification code delivery
- MySQL schema backup in `sql备份/llfc.sql`
- Redis support for verification codes and online state

## Tech Stack

- Client: C++, Qt 5, qmake
- Backend: C++, Boost.Asio, gRPC, Protobuf, MySQL Connector/C++, Redis
- Verification service: Node.js, gRPC, ioredis, nodemailer
- Database: MySQL, Redis

## Project Structure

```text
client/kedayachat/      Qt desktop client
server/GateServer/      HTTP gateway service
server/ChatServer/      chat service instance 1
server/ChatServer2/     chat service instance 2
server/StatusServer/    status routing service
server/VarifyServer/    Node.js verification service
sql备份/llfc.sql         MySQL schema backup
```

## Configuration

Runtime configuration files are intentionally ignored by Git because they contain database passwords, Redis passwords and email authorization codes.

Create local configuration files from the provided examples:

```bash
cp server/VarifyServer/config.example.json server/VarifyServer/config.json
```

For C++ services, create local `config.ini` files in each service directory and fill in the database, Redis and service address values required by your environment.

## Run

### Verification Service

```bash
cd server/VarifyServer
npm install
npm run serve
```

### C++ Services

Open the corresponding `.sln` files with Visual Studio and build each service:

- `server/GateServer/GateServer.sln`
- `server/StatusServer/StatusServer.sln`
- `server/ChatServer/ChatServer.sln`
- `server/ChatServer2/ChatServer.sln`

Start Redis and MySQL before launching the backend services.

### Qt Client

Open `client/kedayachat/kedayachat.pro` with Qt Creator, configure Qt 5 and build/run the desktop client.

## Notes

- Generated build directories and local binaries are excluded from version control.
- Do not commit real `config.ini` or `config.json` files.
- The SQL file is kept for local database initialization and demonstration.
