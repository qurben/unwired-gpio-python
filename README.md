# Unwired One gpio Python bindings

Python bindings for the Unwired One's gpio.

## Compiling

To setup a build environment to build for the Unwired One see [C/C++ Building Environment][2] on the Unwired One wiki.

When you have a working installation, place this repository in the `openwrt/package` folder or create a symlink to this repository in that folder.

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
