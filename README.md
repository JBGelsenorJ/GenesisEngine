# Genesis Engine
  Genesis Engine is a game engine made in C and C++ for learning purposes. Originaly made by Marc Pagès Francesch (@marcpages2020). We (Javier D. Belda González (@JBGelsenorJ) & Silvino Medina Cardona (@silvino00) forked it to develop the 2º assignment for our videogame engines subject in the Development and Design of videogames degree, studied in the UPC.

  Javier D. Belda González Github: https://github.com/JBGelsenorJ
  Silvino Medina Cardona Github: https://github.com/silvino00
  Original Genesis Engine Repository: https://github.com/marcpages2020/GenesisEngine
  Forked Repository: https://github.com/JBGelsenorJ/GenesisEngine

## Controls: 
 
  To freely move the camera in the scene the scene window must be selected or focused.

### Camera Controls:

 - W / Up Arrow: Move Forward
 - A / Left Arrow: Move Left
 - S / Down Arrow: Move Backwards
 - D / Right Arrow: Move Right

 - Mouse Wheel: Zoom In/Out
 - Alt + Left Click: Orbit around the selected object. (If an object is not selected it will orbit around the center of the scene).
 - F: Focus the camera around the selected object.(If an object is not selected it will focus around the center of the scene).
 - R: Reset camera position and orientation. 
 - Hold Shift: Duplicate movement speed.

 If for any reason the camera got stuck or didn't show anything on screen push R to reset it. 

## Engine Functionality

 FBX models can be imported dragging and dropping them directly onto the engine. Textures can also be  imported doing 
 the same and if an object is selected it will be automatically applied to it. 
 
### Game Objects Inspector actions
 - Transform: Translate, Rotate and Scale the object. There is a scale multiplier which lest ypu scale the Object in all the axis at the same time. 
 - Mesh: Toggle the view of the vertex and face normals. 
 - Material: 
     - Toggle the checkers image. 
     - Remove the current texture. 

### Actions in tabs:
 - Windows: Enable the engine windows. 
 - Edit: 
   - Configuration: Change the engine settings and view graphs about the performance. 

 - Game Object: There are six primitives available to be created at any time. These are: Cube, Plane, Cylinder, Sphere,
   Cone and Pyramid. These are duplicated, the firsts are generated automatically and have no texture coordinates and the 
   ones marked with FBX will be loaded from FBX files and will have texture coordinates. 

 - About: Get the pages where the project is held in GitHub and get more information about the engine.