# iWhish - Christmas and Generic Music Player

A simple Arduino Nano-based music player that plays melodies through a buzzer, with start/stop control via a button and tempo adjustment via a potentiometer.

## Project Overview

This project demonstrates low-level AVR programming techniques by using direct register manipulation instead of Arduino framework helper functions, while still leveraging the Arduino environment for essential features like timing and interrupts.

## Project Structure

```
iWhish/
├── src/
│   └── main.cpp          # Main Arduino code with register-based I/O
├── include/
│   ├── Notes.h           # Note frequency definitions
│   └── merrychristmas.h  # Song melody data
├── python/
│   └── main.py           # Song header generator script
└── platformio.ini        # PlatformIO configuration
```

## Hardware Setup

| Component | Arduino Nano Pin | AVR Register |
|-----------|------------------|--------------|
| Buzzer (+) | D8 | PB0 |
| Button | D2 | PD2 (INT0) |
| Potentiometer | A0 | ADC0 |

## main.cpp - Register-Based Implementation

### Why Registers Instead of Arduino Functions?

Using direct register manipulation provides:
- **Lower memory footprint** - No overhead from Arduino wrapper functions
- **Faster execution** - Direct hardware access without function call overhead
- **Better understanding** - Learn how the ATmega328P microcontroller actually works
- **Fine-grained control** - Access to all hardware features

### Register Operations Explained

#### 1. Pin Configuration (DDRx, PORTx)

```cpp
// Set PB0 (Pin 8) as OUTPUT for buzzer
DDRB |= (1 << DDB0);
```
- **DDRB** (Data Direction Register B): Controls whether pins are input (0) or output (1)
- `(1 << DDB0)` creates a bitmask: `00000001`
- `|=` performs OR to set bit 0 without affecting other pins

```cpp
// Set PD2 (Pin 2) as INPUT with pull-up for button
DDRD &= ~(1 << DDD2);   // Clear bit = Input
PORTD |= (1 << PORTD2); // Set bit = Enable internal pull-up resistor
```
- **DDRD** (Data Direction Register D): Pin 2 direction control
- **PORTD** (Port D Data Register): When pin is input, writing 1 enables internal pull-up
- `&= ~(1 << DDD2)` clears bit 2 (makes it input)
- `|= (1 << PORTD2)` sets bit 2 (enables pull-up)

#### 2. ADC Configuration (ADMUX, ADCSRA)

```cpp
void initADC() {
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
```

**ADMUX Register:**
| Bit | Name | Value | Purpose |
|-----|------|-------|---------|
| 6 | REFS0 | 1 | Use AVCC (5V) as voltage reference |
| 3:0 | MUX | 0000 | Select ADC channel 0 (A0) |

**ADCSRA Register:**
| Bit | Name | Value | Purpose |
|-----|------|-------|---------|
| 7 | ADEN | 1 | Enable ADC |
| 2:0 | ADPS | 111 | Prescaler = 128 (16MHz/128 = 125kHz ADC clock) |

#### 3. Reading ADC Value

```cpp
uint16_t readADC(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);  // Select channel
    ADCSRA |= (1 << ADSC);                       // Start conversion
    while (ADCSRA & (1 << ADSC));                // Wait for completion
    return ADC;                                   // Return 10-bit result
}
```

- **ADSC** (ADC Start Conversion): Set to 1 to start, automatically clears when done
- **ADC**: 16-bit register containing the 10-bit conversion result (0-1023)

### What Still Uses Arduino Framework

| Feature | Reason |
|---------|--------|
| `millis()` | Uses Timer0 which Arduino configures at startup |
| `tone()` / `noTone()` | Handles Timer1 configuration for PWM audio |
| `attachInterrupt()` | Reliable interrupt vector management |
| `delay()` | Built on `millis()` infrastructure |

---

## main.py - Song Header Generator

A Python utility that automatically generates C header files from Arduino song sketches.

### What It Does

1. **Clones** the [robsoncouto/arduino-songs](https://github.com/robsoncouto/arduino-songs) repository
2. **Parses** each `.ino` file to extract:
   - Tempo value
   - Melody array (note/duration pairs)
3. **Generates** header files (`.h`) ready to include in the project

### Usage

```bash
cd python
./venv/bin/python3 main.py
```

### Output

Creates `generated_headers/` folder with files like:
- `merrychristmas.h`
- `jinglebells.h`
- `silentnight.h`
- ... and many more!

### Key Functions

| Function | Purpose |
|----------|---------|
| `ensure_repo()` | Clones the songs repository if not present |
| `sanitize_song_name()` | Converts folder name to valid C identifier |
| `extract_from_ino()` | Parses .ino file for tempo and melody |
| `build_header_content()` | Generates the .h file content |

---

## Building & Uploading

Using PlatformIO:

```bash
# Build
pio run

# Upload to Arduino Nano
pio run --target upload

# Monitor serial output
pio device monitor
```

## License

This project is for educational purposes. Song data is sourced from [robsoncouto/arduino-songs](https://github.com/robsoncouto/arduino-songs).
