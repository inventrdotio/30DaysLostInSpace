# Day 11 - "Starting Your Control Panel"

[![video](https://github.com/inventrdotio/AdventureKit30Days/blob/main/Youtube.png)](https://www.youtube.com/watch?v=0IulLD1Q1ZM&list=PL-ykYLZSERMSZFH8_4zQx4BMWpt4aG1kr&index=11)

## Story Synopsis:

Placeholder example: After Just getting your power systems back online and a light to see again, you need to look for a way to save that last bit of remaining battery power remaining until you can deploy the solar panels.... or else it's game over!:

Comic-Style Graphic:
![Art](https://github.com/inventrdotio/AdventureKit30Days/blob/main/Art/sample.jpg "Art")

```
const byte ROWS = 4; 
const byte COLS = 4; 

char buttons[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
```

### Wiring Diagram:
| Arduino | 4x4 Keypad |
| --- | --- |
| 2 | R4 |
| 3 | R3 |
| 4 | R2 |
| 5 | R1 |
| 6 | C1 |
| 7 | C2 |
| 8 | C3 |
| 9 | C4 |

<img src="Day11.png" width="350">

### Installation
4x4 Keypad Library Required: [Download](inventr.io/libraries)
