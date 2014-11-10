/* 
 * File:   datastructures.h
 * Author: georgez
 *
 * Created on 17 October 2014, 14:40
 */

#ifndef IASDATA_H
#define	IASDATA_H

#include <cstdio>
#include <cstdlib>
#include <string>

 typedef struct PACKETHEAD {
     uint16_t length=sizeof(PACKETHEAD);
     uint16_t datasize  =0;    // size of buffer
     uint8_t type       =0;    // type of packet
     uint8_t item       =0;    // Item number in this set
     uint8_t tot        =0;    // total number of items in this set
     uint8_t load       =0;    // set if additional data submitted
     uint8_t ack        =0;    // set if acknowledgement only required
     uint8_t resp       =0;    // set if full response required
     uint8_t ais        =0;    // signals AIS subsystem   
     uint8_t result     =0;    // reserved for future / Application use
     uint32_t id        =0;    // Application specific
     uint64_t ref       =0;    // Hold a reference number or 32/64bit pointer    
     char buffer[1];           // pointer to  buffer
}PACKETHEAD,*PACKETHEAD_PTR;

#define IAS_MAX_BUUFER_SIZE     2048


#define IAS_SERVICE_PRODUCER    1
#define IAS_SERVICE_CONSUMER    2
#define IAS_SERVICE_DETACH      3  // called by consumer
#define IAS_SERVICE_CLOSE       4  // called by producer



#define IAS_PACKETTYPE_DATA         0
#define IAS_PACKETTYPE_REQUEST      1
#define IAS_PACKETTYPE_RESPONSE     2

#define IAS_RESPONSE_TIMEOUT        0
#define IAS_RESPONSE_SUCCESS        1

#endif	/* IASDATA_H */

