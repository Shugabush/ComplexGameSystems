#include <WinSock2.h>
#include <WS2tcpip.h>

#include <iostream>
#include <cassert>

int main()
{
	// initialization of WinSock
	// - this only occurs on Windows and its implementation of sockets
	WSADATA wsaData;
	int success = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (success != 0)
	{
		std::cerr << "ERROR: Failed to initialize WinSock :(" << std::endl;
		return -1;
	}

	// resolve local and server addresses
	addrinfo config;
	memset(&config, 0, sizeof(addrinfo)); // zero out memory for that object
	config.ai_family = AF_INET;
	config.ai_socktype = SOCK_DGRAM;
	config.ai_protocol = IPPROTO_UDP;
	config.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by this program
	addrinfo* localAddr = nullptr;
	success = getaddrinfo(nullptr, "0", &config, &localAddr);
	if (success != 0)
	{
		std::cerr << "ERROR: Failed to initialize sockets" << std::endl;
		WSACleanup();
		return 1;
	}

	addrinfo* remoteAddr = nullptr;
	// Resolve the remote address
	

	// create socket (won't be ready to recieve yet)
	SOCKET curSocket = INVALID_SOCKET;
	curSocket = socket(localAddr->ai_family, localAddr->ai_socktype, localAddr->ai_protocol);
	if (curSocket == INVALID_SOCKET)
	{
		std::cerr << "ERROR: socket creation failed!" << std::endl;
		freeaddrinfo(localAddr);
		WSACleanup();
		return 1;
	}

	// bind and configure socket
	success = bind(curSocket, localAddr->ai_addr, (int)localAddr->ai_addrlen);
	if (success == SOCKET_ERROR)
	{
		std::cerr << "ERROR: socket binding failed!" << std::endl;
		freeaddrinfo(localAddr);
		closesocket(curSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(localAddr); // can clean up local socket after binding is successful

	timeval curSocketTimeout;
	curSocketTimeout.tv_sec = 2; // 2 seconds
	curSocketTimeout.tv_usec = 0; // 0 micro-seconds

	const size_t BUFFER_SIZE = 1400;
	unsigned char buffer[BUFFER_SIZE];

	while (true)
	{
		fd_set curSocketDesc;
		FD_ZERO(&curSocketDesc);
		FD_SET(curSocket, &curSocketDesc);
		int status = select((int)curSocket, &curSocketDesc, nullptr, nullptr, &curSocketTimeout);

		// status may be ...
		// 0 			=> socket timed out (i.e., did not recv any information while waiting)
		// SOCKET_ERROR => an error occurred
		// status > 0 	=> data was recv'd!

		if (status == SOCKET_ERROR)
		{
			status = WSAGetLastError();
			return -1;
		}

		if (status > 0)
		{
			addrinfo incomingAddr;
			memset(&incomingAddr, 0, sizeof(incomingAddr));
			socklen_t incomingAddrLen = sizeof(incomingAddr);

			int bytesRecieved = recvfrom(
				curSocket,
				(char*)buffer,
				BUFFER_SIZE,
				0,
				(sockaddr*)&incomingAddr,
				&incomingAddrLen);

			if (bytesRecieved)
			{
				// Unsafe: assume message is a C-string and is shorter in length
				// and will fit within the buffer we've allocated
				buffer[bytesRecieved] = '\0'; // insert NULL-terminating character

				// print it out to stdout
				std::cout << "[MSG] " << (char*)buffer << std::endl;
			}

			addrinfo* serverAddr = nullptr;
			getaddrinfo(nullptr, "7777", &config, &serverAddr);

			const char* msg = "John Madden";
			const size_t msgLen = strlen(msg);
			assert(msgLen + 1 < BUFFER_SIZE);

			// send the message to the server
			sendto(
				curSocket,
				msg,
				(int)msgLen + 1,
				0,
				serverAddr->ai_addr,
				(int)serverAddr->ai_addrlen
				);
		}
	}

	// clean-up
	closesocket(curSocket);

	return 0;
}