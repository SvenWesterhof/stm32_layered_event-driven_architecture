# STM32 Embedded Project - Professionele Architectuur

Een productie-grade embedded firmware project dat industry best practices demonstreert voor de STM32F767 microcontroller met volledige architecturele scheiding, event-driven ontwerp en complete portabiliteit.

## Projectoverzicht

Dit project implementeert een temperatuurmonitoringsysteem met displayuitvoer en LED-besturing, waarbij een "layered event-driven architecture wordt getoond.

### Functies
- Real-time temperatuur- en vochtigheidsmeting (ATH25 sensor via I2C)
- IPS display uitvoer (ST7735 via SPI)
- LED-knipperbediening
- Event-driven communicatie
- Volledige hardware-abstractie

---

## Architectuur

Het project volgt architectuur met strikte afhankelijkheden die alleen naar beneden gelden, wat zorgt voor lage koppeling en hoge portabiliteit.

![Architectuur Diagram](docs/images/SW-embedded%20layered-event-driven%20style.png)

### Laagbeschrijving

**Application Layer (Applicatielaag)**
- Hoogwaardige orkestratie van het systeem
- Initialisatie van subsystemen
- Hoofdbesturingslus

**Middleware Layer (Middlewarelaag)**
- **Services**: Bieden specifieke mogelijkheden (sensor uitlezen, displaybeheer, LED-besturing)
- **Control**: Bedrijfslogica en besluitvorming (momenteel voorbereid voor toekomstig gebruik)

**Event Bus (OS Layer)**
- Publisher-subscriber patroon voor communicatie
- Asynchrone event queue
- Ontkoppelde communicatie tussen services

**Drivers & BSP Layer**
- **BSP (Board Support Package)**: Board-specifieke initialisatie, LED-besturing, toegang tot peripherals
- **Custom Drivers**: Device-specifieke drivers (ATH25 temperatuursensor, IPS display, ST7735 controller)

**Hardware Abstraction Layer (HAL)**
- Platform-onafhankelijke interface
- GPIO, I2C, SPI, Delay abstracties
- Wikkelt vendor HAL (STM32 HAL)

**Hardware**
- STM32F767ZI microcontroller
- Peripherals: GPIO, I2C2, SPI1

---

## Belangrijkste Sterke Punten

### 1. **Volledige Scheiding van Verantwoordelijkheden (Separation of Concerns)**

Elke laag heeft één goed gedefinieerde verantwoordelijkheid:

- **Application**: Systeeminitialisatie en orkestratie van de hoofdlus
- **Services**: Bieden specifieke mogelijkheden (sensor uitlezen, displaybeheer, LED-besturing)
- **Control**: Bedrijfslogica en besluitvorming (momenteel voorbereid voor toekomstig gebruik)
- **Event Bus**: Ontkoppelde communicatie tussen componenten
- **BSP**: Board-specifieke hardwareconfiguratie
- **Custom Drivers**: Device-specifieke drivers (sensor, display)
- **HAL**: Platformabstractie

### 2. **Volledige Portabiliteit**

De architectuur is ontworpen voor **complete platformonafhankelijkheid**:

#### ✅ **100% Draagbare Lagen**
- **Application** - Geen hardware-afhankelijkheden
- **Middleware (Services)** - Gebruikt alleen BSP en HAL abstracties
- **Event Bus** - Platform-agnostisch eventsysteem
- **Custom Drivers** - Generieke I2C/SPI device drivers

#### ⚠️ **Platform-Specifieke Lagen** (Zoals Ontworpen)
- **BSP** - Board-specifiek (pinout, peripheralconfiguratie)
- **HAL** - Platform-specifieke abstractie-implementatie

**Om te porteren naar een ander MCU/platform:**
1. Herimplementeer HAL-laag (hal_gpio.c, hal_i2c.c, etc.)
2. Update BSP-laag (pinout.h, bsp.c)
3. **Alle andere lagen blijven ongewijzigd!**

