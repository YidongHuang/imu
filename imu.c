#include <string.h>
#include "freespace.h"
#include <stdio.h>
#include "freespace_codecs.h"
#include "freespace_printers.h"
#include "freespace_util.h"
#include <stdlib.h>
#include <signal.h>


int main(){
	int rc = freespace_init();
	int numIds;
	
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
}
