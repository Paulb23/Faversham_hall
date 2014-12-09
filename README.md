Faversham hall
=============

A 2d detective game written by Paul, Harry , Naomi, Tom and Zhidong

<<<<<<< HEAD
=======
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

Load and draw maps made in tiled using zlib x64 compression or csv   

**Timing**   
Get fps, ticks per second, delta time,  and uptime

To Do List / Planned Features
-----------  
- More advanced .tmx parser  
  - rename functions
  - load properties
  - load objects
  - load terrains
  - support background color
  - support, json, csv, uncompress, gzip and XML
  - lighitng support?
- Fix check boxes  
- Add Textboxes
- Audio support
- maths, and physics moduals
  - a*
  - raycasting
  - raytracing
  - tweens
  - collison
   - AABB
   - Circle
   - Pixel
- random / psudo random genorators
- more interface supports
- rethink inut handeling
  - maybe use callbacks
- reduce foot print
- add printf like function to draw fonts
- scale fonts and images
- support bitmap fonts
- asset loader
  - holds pointers to ssests so we don't have to load the same thing in multiple times
  - would be used form pre-loading images in maps ect
- support for texture packers
- cursor support
  - load from image
- cross platform 
- support sprties / animation
- particle effects
- better debug / logging
  - use level
- screen shake
- libgdx stage like callbackm for ticks(), render() and events()
- config file
- wrapper around dictionarys
- timers
  - callbacks?
  - coroutines
- lua scripting 
- image lighting
  - normal maps ect 
>>>>>>> ada909f2c03fb6e327ca132465cc156a95c8f11e
