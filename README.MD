# HTTP 1.1 Server in C
Simple HTTP server from scratch written in C. For more details check write-up below.

## Usage
Assuming on Linux/Unix machine.
``` bash
git clone https://github.com/jamesyoung-15/http-server.git
cd http-server
./http_server.o
```

## Project/Code Detail
Project write-up so that I can re-inforce my understanding.
### Basic Outline/Pseudocode
![alt text](./src/media/simple-socket-diagram.png) 

### Explaining code

### Next Steps/Improvements to make
This HTTP server is very simple and lacks performance and features. For performance, I plan on implementing multi-threading to handle concurrent connections. Feature-wise, I plan on adding file-serving. There are also probably many security issues with this server. It is possible that my server could be vulnerable to buffer overflow that can be exploited with a http GET request. However, my understanding of this cybersecurity isn't great so I'm not sure.

## Resources Used
- [Beej Guide](https://beej.us/guide/bgnet/html/#client-server-background)
- [Mozilla Developer Documentation](https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview)
- [Youtube Playlist of Labs of CSE4202 from Inha University](https://www.youtube.com/playlist?list=PLZIwlOSv75K7jXcVABdIo3wyKp5NwXKlW) 
- [Computer Networking: A Top Down Approach](https://gaia.cs.umass.edu/kurose_ross/index.php) (Textbook used in ELEC3120 course I'm taking in HKUST)
- [Blog Post Example](https://bruinsslot.jp/post/simple-http-webserver-in-c/)
- [Medium Blog Post](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-knoPostExample-simple-http-server-from-scratch-d1ef8945e4fa)
-  RFC 7230, RFC 7231, RFC 7232, RFC 7233, RFC 7234, RFC 7235 (Official source, just skimmed through it)
- `Man` pages of `socket`, section 7)of `ip` 