#include <iostream>
#include <string>
#include <enet/enet.h>
#include <sstream>

const int HOST = ENET_HOST_ANY;
const int PORT = 4444;
const int MAX_CLIENTS = 3;

int main()
{
	if (enet_initialize() != 0)
	{
		std::cout << "Failed to initialize ENet" << std::endl;
		return EXIT_FAILURE;
	}

	// create host
	ENetAddress address;
	ENetHost* server;
	address.host = HOST;
	address.port = PORT;
	server = enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);

	if (server == nullptr)
	{
		std::cout << "Failed to create a server" << std::endl;
		exit(EXIT_FAILURE);
	}

	int client_id = 0;
	
	// events
	ENetEvent event;
	ENetPacket* packet;
	std::cout << "Server started at localhost:" << address.port << std::endl;
	while (1)
	{
		while (enet_host_service(server, &event, 0) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
			{
				printf("Client %u connected from %x:%u.\n",
					client_id,
					event.peer->address.host,
					event.peer->address.port);
				packet = enet_packet_create(std::to_string(client_id).c_str(), strlen(std::to_string(client_id).c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
				++client_id;
				enet_peer_send(event.peer, 0, packet);
				enet_packet_destroy(event.packet);
			}
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet of length %u containing %s was received from %s on channel %u.\n",
					event.packet->dataLength,
					event.packet->data,
					event.peer->data,
					event.channelID);
				/* Clean up the packet now that we're done using it. */
				
				packet = enet_packet_create((char*)event.packet->data, strlen((char*)event.packet->data) + 1, ENET_PACKET_FLAG_RELIABLE);
				enet_host_broadcast(server, 0, packet);
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", event.peer->data);
				/* Reset the peer's client information. */
				event.peer->data = NULL;
				break;
			}
		}
	}
	
	enet_host_destroy(server);
	atexit(enet_deinitialize);
}