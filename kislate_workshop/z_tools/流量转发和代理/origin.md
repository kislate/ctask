好的，这是一个比较典型的反向代理或者说端口转发的场景。你需要一个服务端脚本和一个客户端脚本。下面是一个可以实现你需求的 Python 脚本，分为 `server.py` 和 `client.py` 两个文件。  这段代码实现了基础的 socket 转发功能，没有加密和认证。

**请务必注意：**

*   **安全风险：** 这种未加密的转发方式在公网环境中存在安全风险。如果可能，建议使用 SSH 隧道（`ssh -L` 或 `ssh -R`）或 VPN 等更安全的方案。  如果你坚持使用这种方式，请考虑添加 TLS 加密和身份验证。
*   **错误处理：** 代码包含基本的错误处理，但生产环境需要更健壮的错误处理机制。
*   **性能：**  简单的 socket 转发性能有限，高并发场景下可能需要考虑使用更专业的反向代理服务器（如 Nginx、HAProxy）

**文件结构：**

```
/
├── server.py
└── client.py
```

**1. `server.py` (服务端)**

```python
import socket
import threading
import sys

SERVER_HOST = '0.0.0.0'  # 监听所有可用接口
SERVER_PORT = 8080        # 服务端监听端口
TARGET_HOST = '0.0.0.0'    #目标ip地址,这里改成'0.0.0.0'表示不限制代理的网址
TARGET_PORT = 80          #目标端口，比如你要代理网站访问，默认都是80，当然除非特殊的端口
MAX_CONNECTIONS = 10      # 最大连接数
BUFFER_SIZE = 4096

def handle_client(client_socket, client_address):
    """处理单个客户端连接"""
    print(f"接受来自 {client_address} 的连接")
    try:
        # 连接到目标服务器
        target_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        target_socket.connect((TARGET_HOST, TARGET_PORT))
        print(f"连接到目标服务器 {TARGET_HOST}:{TARGET_PORT}")

        # 创建线程函数，用于从客户端转发到目标服务器
        def forward_client_to_target(client_sock, target_sock):
            try:
                while True:
                    data = client_sock.recv(BUFFER_SIZE)
                    if not data:
                        break
                    target_sock.sendall(data)
            except Exception as e:
                print(f"客户端到目标转发错误: {e}")
            finally:
                client_sock.close()
                target_sock.close()
                print(f"客户端 {client_address} 到目标服务器的连接已关闭")
        #创建线程函数，用于从目标服务器转发到客户端
        def forward_target_to_client(client_sock, target_sock):
             try:
                while True:
                    data = target_sock.recv(BUFFER_SIZE)
                    if not data:
                        break;
                    client_sock.sendall(data)
             except Exception as e:
                print(f"目标服务器到客户端转发错误:{e}")
             finally:
                 client_sock.close()
                 target_sock.close()
                 print(f"目标服务器到客户端连接已关闭")
        # 分别启动从客户端到目标，以及从目标到客户端的转发线程
        client_to_target_thread = threading.Thread(target=forward_client_to_target, args=(client_socket, target_socket))
        target_to_client_thread = threading.Thread(target=forward_target_to_client,args=(client_socket, target_socket))
        client_to_target_thread.start()
        target_to_client_thread.start()

        # 等待两个线程结束
        client_to_target_thread.join()
        target_to_client_thread.join()
        
    except Exception as e:
        print(f"处理客户端连接时出错: {e}")
    finally:
        client_socket.close()

def main():
    """服务端主函数"""
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # 允许地址重用
    try:
        server_socket.bind((SERVER_HOST, SERVER_PORT))
        server_socket.listen(MAX_CONNECTIONS)
        print(f"服务端监听在 {SERVER_HOST}:{SERVER_PORT}")

        while True:
            client_socket, client_address = server_socket.accept()
            client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
            client_thread.start()

    except Exception as e:
        print(f"服务端出错: {e}")
    finally:
        server_socket.close()
        print("服务端关闭")

if __name__ == "__main__":
    main()
```

**2. `client.py` (客户端)**

