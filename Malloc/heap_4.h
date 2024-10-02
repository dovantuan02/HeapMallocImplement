#ifndef _heap_5_h
#define _heap_5_h

#include "stdio.h"
#include "stdint.h"
#include "assert.h"

#define configTOTAL_HEAP_SIZE       131072

#define configSUPPORT_DYNAMIC_ALLOCATION    1
#define portBYTE_ALIGNMENT                  32

#define configHEAP_CLEAR_MEMORY_ON_FREE     1

#define portMAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#define portPOINTER_SIZE_TYPE    size_t

#if portBYTE_ALIGNMENT == 32
    #define portBYTE_ALIGNMENT_MASK    ( 0x001f )
#elif portBYTE_ALIGNMENT == 16
    #define portBYTE_ALIGNMENT_MASK    ( 0x000f )
#elif portBYTE_ALIGNMENT == 8
    #define portBYTE_ALIGNMENT_MASK    ( 0x0007 )
#elif portBYTE_ALIGNMENT == 4
    #define portBYTE_ALIGNMENT_MASK    ( 0x0003 )
#elif portBYTE_ALIGNMENT == 2
    #define portBYTE_ALIGNMENT_MASK    ( 0x0001 )
#elif portBYTE_ALIGNMENT == 1
    #define portBYTE_ALIGNMENT_MASK    ( 0x0000 )
#else /* if portBYTE_ALIGNMENT == 32 */
    #error "Invalid portBYTE_ALIGNMENT definition"
#endif /* if portBYTE_ALIGNMENT == 32 */


#define PRIVILEGED_FUNCTION
#define PRIVILEGED_DATA
#define FREERTOS_SYSTEM_CALL

#define configASSERT(x)     assert((x))


#ifndef traceMALLOC
    #define traceMALLOC( pvAddress, uiSize )
#endif

#ifndef traceFREE
    #define traceFREE( pvAddress, uiSize )
#endif

#ifndef mtCOVERAGE_TEST_MARKER
    #define mtCOVERAGE_TEST_MARKER()
#endif


extern void * pvPortMalloc( size_t xWantedSize );
extern void * pvSafeMalloc( size_t xWantedSize );
extern void * pvPortCalloc( size_t xNum, size_t xSize );
extern void vPortFree( void ** pv );
extern size_t xPortGetFreeHeapSize( void );
extern void vPortHeapResetState( void );
#endif