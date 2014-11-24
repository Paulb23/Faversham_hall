SSL - Simple SDL library
=============

A simple abstraction from SDL2 that handles a lot of the hard work.

**Attention!**  
Supports windows only at the monment.
 
Installation
-----------
Simply download or fork the repo and include SSL/SSL.h
Make sure to call SSL_Init() before using the libary

**Libaries needed**  
*SDL2    
*SDL Image  
*SDL TTF    
*SDL Mixer  

Documentation
-----------
Documentation can be found under doc/ and will open in any browser.

File System
-----------

**doc/**             
documentation  

**extras/**          
the error log file

**src/SSL**            
the source files   

Features
-----------

**Hashmap**  

A simple hashmap system.

**Ini parser**  

Parses standed ini files

**Window Handler**  

Manage a lot of windows with ease.

**Image / sprite handler**  

Loads and draw images and animationsl

**Font handler**  

Loads and draws .ttf fonts

**logger**  

Log errors to a file

**Input**  

Mouse and keyboard

**Interfaces and buttons**  

button and check box support   

**Tiled .tmx parser**  

Load and draw maps made in tiled using zlib x64 compression   

**Timing**   
Get fps, ticks per second, delta time,  and uptime

To Do List / Planned Features
-----------  
- More advanced .tmx parser  
- Fix check boxes  
- Add Textboxes
- Timing
- Audio support
- Demo game
