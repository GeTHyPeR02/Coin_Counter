# Coin Counter

This is a simple Arduino-based coin counter program that keeps track of coins and their total value. The program uses an Arduino board, a 2x16 character LCD, few IR sensors for proximity and one simple button. </br>
The program utilizes the Arduino EEPROM to store the individual coin counts and the total value across power cycles.


## Features

- Count and display individual coin denominations (1 RSD, 2 RSD, 5 RSD, 10 RSD, and 20 RSD) on a 2x16 character LCD.
- Display the total value of all coins counted.
- Switch between individual coin count display and total value display using a button.
- Reset the coin count and total value by holding the button for more than 3 seconds.