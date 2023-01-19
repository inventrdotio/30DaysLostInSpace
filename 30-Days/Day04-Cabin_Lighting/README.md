# Day 4 - "Cabin Lighting"

[![video](https://github.com/inventrdotio/AdventureKit30Days/blob/main/Youtube.png)](https://www.youtube.com/watch?v=0IulLD1Q1ZM&list=PL-ykYLZSERMSZFH8_4zQx4BMWpt4aG1kr&index=4)

## Story Synopsis:

Placeholder example: After Just getting your power systems back online and a light to see again, you need to look for a way to save that last bit of remaining battery power remaining until you can deploy the solar panels.... or else it's game over!:

Comic-Style Graphic:
![Art](https://github.com/inventrdotio/AdventureKit30Days/blob/main/Art/sample.jpg "Art")

```
 void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Light1, OUTPUT);
  pinMode(Light2, OUTPUT);
  pinMode(Light3, OUTPUT);
  pinMode(SWITCH1, INPUT);
  pinMode(SWITCH2, INPUT);
  pinMode(SWITCH3, INPUT);
}
```

### Wiring Diagram:
| Arduino | Buzzer |
| --- | --- |
| 2 | + |
| GND | other |

<img src="Day4.jpg" width="350">

### Installation
No libraries or includes required.
