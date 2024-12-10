## Process we followed in lab:
### Activity 1: We found the safe power supply voltage is between 1.8 - 5.5 V

### Activity 2: Determine what the default values are for:
    - The two clock gate controlling registers:
      WAKE_EN
      SLEEP_EN
    They both reset to 0x1 upon reset meaning all clocks are on.
    
    - The clock enable registers ENABLED0 and ENABLED1 both reset to 0x1
      ENABLED is actually two registers ENABLED0 and ENABLED1 and they both reset to 0x0
     
### Activity 3: Just read a tutorial about taking measurements with a multimeter
  - Turn off the power
  - Disconnect the multimeter power and ground from the board.
  - Connect USB.
  - Load the code for the scenario.
  - Disconnect your USB
  - Connect the multimeter power and ground back to the board
  - Turn on the power supply.
  - Record your measurments.

### Activity 4: For each scenario, we created multiple tasks within the same file called "hello_freertos.c" and measured the power consumption of each task.
We are using a 2.2k resistor
 - Task 1: Blink with Sleep
    We observed 3.3 V between Vsys and Vgnd and ~35 micro amps flowing accross the Vgnd terminal.
    Using P = IV, P ~= 115.5 microWatts
 - Task 2: Blink with FreeRTOS Task
    We observed 3.3 V between Vsys and Vgnd and ~40 mA flowing accross the Vgnd terminal.
    Using P = IV, P ~= 132 mA
 - Task 3: 100% CPU Utilization
    We observed 3.3 V between Vsys and Vgnd and ~28.7 mA flowing accross the Vgnd terminal.
    Using P = IV, P ~= 95 mW
 - Task 4: Blink with Interrupt
    We observed 3.3 V between Vsys and Vgnd and ~33.8 mA flowing accross the Vgnd terminal.
    Using P = IV, P ~= 112 mW
 - Task 5: Sleep Demo
    We observed 3.3 V between Vsys and Vgnd and ~30 mA flowing accross the Vgnd terminal.
    This dropped to ~2.4 mA after sleep mode started.
    Using P = IV, P ~= 100 mW before sleep, ~= 8 mW after.
 - Task 6: Dormant Demo
    We observed 3.3 V between Vsys and Vgnd and ~30 mA flowing accross the Vgnd terminal.
    This dropped to ~1.2 mA after dormant mode started.
    Using P = IV, P ~= 100 mW before dormant, ~= 4 mW after.