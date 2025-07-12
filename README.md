# Arduino-RFID-Access-With-LED

Hi, my name is Rahmat Hidayat. I code for fun and sometimes share my code here so I can reuse it later.  
Feel free to use or modify this project. If you need help setting it up, follow this tutorial.

## Required Materials
- Arduino Uno / Nano / Mega
- MFRC522 RFID Module (RC522)
- Breadboard
- 10 Jumper wires (Male to Male)
- 2 LED (Red & Green)
- 2 Resistors (220Ω–330Ω recommended)

## Wiring

### RFID RC522
| RFID Pin | Arduino Pin |
|----------|-------------|
| SDA      | 2           |
| SCK      | 13          |
| MOSI     | 11          |
| MISO     | 12          |
| RST      | 3           |
| 3.3V     | 3.3V        |
| GND      | GND         |

### LEDs
| LED | Arduino Pin | Via Resistor |
|-----|-------------|--------------|
| Red | 4           | 220Ω         |
| Green | 5         | 220Ω         |

## How to Use
1. Download the code from the `Tags` section or copy from this repo.
2. Open it with Arduino IDE.
3. Select your board (`Tools -> Board -> Arduino Uno`) and port (`Tools -> Port`).
4. Upload.
5. Tap your RFID card on the module.
6. Green LED will light up for a few seconds (access granted), then return to Red LED (standby).

## Code Highlights
- Using `MFRC522` library to handle RFID reading.
- When a card is detected, green LED lights up for `SesionMaxTimePerScan` seconds.
- Red LED stays on while waiting for a new card.

```cpp
void LEDtoggle() { /* Toggle Red & Green */ }
void LEDsetState(int red, int green) { /* Set LED state */ }
void RFIDgrantAccess() { /* Grant access */ }
void RFIDungrantAccess() { /* Ungrant access */ }
```

# Debugging
- Serial Monitor set to 250000 baud. Shows UID of card & LED states.

**License**: MIT

Thanks for reading! 
