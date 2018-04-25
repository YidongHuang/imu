/**
 * This file is part of libfreespace-examples.
 *
 * Copyright (c) 2009-2013, Hillcrest Laboratories, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of the Hillcrest Laboratories, Inc. nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef _WIN32
#include "win32/stdafx.h"
#include <stdio.h>
#else
#include <stdlib.h>
#include <signal.h>
#endif

#include <freespace/freespace.h>
#include <freespace/freespace_util.h>
#include <freespace/freespace_printers.h>
#include "appControlHandler.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

#include <string.h>

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT 5001

/**
 * main
 * This example uses the synchronous API to
 *  - find a device
 *  - open the device found
 *  - configure the device to output motion
 *  - read motion messages sent by the device
 * This example assume the device is already connected.
 */
int main(int argc, char* argv[]) {
    struct freespace_message message;
    FreespaceDeviceId device;
    int numIds; // The number of device ID found
    int rc; // Return code
    struct MultiAxisSensor angPos;

    // Flag to indicate that the application should quit
    // Set by the control signal handler
    int quit = 0;

    printVersionInfo(argv[0]);

    addControlHandler(&quit);

    // Initialize the freespace library
    rc = freespace_init();
    if (rc != FREESPACE_SUCCESS) {
        printf("Initialization error. rc=%d\n", rc);
	    return 1;
    }

    printf("Scanning for Freespace devices...\n");
     // Get the ID of the first device in the list of availble devices
    rc = freespace_getDeviceList(&device, 1, &numIds);
    if (numIds == 0) {
        printf("Didn't find any devices.\n");
        return 1;
    }

    printf("Found a device. Trying to open it...\n");
    // Prepare to communicate with the device found above
    rc = freespace_openDevice(device);
    if (rc != FREESPACE_SUCCESS) {
        printf("Error opening device: %d\n", rc);
        return 1;
    }

    // Display the device information.
    printDeviceInfo(device);

    // Make sure any old messages are cleared out of the system
    rc = freespace_flush(device);
    if (rc != FREESPACE_SUCCESS) {
        printf("Error flushing device: %d\n", rc);
        return 1;
    }

    // Configure the device for motion outputs
    printf("Sending message to enable motion data.\n");
    memset(&message, 0, sizeof(message)); // Make sure all the message fields are initialized to 0.
    
    message.messageType = FREESPACE_MESSAGE_DATAMODECONTROLV2REQUEST;
    message.dataModeControlV2Request.packetSelect = 8;  // MotionEngine Outout
    message.dataModeControlV2Request.mode = 0;          // Set full motion
    message.dataModeControlV2Request.formatSelect = 0;  // MEOut format 0
    message.dataModeControlV2Request.ff0 = 1;           // Pointer fields
    message.dataModeControlV2Request.ff3 = 1;           // Angular velocity fields
    message.dataModeControlV2Request.ff6 = 1;
    
    rc = freespace_sendMessage(device, &message);
    if (rc != FREESPACE_SUCCESS) {
        printf("Could not send message: %d.\n", rc);
    }
    
    // Initial Socket
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[DEFAULT_BUFLEN];
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(DEFAULT_PORT);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    listen(listenfd, 1);
    
    // A loop to read messages
    printf("Listening for messages.\n");
   // while (!quit) {
    int count = 1;
    //connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    while(!quit){
	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
	
	//count = count + 1;
        rc = freespace_readMessage(device, &message, 100);
        if (rc == FREESPACE_ERROR_TIMEOUT ||
            rc == FREESPACE_ERROR_INTERRUPTED) {
            // Both timeout and interrupted are ok.
            // Timeout happens if there aren't any events for a second.
            // Interrupted happens if you type CTRL-C or if you
            // type CTRL-Z and background the app on Linux.
            continue;
        }
        if (rc != FREESPACE_SUCCESS) {
            printf("Error reading: %d. Quitting...\n", rc);
            break;
        }

        // freespace_printMessage(stdout, &message); // This just prints the basic message fields
        if (message.messageType == FREESPACE_MESSAGE_MOTIONENGINEOUTPUT) {
            rc = freespace_util_getAngPos(&message.motionEngineOutput, &angPos);
            if (rc == 0) {
                printf ("W: % 6.2f, X: % 6.2f, Y: % 6.2f, Z: % 6.2f\n", angPos.w, angPos.x, angPos.y, angPos.z);
		sprintf(&sendBuff, "%6.2f%6.2f%6.2f%6.2f\n", angPos.w, angPos.x, angPos.y, angPos.z);
		send(connfd, sendBuff, strlen(sendBuff), 0);
		usleep(10);
		printf("The number of message sent: %d\n", count);
		count = count + 1;
            }
        }

	close(connfd);
    }


    // Close communications with the device
    printf("Cleaning up...\n");
    freespace_closeDevice(device);
    /** --- END EXAMPLE FINALIZATION OF DEVICE --- **/

    // Cleanup the library
    freespace_exit();

    return 0;
}
