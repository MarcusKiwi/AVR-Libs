# AVR-Libs

Libs for AVR-C to simplify using UART, I2C, LCD's and more.

Includes a reusable makefile addressing some of the peculiarities of AVR development.

Faster than Arduino libs but requires a more advanced understanding of C to use.

# Instructions

Download AvrLibs and unzip it into its own folder. Edit the makefile and set up your programmer type.

Create a new project folder with its own C files as you normally would. Save the example below as "makefile" in this folder. Change it to suit your project.

```
MCU   = atmega328p
LIBS  = 
F_CPU = 8000000
BAUD  = 9600
include ~/Code/AVR-Libs/makefile
```

Use these commands to build your project:

`make` - Compiles a HEX file for the project.  
`make install` - Compiles a HEX file and writes it to the AVR.  
`make clean` - Deletes compiled (O, ELF, HEX) files.  

To add libraries to your project #include them as you normally would, and add their file names (without extension) to the LIBS line of the makefile. Example: `LIBS = i2c serial`

For info on how to use a library read the comments in its header file.

Some libraries depend on other libraries, these are listed in the header files.

# Makefile Features

Each project has its own short and simple to configure makefile. All the complex ugly stuff is tucked away in a shared makefile.

Only compiles the libraries your project needs in your HEX file. Most makefiles I've seen include everything. Including everything is easier, but it wastes a lot of program memory on stuff your project doesn't use. Or worse, tries to compile for things your AVR might not have (eg: ATtiny and UART).

Always recompiles your entire project and produces a single .HEX file. Compiling is extremely fast for AVR. Recycling .O files with AVR is more hassle than it's worth.

Displays program and data memory use estimates using avr-size.

Can flash/install HEX file using avrdude.

# Using Libraries Without The Makefile

In theory these libraries should work fine without the makefile.

1. Download the files for the hardware you want to use.
2. Check the header file for #included libraries it depends on (fonts, I2C, UART, etc) and get these too.
3. Dump all these files into your main code folder. Alongside main.c is fine.
4. Compile with options `-DF_CPU=8000000UL -DBAUD=9600UL` adjust as necessary.
