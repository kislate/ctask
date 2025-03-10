import socket
import threading
import sys
import os
import nacl.secret
import nacl.utils
from nacl.exceptions import CryptoError
import configparser

import subprocess
import platform

def ping(host):
    """
    Ping a host and return True if it responds, False otherwise.
    """
    # Determine the platform to adjust the ping command accordingly
    param = '-n' if platform.system().lower() == 'windows' else '-c'
    
    # Building the command. Ex: "ping -c 1 google.com" or "ping -n 1 google.com"
    command = ['ping', param, '1', host]
    
    # Run the command
    try:
        output = subprocess.check_output(command, stderr=subprocess.STDOUT, universal_newlines=True)
        if "unreachable" in output.lower():
            return False
        else:
            return True
    except subprocess.CalledProcessError:
        return False

SERVER_HOST = '43.156.122.9'
SERVER_PORT = 8080
LOCAL_HOST = '127.0.0.1'
LOCAL_PORT = 8080
BUFFER_SIZE = 4096

def load_secret_key():
    """尝试从环境变量或配置文件加载密钥"""

    # 1. 尝试从环境变量读取密钥
    secret_key = os.environ.get("PROXY_SECRET_KEY")  # 环境变量名可以自定义
    if secret_key:
        print("从环境变量加载密钥")
        return secret_key.encode('utf-8')  # 转换为字节

    # 2. 如果环境变量不存在，则从配置文件读取
    config = configparser.ConfigParser()
    config.read("config.ini")
    try:
        secret_key = config["security"]["secret_key"]
        print("从config.ini加载密钥")
        return secret_key.encode('utf-8')  # 转换为字节
    except KeyError:
        print("无法从config.ini加载密钥")
        pass

    # 3. 如果两者都不存在，抛出异常或使用默认密钥(非常不建议!!!)
    raise ValueError("未找到密钥：请设置环境变量 'PROXY_SECRET_KEY' 或在 config.ini 中配置")

# 加载密钥
try:
    SECRET_KEY = load_secret_key()
    # 保证秘钥长度
    while len(SECRET_KEY) < 32:
        SECRET_KEY += b'\0'
    SECRET_KEY = SECRET_KEY[:32]  # 截断到 32 字节
except ValueError as e:
    print(f"密钥加载错误: {e}")
    sys.exit(1)  # 退出程序

def handle_client(client_socket, client_address):
    """处理来自本地浏览器的连接，转发到服务端，使用 ChaCha20 加密"""
    try:
        # 连接到服务端
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.connect((SERVER_HOST, SERVER_PORT))

        box = nacl.secret.SecretBox(SECRET_KEY)
        # 创建线程，用于从客户端转发到服务端
        def forward_client_to_server(client_sock, server_sock,secret_box):
            try:
                while True:
                    data = client_sock.recv(BUFFER_SIZE)
                    if not data:
                        break

                    # 使用随机数加密数据
                    nonce = nacl.utils.random(nacl.secret.SecretBox.NONCE_SIZE)
                    encrypted = secret_box.encrypt(data, nonce)

                    #发送随机数+加密数据给服务器
                    server_sock.sendall(encrypted)
            except Exception as e:
                print(f"客户端到服务端转发错误: {e}")
            finally:
                client_sock.close()
                server_sock.close()

        # 创建线程，用于从服务端转发到客户端
        def forward_server_to_client(client_sock, server_sock, secret_box):
            try:
                while True:
                     encrypted_data = server_sock.recv(BUFFER_SIZE)
                     if not encrypted_data:
                        break

                     nonce = encrypted_data[:nacl.secret.SecretBox.NONCE_SIZE] #NonceSize = 24字节

                     encrypted = encrypted_data[nacl.secret.SecretBox.NONCE_SIZE:]#剩下的为加密数据
                     try:

                        data = secret_box.decrypt(encrypted,nonce)
                        client_sock.sendall(data)

                     except CryptoError as e:
                         print(f"解密错误:{e}")
                         break

            except Exception as e:
                print(f"服务端到客户端转发错误: {e}")
            finally:
                client_sock.close()
                server_sock.close()
        # 分别启动从客户端到目标，以及从目标到客户端的转发线程
        client_to_server_thread = threading.Thread(target=forward_client_to_server, args=(client_socket, server_socket,box))
        server_to_client_thread = threading.Thread(target=forward_server_to_client,args=(client_socket, server_socket,box))
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
    host = SERVER_HOST
    if ping(host):
        print(f"{host} is reachable.")
    else:
        print(f"{host} is not reachable.")
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