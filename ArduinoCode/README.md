# Arduino Code for Home-Fake-RGB
In order to use this module you'll need an arduino with a specific program burned in.

## Without RF Module
If you do not need to use the RF module, you just need the server code
Remove all the lines between :

```cpp
//YOU NEED TO OVERWRITE THE FOLLOWING LINES:
```
and the next 
```cpp 
//STOP
```

Set the macro definition USERF to false :
```cpp
#define USERF false
```

## How to use received data:
All data received where stored in an array of bytes.
Some keys where already defined to simplify the access of good lines in the array :
* **KEYRED** : Read the __RED__ intensity
* **KEYGREEN** : Read the __GREEN__ intensity
* **KEYBLUE** : Read the __BLUE__ intensity
* **KEYBULB** : Read the bulb number
* **KEYRADIO** : Read the radio adress (only if you use radio modules)

In order to access the data just use the following command :
```cpp
byte bValue = bMessage[THEKEY];
```
