#include <stdint.h>
// #include <bcm2835.h>
#include <unistd.h>
#include <stdio.h>
#include "spi.h"
#include "server.h"
#include "instruction.h"
#include <string.h>
#include <iostream>
#include <bitset>

using namespace std;

int main()
{
	Server server = Server();
	// Instruction instruction = Instruction();
	// SPI spi = SPI();

	string data = "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0";

	server.startServer();
	while (1)
	{

		string msg = server.recieveData();
		printf("Recieved: %s\n", msg.c_str());

		/*uint8_t command = instruction.getInterpetation(msg);
		bitset<8> x(command);
		cout << "Sending to SPI: " << x << endl;

		uint8_t recieveData = spi.transferData(command);
		printf("Sent to SPI: 0x%02x. Read back from SPI: 0x%02x. \n", command, recieveData);*/

		server.sendData(data);
		usleep(100000);

		if (msg == server.getDisconnectMessage())
		{
			// spi.closeSPI();
			printf("Server shutting down...\n");
			// closing the connected socket
			server.closeClient();
			// closing the listening socket
			server.shutDown();
			return 0;
		}
	}
	return 0;
}
