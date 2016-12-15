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
Every data reception, the function __void receiveEvent(int howMany)__ is executed.
That mean that every instruction on Siri bulb, this will run.
You need to add your code after the comment in that function :

```cpp
void receiveEvent(int howMany) {
  static uint8_t bMessage[SIZE_MSG];
  static uint8_t addr_emit[5]={'n','r','f','0','0'};

  if(howMany>=SIZE_MSG){
    for(int iLoop=0; iLoop<SIZE_MSG; iLoop++){
       bMessage[iLoop]=Wire.read();
    }
    //ENTER HERE WHAT TO DO ON I2C DATA RECEPTION:

    //YOU NEED TO OVERWRITE THE FOLLOWING LINES:
    addr_emit[3]='0'+(bMessage[KEYRADIO]/10)%10;
    addr_emit[4]='0'+ bMessage[KEYRADIO]%10;
    while(Mirf.isSending());
    Mirf.setTADDR(addr_emit); // Adresse de transmission
    Mirf.send(bMessage);
    //STOP
  }
  delay(100);
}
```

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

## Wiring Raspberry and Arduino
Wire Raspberry and Arduino as below :
!(Wiring)(Wiring_Server.png)
