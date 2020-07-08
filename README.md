# binary-clock
Time and date in binary values on a 8x8 LED Matrix

## Why?
This is a one weekend project I started because I was curious how much information I could display on a 8x8 matrix. From my experiments I realized it is difficult to display more than 2 characters at the same time with a correct readability on such matrix. The only way I found was to display values in [binary system](https://en.wikipedia.org/wiki/Binary_number) instead of base 10. I was worried about the understandability but since the dots are padded in the matrix I use, it is not a problem. I fact it's even fun to do the little math when I want to know what time it is.

## Stack
- Wemos D1 Mini
- Wemos 8x8 LCD Matrix Shell
- Solder
- Scrap wood
- VS Code with PlatformIO
- Mini USB cable

## How to read the matrix

|        | 1 | 2 | 4 | 8 | 16 | 32 |   | Weekday |           |
|--------|---|---|---|---|----|----|---|---------|-----------|
| Hour   | • | • | • |   | •  |    |   |         | Sunday    |
|        |   |   |   |   |    |    |   |         | Monday    |
| Minute |   |   | • | • |    | •  |   |         | Tuesday   |
|        |   |   |   |   |    |    |   | •       | Wednesday |
| Second | • | • |   | • | •  |    |   |         | Thursday  |
|        |   |   |   |   |    |    |   |         | Friday    |
| Day    |   |   |   | • |    |    |   |         | Saturday  |
| Month  | • | • | • |   |    |    |   |         |           |

In this example, time is Wednesday 8th July 23:44:27.

## Workflow

### On setup
1) Display the loading message `Hi`.
2) Connect to one of the WiFi networks provided in `wifi_settings.h`.
3) Get current JST time from NTP server (syncs every hour).
4) Proceed to loop.

### On loop
1) Set time in time manipulation library.
2) Draw each time unit on their respective lines.
3) Set the dot for the weekday value.
4) Wait 500ms and start over.
