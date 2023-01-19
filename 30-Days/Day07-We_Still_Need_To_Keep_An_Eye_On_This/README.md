# Day 7 - "We Still Need To Keep An Eye On This"

[![video](https://github.com/inventrdotio/AdventureKit30Days/blob/main/Youtube.png)](https://www.youtube.com/watch?v=0IulLD1Q1ZM&list=PL-ykYLZSERMSZFH8_4zQx4BMWpt4aG1kr&index=7)

## Story Synopsis:

Placeholder example: After Just getting your power systems back online and a light to see again, you need to look for a way to save that last bit of remaining battery power remaining until you can deploy the solar panels.... or else it's game over!:

Comic-Style Graphic:
![Art](https://github.com/inventrdotio/AdventureKit30Days/blob/main/Art/sample.jpg "Art")

```
void PrintBatteryPercentage() {
  Serial.print(((double)batteryLevel / (double)batteryCapacity)*100);
  Serial.println("%");
}
```

### Wiring Diagram:
| Arduino | Photoresisor |
| --- | --- |
| 2 | + |
| GND | other |

<img src="../Day6.png" width="350">

### Installation
No libraries or includes required.
