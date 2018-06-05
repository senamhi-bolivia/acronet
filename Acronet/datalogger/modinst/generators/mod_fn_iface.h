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


#define DECLARATION_ITER BOOST_PP_SEQ_ELEM(BOOST_PP_FRAME_ITERATION(1),MODULE_DECLARATION)
#define REGISTRY_ITER BOOST_PP_TUPLE_ELEM(2,0,DECLARATION_ITER)
#define MODULE_NAME BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_SEQ_ELEM(REGISTRY_ITER, MODULE_REGISTRY))
#define MODULE_HEADER_FILE BOOST_PP_TUPLE_ELEM(3,2,BOOST_PP_SEQ_ELEM(REGISTRY_ITER, MODULE_REGISTRY))

#undef MODULE_PUBLIC_DATATYPE
#undef MODULE_INTERFACE_INIT
#undef MODULE_INTERFACE_ENABLE
#undef MODULE_INTERFACE_DISABLE
#undef MODULE_INTERFACE_YIELD 
#undef MODULE_INTERFACE_RESET
#undef MODULE_INTERFACE_GETDATA
#undef MODULE_INTERFACE_DATA2STRING
#undef MODULE_INTERFACE_DATA2STRING_RMAP
#undef MODULE_CHANNEL_GLUE_FILE
#undef MODULE_INTERFACE_PERIODIC
#undef MODULE_CMD_FILTER


#define MODULE_INSPECTION_PHASE
#include MODULE_HEADER_FILE
#undef MODULE_INSPECTION_PHASE

#define MODULE_ISTANCES BOOST_PP_TUPLE_ELEM(2,1,DECLARATION_ITER)
#define BOOST_PP_ITERATION_PARAMS_2 (3, (0, BOOST_PP_SEQ_SIZE(MODULE_ISTANCES)-1, "Acronet/datalogger/modinst/generators/mod_fn_iface2.h"))
#include BOOST_PP_ITERATE()

#undef MODULE_ISTANCES
#undef MODULE_HEADER_FILE
#undef MODULE_NAME
#undef REGISTRY_ITER
#undef DECLARATION_ITER
