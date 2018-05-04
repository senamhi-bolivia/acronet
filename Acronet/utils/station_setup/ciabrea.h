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


//Pluviometro
//VP61

#ifndef CIABREA_H_
#define CIABREA_H_

#define USES_PULSE_CHAN_0
#define USES_ADC_CHAN_0

#define MODULE_DECLARATION ((MOD_ID_RAINGAUGE,(PULSE_CHAN_0)))((MOD_ID_VP61,(ADC_CHAN_0)))


#define SP336_MODE					SP336_MODE_HIGHZ
#define SP336_2_MODE				SP336_2_MODE_HIGHZ

#define CV7L_PUSART					(&SP336_USART0)
#define CV7L_PIN_TX_ENABLE			SP336_USART0_PIN_TX_ENABLE
#define CV7L_PIN_TX_SIGNAL			SP336_USART0_PIN_TX_SIGNAL
#define CV7L_PIN_RX_SIGNAL			SP336_USART0_PIN_RX_SIGNAL

#define L8095N_PUSART				(&SP336_USART1)
#define L8095N_PIN_TX_ENABLE		SP336_USART1_PIN_TX_ENABLE
#define L8095N_PIN_TX_SIGNAL		SP336_USART1_PIN_TX_SIGNAL
#define L8095N_PIN_RX_SIGNAL		SP336_USART1_PIN_RX_SIGNAL

#define L8095N_SEC_PUSART			(&SP336_USART0)
#define L8095N_SEC_PIN_TX_ENABLE	SP336_USART0_PIN_TX_ENABLE
#define L8095N_SEC_PIN_TX_SIGNAL	SP336_USART0_PIN_TX_SIGNAL
#define L8095N_SEC_PIN_RX_SIGNAL	SP336_USART0_PIN_RX_SIGNAL

#define LB150_PUSART					(&SP336_USART0)
#define LB150_PIN_TX_ENABLE			SP336_USART0_PIN_TX_ENABLE
#define LB150_PIN_TX_SIGNAL			SP336_USART0_PIN_TX_SIGNAL
#define LB150_PIN_RX_SIGNAL			SP336_USART0_PIN_RX_SIGNAL

#define PM10QBIT_PIN_RX_SIGNAL		SP336_USART0_PIN_RX_SIGNAL

#define VP61_VOLTMETER				ADCA
#define VP61_VOLTMETER_CH			ADC_CH0
#define VP61_VOLTMETER_PIN_POS		ADCCH_POS_PIN4
#define VP61_VOLTMETER_PIN_NEG		ADCCH_POS_PIN0


#endif /* CIABREA_H_ */