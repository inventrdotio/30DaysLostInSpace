# Day 3 - "I'm Worried About Your Battery Levels"


[![video](https://github.com/inventrdotio/AdventureKit30Days/blob/main/Youtube.png)](https://www.youtube.com/watch?v=0IulLD1Q1ZM&list=PL-ykYLZSERMSZFH8_4zQx4BMWpt4aG1kr&index=3)

## Story Synopsis:

Placeholder example: After Just getting your power systems back online and a light to see again, you need to look for a way to save that last bit of remaining battery power remaining until you can deploy the solar panels.... or else it's game over!:

Comic-Style Graphic: <br>
![Art](https://github.com/inventrdotio/AdventureKit30Days/blob/main/Art/sample.jpg "Art")


## Code-Snippet
```
  void setup() {
    pinMode(LED, OUTPUT);
    pinMode(Switch1, INPUT);
  }

  void loop() {
    if (digitalRead(Switch1) == 1){
      digitalWrite(LED, HIGH); // 5V  
    }
    else {
      digitalWrite(LED, LOW); // GROUND
    }
  }
```

### Wiring Diagram:
| Arduino | LED |
| --- | --- |
| 12 | Long Wire |
| GND | Short Wire |

<img src="Day3.png">

### Installation
No libraries or includes required.