SUBSYSTEM == "input", GROUP = "input", MODE = "0666"
SUBSYSTEM == "usb", ATTRS{idVendor} == "054c", ATTRS{idProduct} == "0ce6", MODE := "666", GROUP = "plugdev"
KERNEL == "hidraw*", ATTRS{idVendor} == "054c", ATTRS{idProduct} == "0ce6", MODE = "0666", GROUP = "plugdev"
