# Sofle RGB v2.1

Sofle is a column-staggered split keyboard with a layout of 6×4+5 keys and encoder support, taking inspiration from the Lily58, Corne, and Helix keyboards. Sofle versions 1 and 2 were designed by [Josef Adamcik](https://josef-adamcik.cz), while the Sofle RGB version was contributed by [Dane Evans](https://github.com/DaneEvans).

## Build & Flash

After setting up your QMK Build build environment, you can utilize the following command to compile the firmware for this keyboard:

    make nhutdm/sofle/rev1:default

To flash this keyboard with compiled firmware, use the command:

    make nhutdm/sofle/rev1:default:avrdude-split-left
    make nhutdm/sofle/rev1:default:avrdude-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

You can enter the bootloader by briefly pressing the reset button on the side of the PCB, next to the TRRS socket.

## Features

The Sofle RGB v2.1 offers the following features:

- Compatibility with MX switches.
- Support for up to two 128×32 pixel OLED displays.
- Provision for up to one EC11 rotary encoder per half, placed in one of three potential positions.
- Individual per-key RGB backlighting using RGB LEDs.
- Underglow illumination using individual RGB LEDs.
