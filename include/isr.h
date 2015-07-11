/*
 * A set of macros used to define interrupt service routines.
 * I decided to go with two stage ISRs, the first stage runs `pushad' and `iret'
 * and calls the second stage in between. This allows us to write ISRs in C, and
 * just wrap them in assembly with a macro.
 *
 * TODO: Perhaps make this work with clang too?
 */
#ifndef _ISR_H
#define _ISR_H

#include <quote.h>

#define __ISR_PREFIX __isr_

/*
 * When defining an ISR, we define a regular C function, and then wrap it in
 * assembly. The wrapped function is named AS_ISR(symbol). To address it, call
 * AS_ISR first.
 */
#define AS_ISR(symbol) CONCAT(__ISR_PREFIX, symbol)

/*
 * Define an interrupt service routine wrapper.
 */
#define ISR(symbol) \
    __asm__ \
    ( \
      ".text\n" \
	  ".globl " QUOTE(AS_ISR(symbol)) "\n" \
      ".align 4\n" \
	  ".type "  QUOTE(AS_ISR(symbol)) ", @function\n" \
      QUOTE(AS_ISR(symbol)) ":\n" \
      "     pushad\n" \
      "     cld\n" \
      "     call " #symbol "\n" \
      "     popad\n" \
      "     iret\n" \
    ); \
    void AS_ISR(symbol)(void);

#endif /* ! defined(_ISR_H) */
