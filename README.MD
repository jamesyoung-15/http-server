# HTTP 1.1 Server in C
Simple HTTP server from scratch written in C. I decided to create this personal project to practice some basic C programming while also applying some computer networking knowledge I learned in class.

## Usage
Assuming on Linux/Unix machine. Feel free to test it out.
``` bash
git clone https://github.com/jamesyoung-15/http-server.git
cd http-server
gcc http-server.c -o http-server.o
```

## Project Write-Up
### Background
HTTP is an application layer protocol that defines how a browser and server communicates and delivers data. HTTP mostly uses TCP for the transport protocol. In order to implement the transport protocol, the use of sockets and socket programming is required to establish a communication link between the client and server. Below is a diagram that shows how a typical TCP connection can be established.

![alt text](./src/media/simple-socket-diagram.png)

Very simply, on the server side we first create a socket. Then, we bind the socket to an IP address and port. Afterwards, the server will listen for incoming connection and once the client's connection is accepted, the client and server can read/write to each other. The client side is much simpler, where we just need to create a socket and connect to the IP and port of server. Once a communication is finished, we close the socket. For code of a simple TCP server and client, see [simple_tcp folder](https://github.com/jamesyoung-15/http-server/tree/main/simple_tcp).

Now HTTP's implementation looks something like this:

![alt text](./src/media/http-diagram.png)


### Next Steps/Improvements to make
This HTTP server is very simple and lacks performance and features. For performance, I plan on implementing multi-threading to handle concurrent connections. Feature-wise, I plan on adding file-serving. There are also probably many security issues with this server. It is possible that my server could be vulnerable to buffer overflow that can be exploited with a http GET request. However, my understanding of this cybersecurity isn't great so I'm not sure.

## Resources Used
- [Beej Guide](https://beej.us/guide/bgnet/html/#client-server-background)
- [Mozilla Developer Documentation](https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview)
- [Youtube Playlist of Labs of CSE4202 from Inha University](https://www.youtube.com/playlist?list=PLZIwlOSv75K7jXcVABdIo3wyKp5NwXKlW) 
- [Computer Networking: A Top Down Approach](https://gaia.cs.umass.edu/kurose_ross/index.php) (Textbook used in course I'm taking)
- [Blog Post Example](https://bruinsslot.jp/post/simple-http-webserver-in-c/)
- [Medium Blog Post](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-knoPostExample-simple-http-server-from-scratch-d1ef8945e4fa)
-  RFC 7230, RFC 7231, RFC 7232, RFC 7233, RFC 7234, RFC 7235 (official resources for HTTP 1.1)
- `Man` pages of `socket`, `man 7 ip`, etc. 