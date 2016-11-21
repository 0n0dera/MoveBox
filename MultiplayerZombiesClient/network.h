#pragma once

#include <iostream>
#include <enet/enet.h>
#include <string>
#include "packet_builder.h"
#include "scene.h"
#include "player.h"

class Network
{
public:
	Network();
	~Network();
	void SendPositionInfo(const Player & player);
	void ReceiveInfo(const Scene & scene);
private:
	const char* host = "localhost";
	const int port = 4444;

	int id;
	ENetHost* client;
	ENetPeer* server;
	ENetEvent event;
};