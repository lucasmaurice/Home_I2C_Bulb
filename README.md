# homebridge-fake-rgb

An homebridge plugin that create an Fake RGB Bulb HomeKit accessory

## Installation

Follow the instruction in [homebridge](https://www.npmjs.com/package/homebridge) for the homebridge server installation. The plugin is published through [NPM](https://www.npmjs.com/package/homebridge-fake-rgb) and should be installed "globally" by typing:

```bash
npm install -g homebridge-fake-rgb
```

And clone this repository to your computer and replace files of original plugin :

```bash
cd ~/
mkdir FakeRGB-I2C
cd FakeRGB-I2C
git clone https://github.com/lucasmaurice/Home_I2C_Bulb.git
sudo cp -R * /usr/local/lib/node_modules/homebridge-fake-rgb

```

## Configuration

Remember to configure the plugin in config.json in your home directory inside the .homebridge directory.

```json
"accessories": [{
    "accessory": "Fake-RGB",
    "name": "RGB Bulb",
    "address": 8,
    "bulbNbr": 2,
    "radioNbr": 2
}]
```

### Configuration parameters:

- "accessory": "Fake-RGB",
- "name": Name of the bulb _(default value : 8)_, 
- "address": Adress I2C of the Arduino,
- "bulbNbr": ID of the bulb,
- "radioNbr": Adress RF if you use RF receptors _(If you dont use RF module, set to 0)_


Look for a sample config in [config-sample.json example](https://github.com/lucasmaurice/Home_I2C_Bulb/blob/master/config-sample.json)

### TODO:
Will need to change I2C to Serial communication, for support more server platforms.
