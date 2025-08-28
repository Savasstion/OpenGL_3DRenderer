# Overview
This is a renderer built on OpenGL to render a 3D robot model for my Graphics Programming course assignment. It uses the FBX SDK to import fbx file formats into the scene and uses linear interpolation to animate the robot using keyframes.

<img width="585" height="588" alt="cgDemo" src="https://github.com/user-attachments/assets/ff0bb66b-0cf7-4397-8107-9db31e32229f" />

(Image of a robot being rendered using OpenGL with diffuse lighting)

# Requirements
- FBX SDK
- OpenGL

# Manual
 ## Reset Robot
 Enter key : Reset robot transforms
 
 ## Update States (To reuse same keys, you must switch between states)
 Z : Camera Mode (to use arrow keys for camera movement, + and- for zooming in and out)
 
 X : Light Mode (to use arrow keys for light position change, + and- for changing depth position)
 
 C : Head Transform Mode (To update the transform of the head)
 
 V : Torso Transform Mode
 
 B : Upper Left Arm Transform Mode
 
 N : Lower Left Arm Transform Mode
 
 M : Upper Right Arm Transform Mode
 
 J : Lower Right Arm Transform Mode
 
 H : Upper Left Leg Transform Mode
 
 G : Lower Left Leg Transform Mode
 
 F : Upper Right Leg Transform Mode
 
 R : Lower Right Leg Transform Mode
 
 ## Camera
 A/D : Orbit around robot
 
 ## Camera Movement (make sure in Camera Mode)
 Up : Move Camera Up
 
 Down : Move Camera Down
 
 Left : Move Camera Left
 
 Right : Move Camera Right
 
 ## Light Source Movement (make sure in Light Mode)
 Up : Move Light Up
 
 Down : Move Light Down
 
 Left : Move Light Left
 
 Right : Move Light Right
 
## Robot Part Transform Update (make sure in a Transform Mode)
 Left : Rotate anti-clockwise in all axis
 
 Right : Rotate clockwise in all axis
 
 Up : Scale up in all axis
 
 Down : Scale down in all axis
 
 (+) : Decrease depth position
 
 (-) : Increase depth position
 
 ## Zoom (Make sure in correct state)
 (+) : Zoom in (Camera / Lighting)
 
 (-) : Zoom out (Camera / Lighting)
 
 ## Textures
 1-7 : switch between 7 robot textures
 
 ## Animation
 Space : Pause Animation
 
 8 : Awake Animation
 
 9 : Walking Animation
 
 0 : Shooting Animation
 
 ## Projection
 O : Orthographic
 
 P : Perspective
 
 ## Lighting
 L : Toggle Lighting
 
 K : Toggle Ambient or Diffuse
 


