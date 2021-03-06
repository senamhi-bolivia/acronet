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


#ifndef PCAL9554B_H_
#define PCAL9554B_H_


//RET_ERROR_CODE PCAL9554B_Init(void);



RET_ERROR_CODE PCAL9554B_Write( const uint8_t cmd, const uint8_t data );
RET_ERROR_CODE PCAL9554B_Read( const uint8_t cmd, uint8_t * const data );
#endif /* PCAL9554B_H_ */