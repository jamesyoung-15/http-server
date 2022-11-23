# HTTP 1.1 Server in C
Simple HTTP server from scratch written in C. I decided to create this personal project to practice some basic C programming while also applying some computer networking knowledge I learned in class.

## Demo

![alt text](https://github.com/jamesyoung-15/http-server/blob/main/images/http-demo.gif)
## Usage
Assuming on Linux/Unix machine.
``` bash
git clone https://github.com/jamesyoung-15/http-server.git
cd http-server
gcc http-server.c -o http-server.o
./http-server.o
```
Then go to http://localhost:4545 on same machine. When using another machine use server IP eg. 192.168.0.15:4545. To access other files, state the file path (in this directory) eg. http://localhost:4545/images/testpic.png.

## Project Write-Up
### Background Info
<details open><summary><h5>Collapse/Expand</h5></summary>
HTTP is an application layer protocol that defines how a browser and server communicates and delivers data. HTTP mostly uses TCP for the transport protocol. In order to implement the transport protocol, the use of sockets and socket programming is required to establish a communication link between the client and server. Below is a diagram that shows how a typical TCP connection can be established.

![alt text](./src/images/simple-socket-diagram.png)

Very simply, on the server side we first create a socket. Then, we bind the socket to an IP address and port. Afterwards, the server socket will listen for incoming connection and once the client's connection is accepted, the client and server can transfer data to each other. The client side is much simpler, where we just need to create a socket and connect to the server. Once a communication is finished, we close the socket. For code of a simple TCP server and client, see [simple_tcp folder](https://github.com/jamesyoung-15/http-server/tree/main/simple_tcp).

Building on top of the TCP transport protocol described above, HTTP adds it's application layer protocol as shown below:

![alt text](./src/images/http-diagram.png)

As seen, once connection is established the client writes an HTTP request. Whilst the format and content of HTTP request differ based on different HTTP versions, certain principles stay the same. The request message should consist of a method (eg. GET) that tells the server what it should do. Next should be the path to the requested target (eg. /index.html). Finally it should include the HTTP version. Here is an example of a request message: 
```
GET /index.html HTTP/1.1
Host: developer.mozilla.org
Accept-Language: fr
```
Note after the `GET /index.html HTTP/1.1` start line, below it are examples of HTTP headers that pass extra info.

Once the server receives the request, it will send out an HTTP response where the first line is the status line that includes the HTTP version, status code (eg. 404), and a status text (eg. Not Found). Once again, HTTP headers can be included for extra info. Below is an example of an HTTP response:
```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 88
``` 
In HTTP 2 uses frames but this project is focused on HTTP 1.1. For more info check the Mozilla Developer docmentation listed below.
</details>



### Next Steps/Improvements to make
<details open><summary><h5>Collapse/Expand</h5></summary>
This HTTP server is very simple and I plan to work on it a bit more when I have time. For performance, the server lacks multi-threading to handle concurrent connections. There are also probably many security issues with this server. For example, the server could be vulnerable to buffer overflow attack that can be exploited with a HTTP GET request.
</details>

## Resources Used
- [Beej Guide](https://beej.us/guide/bgnet/html/#client-server-background)
- [Mozilla Developer Documentation](https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview)
- [Youtube Playlist of Labs of CSE4202 from Inha University](https://www.youtube.com/playlist?list=PLZIwlOSv75K7jXcVABdIo3wyKp5NwXKlW) 
- [Computer Networking: A Top Down Approach](https://gaia.cs.umass.edu/kurose_ross/index.php) (Textbook used in course I'm taking)
- [Blog Post Example](https://bruinsslot.jp/post/simple-http-webserver-in-c/)
- [Medium Blog Post](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-knoPostExample-simple-http-server-from-scratch-d1ef8945e4fa)
-  RFC 7230, RFC 7231, RFC 7232, RFC 7233, RFC 7234, RFC 7235 (official resources for HTTP 1.1)
- `Man` pages of `socket`, `man 7 ip`, etc. 