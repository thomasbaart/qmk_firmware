#include "trackball.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "pointing_device.h"
#include <avr/interrupt.h>

//Trackball pin defs
// #define TRKUP B1
// #define TRKDN B2
// #define TRKLT B3 
// #define TRKRT B4

#define TRKUP (1<<1)
#define TRKDN (1<<2)
#define TRKLT (1<<3) 
#define TRKRT (1<<4)

// Multiple for mouse moves
#ifndef TRKSTEP
#define TRKSTEP 20 
#endif

// multiple for mouse scroll
#ifndef SCROLLSTEP
#define SCROLLSTEP 3
#endif

// bit masks
#define TRKMASK   (TRKUP | TRKDN | TRKRT | TRKLT)

// Trackball interrupts accumulate over here. Processed on scan
// Stores prev state of mouse, high bits store direction
uint8_t trkState    = 0; 

volatile uint8_t tbUpCnt  = 0; 
volatile uint8_t tbDnCnt  = 0; 
volatile uint8_t tbLtCnt  = 0; 
volatile uint8_t tbRtCnt  = 0; 

static void enableInterrupts(void);

uint8_t matrix_scan_trackball(void)
{
  // TODO: Find what is trashing interrupts
  enableInterrupts();

  // First we handle the mouse inputs
  // Modify the report
  report_mouse_t pRprt = pointing_device_get_report();

  // Scroll by default, move on layer
  if (layer_state == 0) {
    pRprt.h += tbLtCnt * SCROLLSTEP; tbLtCnt = 0;
    pRprt.h -= tbRtCnt * SCROLLSTEP; tbRtCnt = 0;
    pRprt.v -= tbUpCnt * SCROLLSTEP; tbUpCnt = 0;
    pRprt.v += tbDnCnt * SCROLLSTEP; tbDnCnt = 0;
  } else {
    pRprt.x -= tbLtCnt * TRKSTEP * (layer_state - 1); tbLtCnt = 0;
    pRprt.x += tbRtCnt * TRKSTEP * (layer_state - 1); tbRtCnt = 0;
    pRprt.y -= tbUpCnt * TRKSTEP * (layer_state - 1); tbUpCnt = 0;
    pRprt.y += tbDnCnt * TRKSTEP * (layer_state - 1); tbDnCnt = 0;
  }

  // Save state, push update
  if (pRprt.x != 0 || pRprt.y != 0 || pRprt.h != 0 || pRprt.v != 0) { // || (trkBtnState != pBtn)) 
    pointing_device_set_report(pRprt);
  }
  
  enableInterrupts();
  return 1;
}

// Trackball Interrupts
static void enableInterrupts(void) {
    // Set interrupt mask
    // Set port defs
    DDRB &= ~TRKMASK;
    PORTB |= TRKMASK;

    // Interrupt shenanigans
    //EIMSK |= (1 << PCIE0);
    PCMSK0 |= TRKMASK;
    PCICR |= (1 << PCIE0);
    sei();

    return;
}

ISR (PCINT0_vect) {
  // Don't get fancy, we're in a interrupt here
  // PCINT reports a interrupt for a change on the bus
  // We hand the button at scantime for debounce
  volatile uint8_t pState = PINB & TRKMASK;
  if ((pState & TRKUP) != (trkState & TRKUP)) tbUpCnt++;
  if ((pState & TRKDN) != (trkState & TRKDN)) tbDnCnt++;
  if ((pState & TRKLT) != (trkState & TRKLT)) tbLtCnt++;
  if ((pState & TRKRT) != (trkState & TRKRT)) tbRtCnt++;
  trkState = pState;
}