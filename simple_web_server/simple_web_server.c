#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // 读取客户端请求
    bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("Failed to read from client");
        close(client_socket);
        return;
    }

    buffer[bytes_read] = '\0';
    printf("Received request:\n%s\n", buffer);

    // 解析 HTTP 请求（这里只处理 GET 请求）
    if (strncmp(buffer, "GET", 3) == 0) {
        // 创建 HTTP 响应
        const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>Hello, World!</h1></body></html>\r\n";

        // 发送响应给客户端
        write(client_socket, response, strlen(response));
    } else {
        // 处理非 GET 请求
        const char *response =
            "HTTP/1.1 405 Method Not Allowed\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>405 Method Not Allowed</h1></body></html>\r\n";

        // 发送响应给客户端
        write(client_socket, response, strlen(response));
    }

    // 关闭客户端连接
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 创建服务器套接字
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    server_addr.sin_family = AF_INET; //指定地址族，对于 IPv4，一般设置为 AF_INET。
    /**
     * 存储 IPv4 地址。这个成员是一个 struct in_addr 类型，其定义如下：
     * struct in_addr {
     *     uint32_t s_addr; // 32 位的 IPv4 地址，使用网络字节序
     * };
     * 
     * */
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(PORT); //指定端口号，必须使用网络字节序。可以使用 htons 函数将主机字节序转换为网络字节序。

    // 绑定套接字到端口
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to bind socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_socket, 5) < 0) {
        perror("Failed to listen on socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // 接受并处理客户端连接
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) >= 0) {
        handle_client(client_socket);
    }

    if (client_socket < 0) {
        perror("Failed to accept client connection");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // 关闭服务器套接字
    close(server_socket);
    return 0;
}
