/**************************************************************************/
/*!
    @brief  Init interrupt
*/
/**************************************************************************/
void _isr_init()
{
  // external interrupt
  DBG_P(F("Init Interrupt... "));

  // Setup flags to activate the ISR PCINT2.
  PCICR |= (1 << PCIE2); // This enables Pin Change Interrupt 2 that covers the Analog input pins or Port K
  PCMSK2 |= (1 << PCINT16) | (1 << PCINT17) | (1 << PCINT20) | (1 << PCINT21); // This enables the interrupt for pins of Port K.
  DBG_P(F("Done.\n"));

  // Initialize Timer, attach interrupt routine
  DBG_P(F("Init Timer... "));
  Timer1.initialize(TIMER_INT_US); // every n microseconds
  Timer1.attachInterrupt(_isr_timer);
  DBG_P(F("Done.\n"));
}


/**************************************************************************/
/*!
    @brief  Function is called on overflow of Timer1 (every second)
*/
/**************************************************************************/
void _isr_timer()
{
  // Set bits
  bitSet(ucTimerInterruptMask, TIMER_UPDATE);
}


/**************************************************************************/
/*!
    @brief  The Interrupt Service Routine for Pin Change Interrupt 2.
    @brief  This routine will only be called on any signal change on PORT K.
*/
/**************************************************************************/
ISR(PCINT2_vect)
{
  // just call tick() to check the state.
  main_encoder->tick();
  aux_encoder->tick();
}
