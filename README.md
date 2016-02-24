# Unwired One gpio Python bindings

Python bindings for the Unwired One's gpio.

## Usage

Import `unwired.gpio`, the following methods are available.

`direction(gpio, direction)`: Set the direction of a gpio pin. `gpio` and `direction` are numbers. Make sure to use this, because the current state is unknown before calling it.

`set(gpio, value)`: Set the value of a gpio pin. `gpio` and `value` are numbers.

`read(gpio)`: Read the value of a gpio pin. `gpio` is a number.

### Example script 'Blinking Led'

```python
from unwired import gpio
from time import sleep

# Set pin 27 to output
gpio.direction(27, 1)

while True:
  gpio.set(27, 1)
  sleep(1)
  gpio.set(27, 0)
  sleep(1)
```

## Compiling

To setup a build environment to build for the Unwired One see [C/C++ Building Environment][2] on the Unwired One wiki.

When you have a working installation, place this repository in the `openwrt/package` folder or create a symlink to this repository in that folder.

Register the module in make menuconfig

```bash
make menuconfig
```

Create a `.ipk` file by running

```bash
make package/unwired-gpio-python/{prepare,compile}
```

from the `openwrt` folder.

You can find the `unwired-gpio-python_1_ar71xx.ipk` file in the `bin/ar71xx/packages/base/` folder, copy this file to your Unwired One and install it with

```bash
opkg install unwired-gpio-python_1_ar71xx.ipk
```


[2]: http://www.unwireddevices.com/wiki/index.php/C/C%2B%2B_Building_Environment
