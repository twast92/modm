// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2011, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
// ----------------------------------------------------------------------------
/*
 * WARNING: This file is generated automatically, do not edit!
 * Please modify the corresponding *.in file instead and rebuild this file.
 */
// ----------------------------------------------------------------------------


#include <avr/interrupt.h>
#include "timer_interrupt_f1.hpp"

#ifdef TCF1

xpcc::TimerInterruptF1::F xpcc::TimerInterruptF1::overflow=xpcc::dummy;
xpcc::TimerInterruptF1::F xpcc::TimerInterruptF1::error=xpcc::dummy;
xpcc::TimerInterruptF1::F xpcc::TimerInterruptF1::cca=xpcc::dummy;
xpcc::TimerInterruptF1::F xpcc::TimerInterruptF1::ccb=xpcc::dummy;


ISR(TCF1_ERR_vect)
{
	xpcc::TimerInterruptF1::error();
}

ISR(TCF1_OVF_vect)
{
	xpcc::TimerInterruptF1::overflow();
}

ISR(TCF1_CCA_vect)
{
	xpcc::TimerInterruptF1::cca();
}

ISR(TCF1_CCB_vect)
{
	xpcc::TimerInterruptF1::ccb();
}


// specific configuration combinations
void
xpcc::TimerInterruptF1::setMsTimer(F function, uint8_t interval)
{
	setClockSource(TC_CLKSEL_DIV64_gc);
	attachOverflowInterrupt(TC_OVFINTLVL_MED_gc, function);
	TCF1_PER = (interval * F_CPU) / 64000l;
}

bool
xpcc::TimerInterruptF1::attachCompareCaptureInterrupt(xpcc::timer::Channel channel, uint8_t level, F function)
{
	level <<= 2*channel;
	if (channel == xpcc::timer::CHANNELA) {
		attachCompareCaptureAInterrupt(static_cast<TC_CCAINTLVL_t>(level), function);
		return true;
	}
	else if (channel == xpcc::timer::CHANNELB) {
		attachCompareCaptureBInterrupt(static_cast<TC_CCBINTLVL_t>(level), function);
		return true;
	}
	return false;
}

#endif	// TCF1