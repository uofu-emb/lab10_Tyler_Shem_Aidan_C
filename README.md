Process we followed in lab:

Activity 1: We found the safe power supply voltage is between 1.8 - 5.5 V

Activity 2: Determine what the default values are for:
    - The two clock gate controlling registers:
      WAKE_EN
      SLEEP_EN
    They both reset to 0x1 upon reset meaning all clocks are on.
    
    - The clock enable registers ENABLED0 and ENABLED1 both reset to 0x1
      ENABLED is actually two registers ENABLED0 and ENABLED1 and they both reset to 0x0
Activity 3: Just read a tutorial about taking measurements with a multimeter
  - Turn off the power
  - Disconnect the multimeter power and ground from the board.
  - Connect USB.
  - Load the code for the scenario.
  - Disconnect your USB
  - Connect the multimeter power and ground back to the board
  - Turn on the power supply.
  - Record your measurments.

Activity 4: For each scenario, we created multiple tasks within the same file called "hello_freertos.c" and measured the power consumption of each task.

 - Task 1: Blink an LED using sleep_ms to delay iterations
     We observed 3.2 V between Vsys and Vgnd and ~20 micro amps flowing accross the Vgnd terminal.
     Using P = IV, P ~= 64 microWatts