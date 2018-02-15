/*
 * ACRONET Project
 * http://www.acronet.cc
 *
 * Copyright ( C ) 2014 Acrotec srl
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the EUPL v.1.1 license.  See http://ec.europa.eu/idabc/eupl.html for details.
 */

#include "Acronet/setup.h"


#include <asf.h>
#include <stdio.h>
#include "progmem.h"
#include <conf_board.h>
#include <conf_usart_serial.h>

#include "Acronet/globals.h"

#include "config/conf_usart_serial.h"
#include "Acronet/drivers/SIM/sim900.h"
#include "Acronet/drivers/UART_INT/cbuffer_usart.h"
#include "Acronet/Sensors/raingauge/pulse_raingauge.h"
#include "Acronet/drivers/StatusLED/status_led.h"
//#include "config/conf_APN.h"
#include "Acronet/drivers/AT24CXX/AT24CXX.h"
#include "Acronet/services/config/config.h"
#include "Acronet/drivers/Voltmeter/voltmeter.h"

#define METTITUTTO

#ifdef METTITUTTO
static const __flash uint8_t cfg_template[] = {
	0xAC, 0x30, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0x01, 0x02, 0x01, 0x10, 0x01, 0x03, 0x01, 0x30, 0x01,
	0x04, 0x01, 0x80, 0x01, 0x01, 0x02, 0x00, 0x02, 0x02, 0x02, 0x10, 0x02, 0x01, 0x03, 0xC0, 0x02,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3C, 0x00, 0x00, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x54, 0x45, 0x53, 0x54, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x61, 0x77, 0x73, 0x67, 0x61, 0x74, 0x65, 0x2E, 0x61,
	0x63, 0x72, 0x6F, 0x6E, 0x65, 0x74, 0x77, 0x6F, 0x72, 0x6B, 0x2E, 0x6F, 0x72, 0x67, 0x2F, 0x70,
	0x75, 0x74, 0x44, 0x61, 0x74, 0x61, 0x2F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x61, 0x77, 0x73, 0x67, 0x61, 0x74, 0x65, 0x2E, 0x61,
	0x63, 0x72, 0x6F, 0x6E, 0x65, 0x74, 0x77, 0x6F, 0x72, 0x6B, 0x2E, 0x6F, 0x72, 0x67, 0x2F, 0x67,
	0x65, 0x74, 0x54, 0x69, 0x6D, 0x65, 0x2F, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x32, 0x2E, 0x68, 0x74,
	0x6D, 0x6C, 0x3F, 0x41, 0x57, 0x53, 0x49, 0x44, 0x3D, 0x54, 0x45, 0x53, 0x54, 0x36, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x23, 0x76, 0x6F, 0x64, 0x61, 0x66, 0x6F, 0x6E, 0x65, 0x20, 0x49, 0x54, 0x3D, 0x77, 0x65, 0x62,
	0x2E, 0x6F, 0x6D, 0x6E, 0x69, 0x74, 0x65, 0x6C, 0x2E, 0x69, 0x74, 0x23, 0x49, 0x20, 0x54, 0x49,
	0x4D, 0x3D, 0x69, 0x62, 0x6F, 0x78, 0x2E, 0x74, 0x69, 0x6D, 0x2E, 0x69, 0x74, 0x23, 0x70, 0x6F,
	0x73, 0x74, 0x65, 0x6D, 0x6F, 0x62, 0x69, 0x6C, 0x65, 0x3D, 0x69, 0x6E, 0x74, 0x65, 0x72, 0x6E,
	0x65, 0x74, 0x2E, 0x70, 0x6F, 0x73, 0x74, 0x65, 0x6D, 0x6F, 0x62, 0x69, 0x6C, 0x65, 0x2E, 0x69,
	0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#else 
static const __flash uint8_t cfg_template[] = {0};
#endif


RET_ERROR_CODE cfg_check(void)
{
	uint16_t v;
	nvm_eeprom_read_buffer(0,&v,sizeof(uint16_t));
	
	return (v==0x30AC)?AC_ERROR_OK:AC_ERROR_GENERIC;
	
}


RET_ERROR_CODE cfg_find_item(CFG_ITEM_TAG item_tag,CFG_ITEM_ADDRESS * item_address)
{
	static const uint8_t BUF_MAX_LEN = 64;
	struct {uint16_t tag,address;} buf[BUF_MAX_LEN];
	
	eeprom_addr_t it=0;
	uint8_t cycle = 16;
	
	do {
		nvm_eeprom_read_buffer(it,&buf,sizeof(buf));
		
		if (buf[0].tag != 0x30AC)
		{
				*item_address = 0;
				return AC_UNSUPPORTED;
		}

		for (uint8_t i=1;i<BUF_MAX_LEN;++i)
		{
			if(item_tag == buf[i].tag) {
				*item_address = buf[i].address;
				return AC_ERROR_OK;
			}
		}

		if (buf[0].address == 0xFFFF)
		{
			break;
		}
		
		it = buf[0].address;
		
	} while(--cycle != 0);
	

	return AC_ITEM_NOT_FOUND;
}

RET_ERROR_CODE cfg_get_item_BYTE(CFG_ITEM_ADDRESS item_address,uint8_t * pByte)
{
	*pByte = nvm_eeprom_read_byte(item_address);
	return AC_ERROR_OK;
}

RET_ERROR_CODE cfg_get_item_DWORD(CFG_ITEM_ADDRESS item_address,uint32_t * pDWORD)
{
	nvm_eeprom_read_buffer(item_address,pDWORD,sizeof(uint32_t));
	return AC_ERROR_OK;
}


RET_ERROR_CODE cfg_get_item_file(CFG_ITEM_ADDRESS item_address,void * pBuf,uint16_t len)
{
		
	if (item_address>=EEPROM_SIZE)
	{
		return AC_BUFFER_TOO_SMALL;
	}

	Bool t = false;
	uint16_t l = len;
	
	if (item_address+l >= EEPROM_SIZE)
	{
		t = true;
		l = EEPROM_SIZE - item_address;
	}

	nvm_eeprom_read_buffer(item_address,pBuf,l);

	return t ? AC_TRUNCATED_READ : AC_ERROR_OK;
}


RET_ERROR_CODE cfg_get_item_dictionary(CFG_ITEM_ADDRESS item_address,char szKey[], char szVal[],const uint8_t lenBufVal)
{
	
	debug_string_1P(NORMAL,PSTR("****** Searching for key : "));
	debug_string(NORMAL,szKey,RAM_STRING);
	debug_string_1P(NORMAL,g_szCRLF);
	

	uint16_t idx = item_address;

	const uint8_t lenSZKey = strlen(szKey) + 1;

	
	while (true)
	{
		const uint16_t bs = min(EEPROM_SIZE-idx,lenBufVal);
		nvm_eeprom_read_buffer(idx,szVal,bs);

		if(szVal[0]!='#') {
			return AC_UNSUPPORTED;
		}

		char * psz = szVal+1;
		uint8_t ix;
		
		for (ix=0;ix<lenSZKey;++ix)
		{
			if(psz[ix]!=szKey[ix]) break;
		}
		
		if (psz[ix]!='=')
		{
			uint8_t iy=ix;
			for (;iy<bs;++iy)
			{
				if((psz[iy]=='#') || (psz[iy]=='*'))
				{
					idx += iy+1;
					break;
				}
				
				if(psz[iy]==0) {
					debug_string_2P(NORMAL,PSTR("cfg_get_item_dictionary") ,PSTR("Unable to find the requested VALUE"));
					szVal[0]=0;
					return AC_ITEM_NOT_FOUND;
				}
				
			}
			continue;
		}
		

		psz = (&psz[ix])+1; //TODO: could it be psz = (&psz[ix+1]) ?
		
		for(ix = 0;ix<bs;++ix)
		{
			if((psz[ix]=='#') || (psz[ix]=='*') || (psz[ix]==0))
			{
				break;
			}
			
			szVal[ix] = psz[ix];
		}

		szVal[ix] = 0;
		return AC_ERROR_OK;
	}
}




static void cfg_old_get(uint8_t it, char szVal[],const uint8_t len)
{
	int idx;
	nvm_eeprom_read_buffer(it,&idx,sizeof(uint16_t));
	
	uint8_t bs = min(EEPROM_SIZE-idx,len);
	nvm_eeprom_read_buffer(idx,szVal,bs);
}


uint8_t cfg_old_check(void)
{
	uint16_t v;
	nvm_eeprom_read_buffer(0,&v,sizeof(uint16_t));
	
	return (v==0x01AC);
}


void cfg_old_get_sim_pin(char szVal[],const uint8_t len)
{
	cfg_old_get(8,szVal,len);
}

void cfg_old_get_gprs_apn(char szKey[], char szVal[],const uint8_t lenBufVal)
{
	uint16_t idx = 0;
	nvm_eeprom_read_buffer(6,&idx,sizeof(uint16_t));

	cfg_get_item_dictionary(idx,szKey,szVal,lenBufVal);

}

void cfg_old_get_aws_id(char szVal[],const uint8_t len)
{
	cfg_old_get(4,szVal,len);
}

void cfg_old_get_service_url_time(char szVal[],const uint8_t len)
{
	cfg_old_get(10,szVal,len);
}

void cfg_old_get_service_url_send(char szVal[],const uint8_t len)
{
	cfg_old_get(12,szVal,len);
}

void cfg_old_get_datalogger_timings(uint32_t * const sendDT,uint32_t * const storeDT,uint32_t * const syncDT,uint32_t * const tickDT)
{
	union {
		struct {uint32_t a,b,c,d;} buf;
		char cbuf[sizeof(uint32_t)*4];
	} U;
	cfg_old_get(0x0e,U.cbuf,sizeof(U.cbuf));
	*sendDT  = U.buf.a;
	*storeDT = U.buf.b;
	*syncDT  = U.buf.c;
	*tickDT  = U.buf.d;
}


RET_ERROR_CODE cfg_upgrade_from_old(void)
{
	DEBUG_PRINT_FUNCTION_NAME(NORMAL,"OLD CONFIG UPDATE");
	
	char id[32];
	cfg_old_get_aws_id(id,sizeof(id));
	id[31]=0;
	debug_string_1P(NORMAL,PSTR("[INFO] AWSID is "));
	debug_string(NORMAL,id,RAM_STRING);
	debug_string_1P(NORMAL,g_szCRLF);

	char tmp[sizeof(cfg_template)];

	memcpy_P(tmp,cfg_template,sizeof(cfg_template));
	
	strcpy(tmp+0x110,id);
	strcpy(tmp+0x1B9,id);

	nvm_eeprom_erase_and_write_buffer(0,tmp,sizeof(cfg_template));
	delay_s(1);
	
	return AC_ERROR_OK;
}