```python
import socket
import threading
import sys

SERVER_HOST = 'your_server_ip' # 服务端IP地址
SERVER_PORT = 8080              # 服务端监听端口
LOCAL_HOST = '127.0.0.1'        # 本地监听地址
LOCAL_PORT = 9090              # 本地监听端口,客户端通过这个端口和本地进行通信
BUFFER_SIZE = 4096

def handle_client(client_socket, client_address):
    """处理来自本地浏览器的连接，转发到服务端"""
    try:
        # 连接到服务端
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.connect((SERVER_HOST, SERVER_PORT))

        # 创建线程，用于从客户端转发到服务端
        def forward_client_to_server(client_sock, server_sock):
            try:
                while True:
                    data = client_sock.recv(BUFFER_SIZE)
                    if not data:
                        break
                    server_sock.sendall(data)
            except Exception as e:
                print(f"客户端到服务端转发错误: {e}")
            finally:
                client_sock.close()
                server_sock.close()

        # 创建线程，用于从服务端转发到客户端
        def forward_server_to_client(client_sock, server_sock):
            try:
                while True:
                    data = server_sock.recv(BUFFER_SIZE)
                    if not data:
                        break
                    client_sock.sendall(data)
            except Exception as e:
                print(f"服务端到客户端转发错误: {e}")
            finally:
                client_sock.close()
                server_sock.close()
        # 分别启动从客户端到目标，以及从目标到客户端的转发线程
        client_to_server_thread = threading.Thread(target=forward_client_to_server, args=(client_socket, server_socket))
        server_to_client_thread = threading.Thread(target=forward_server_to_client,args=(client_socket, server_socket))
        client_to_server_thread.start()
        server_to_client_thread.start()

        # 等待线程结束
        client_to_server_thread.join()
        server_to_client_thread.join()

    except Exception as e:
        print(f"处理本地客户端连接时出错: {e}")
    finally:
        client_socket.close()


def main():
    """客户端主函数"""
    local_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    local_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    try:
        local_socket.bind((LOCAL_HOST, LOCAL_PORT))
        local_socket.listen(10)
        print(f"客户端监听在 {LOCAL_HOST}:{LOCAL_PORT}")

        while True:
            client_socket, client_address = local_socket.accept()
            client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
            client_thread.start()

    except Exception as e:
        print(f"客户端出错: {e}")
    finally:
        local_socket.close()


if __name__ == "__main__":
    main()
```

**使用方法：**

1.  **修改配置：**
    *   在 `server.py` 中，设置 `TARGET_HOST` 和 `TARGET_PORT` 为**目标服务器的地址和端口**。 如果希望可以访问任意网址就保留'0.0.0.0',如果固定代理某个网站的请求就写死. 例如 `TARGET_HOST = 'www.google.com'` `TARGET_PORT= 443`，注意443为https
    *   在 `client.py` 中，设置 `SERVER_HOST` 为**服务端（具有公网 IP 的机器）的公网 IP 地址**。修改`LOCAL_HOST` 和 `LOCAL_PORT`为你想要使用的本地监听地址和端口。  通常 `LOCAL_HOST` 为 `127.0.0.1`。

2.  **运行服务端：** 在具有公网 IP 的服务器上运行 `python server.py`。

3.  **运行客户端：** 在你的本地电脑上运行 `python client.py`。

4.  **配置浏览器/应用程序：**  将你的浏览器或需要使用代理的应用程序的代理服务器设置为 `127.0.0.1:9090`（或者你在 `client.py` 中设置的 `LOCAL_HOST` 和 `LOCAL_PORT`）。

**工作原理：**

1.  **服务端：**
    *   监听在指定的端口（`SERVER_PORT`）。
    *   接受客户端连接。
    *   与目标服务器建立连接（`TARGET_HOST`, `TARGET_PORT`）。
    *   在客户端和目标服务器之间双向转发数据。

2.  **客户端：**
    *   监听在本地端口（`LOCAL_PORT`）。
    *   接受本地浏览器/应用程序的连接。
    *   与服务端建立连接（`SERVER_HOST`, `SERVER_PORT`）。
    *   在本地浏览器/应用程序和服务端之间双向转发数据。

**重要提示：**

*   **防火墙：** 确保服务端防火墙允许 `SERVER_PORT` 的流量。
*   **安全性：**  强烈建议使用更安全的替代方案（如 SSH 隧道或 VPN）。 如果您使用此脚本，请务必了解其安全限制。
*   **调试：** 如果遇到问题，请检查控制台输出，查看是否有错误消息。  可以使用 `tcpdump` 或 Wireshark 等工具来抓包分析网络流量。

这个代码是一个基础版本。 为了提高可用性和安全性，您可能需要考虑以下改进：

*   **TLS 加密：**  使用 `ssl` 模块为连接添加 TLS 加密。
*   **身份验证：**  在客户端和服务端之间添加身份验证机制。
*   **日志记录：**  使用 `logging` 模块记录详细的日志。
*   **配置解析：**  使用 `argparse` 或 `configparser` 等模块来管理配置。
*   **连接池：**  维护一个到目标服务器的连接池，以提高性能。
*   **异步 IO：** 使用 `asyncio` 或其他异步 IO 框架来处理并发连接。

请在实际使用之前，充分理解代码并根据你的需求进行修改和测试。 再次强调，安全性是首要考虑的因素！
