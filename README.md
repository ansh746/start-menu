# 👀 What is this? 
___
A custom start menu for Fire Red.

## ✨ Features
- BW styled UI
- Configurable to add more than 6 default options.

# ❓ How to use?
___
Same as CFRU, `python 3.6+` and `devkitARM` are required to compile.<br>

### 💾  Adding your rom  
Copy your rom to this directory and rename it to `BPRE0.gba`

### ⚙️ Configuration 
**Compile Time Constants** <br>
Open [scripts/make.py](https://github.com/ansh860/start-menu/blob/bw/scripts/make.py#L12) in a text editor to set some compile-time configuration.
The build system is smart enough to find enough free space on its own, and if you want it to be inserted at a particular address, you can specify it by updating the definition of `OFFSET_TO_PUT`:

```python
OFFSET_TO_PUT = 0x1C88650
SEARCH_FREE_SPACE = True   # Set to True if you want the script to search for free space
                           # Set to False if you don't want to search for free space as you for example update the engine
```

The build system will use `OFFSET_TO_PUT` to determine where in the ROM it should start looking for free space if `SEARCH_FREE_SPACE` is `True`.  Otherwise, the build system places the code to insert directly at `OFFSET_TO_PUT`.

### 🛠️ Building The Project
Once you are ready run:
```shell
$ python scripts/make.py
```
The code will start compiling, and generate a output rom `test.gba` in same directory.
Naturally, test it in an emulator.

### ➕ Adding New Options To Start Menu

....