### 3. **Event-Driven Architectuur**

Implementeert **publisher-subscriber patroon** voor lage koppeling:

```c
// Services publiceren events (geen kennis van consumenten)
event_bus_publish(EVENT_TEMPERATURE_UPDATED, &data, sizeof(data));

// Andere services abonneren zich en reageren
event_bus_subscribe(EVENT_TEMPERATURE_UPDATED, on_temperature_handler);
```

**Voordelen:**
- Services weten niets van elkaar
- Gemakkelijk nieuwe subscribers toe te voegen (logging, netwerk, opslag)
- Testbaar in isolatie

### 4. **Geen Laagschendingen**

Strikte naleving van **alleen neerwaartse afhankelijkheden**:

Application → Middleware  
Middleware → Event Bus / BSP  
BSP → HAL  
HAL → Hardware  

Geen opwaartse aanroepen  
Geen laag overslaan (behalve voor hulpfuncties zoals timing)

### 5. **Modulair & Testbaar**

- Elke service is onafhankelijk
- Mock HAL-laag voor unit testing
- Duidelijke interfaces tussen lagen
- Gemakkelijk functies toe te voegen/verwijderen

### 6. **Schaalbaar**

Klaar voor uitbreiding:
- Voeg meer sensors toe (abonneer op events)
- Voeg logging service toe
- Voeg netwerkcommunicatie toe
- Implementeer controle-algoritmen
- Integreer RTOS (FreeRTOS hooks zijn al aanwezig)

---

## Directory Structure

```
stm32_development/
├── Application/              # Application layer
│   ├── app_main.c           # Main application logic
│   ├── app_main.h
│   └── state_machine.c      # State machine implementation
│
├── Middleware/              # Middleware layer
│   ├── Services/            # Service implementations
│   │   ├── services.c       # Service registry
│   │   ├── serv_blinky.*    # LED control service
│   │   ├── serv_temperature_sensor.*  # Temperature sensor service
│   │   ├── serv_display.*   # Display service
│   │   └── service_events.h # Event data structures
│   └── Control/             # Control/business logic (prepared)
│       └── control.h
│
├── OS/                      # Event bus & OS utilities
│   ├── event_bus.*          # Publish-subscribe event system
│   └── os_tasks.*           # RTOS task definitions (prepared)
│
├── Drivers_BSP/            # Board Support Package & Drivers
│   ├── BSP/                # Board-specific code
│   │   ├── bsp.*           # Board initialization
│   │   └── pinout.h        # Pin definitions
│   ├── Custom/             # Custom device drivers
│   │   ├── ath25.*         # Temperature sensor driver
│   │   └── ips_display.*   # Display driver
│   └── External/           # Third-party drivers
│       └── ST7735/         # Display controller driver
│
├── HAL/                    # Hardware Abstraction Layer
│   ├── hal_gpio.*          # GPIO abstraction
│   ├── hal_i2c.*           # I2C abstraction
│   ├── hal_spi.*           # SPI abstraction
│   └── hal_delay.*         # Timing abstraction
│
├── Core/                   # STM32 CubeMX generated code
│   ├── Inc/
│   └── Src/
│
├── Drivers/                # STM32 HAL drivers (vendor)
│   ├── CMSIS/
│   └── STM32F7xx_HAL_Driver/
│
├── cmake/                  # Build system
│   └── gcc-arm-none-eabi.cmake
│
├── CMakeLists.txt          # Root CMake configuration
└── STM32F767XX_FLASH.ld    # Linker script
```

---

## Design Patterns Used

1. **Layered Architecture** - Clear separation of concerns
2. **Publisher-Subscriber** - Event-driven communication
3. **Hardware Abstraction** - Platform independence
4. **Service-Oriented** - Modular capabilities
5. **Dependency Inversion** - Upper layers depend on abstractions, not concretions

---

**Gebouwd met professionele architectuurprincipes voor productie-grade embedded systemen