# cub3D (macOS)

cub3D is a tiny 2.5D game engine based on raycasting algorithm.

![screenshot][1]

## Installation and launch

Just run this:
```
$ ./launcher.sh
```
## Controls
* `W A S D` to move
* `<- ->` or mouse to rotate
* `Shift` to run
* `LMB` to shoot
* `1 2` to change weapon
* `Backspace` to free mouse

## Turned-in bonuses
* Wall and object collisions
* Animated sprites
* Textured floor
* HUD
* Sounds
* Hit-scan and projectile weapons
* Items on floor
* Mouse support
## Graphics

### Library
cub3D runs using the [MiniLibX][2], a simplified version of the [Xlib][3]. You can find library Linux version [here][4].

### Render algorithm
Based on [Lode's Computer Graphics Tutorial][5] with some improvements:
* Some cycles was refactored.
* Sprites stored in sorted doubly linked list to avoid reallocations and copying.
* FPS counter was added
* Stencil buffer was added, draw order was changed accordingly.

### Draw order
With [stencil buffer][6] you can reach higher and more stable FPS. It allows you to draw in every pixel only once per frame and skip some operations. If you want to use it you need to draw frame in the following order:
1. HUD
2. Weapon
3. Sprites
4. Walls
5. Floor and ceil

[1]:https://github.com/Sidor247/cub3D/blob/main/screenshot.jpg?raw=true
[2]:https://harm-smits.github.io/42docs/libs/minilibx
[3]:https://en.wikipedia.org/wiki/Xlib
[4]:https://github.com/42Paris/minilibx-linux
[5]:https://lodev.org/cgtutor/raycasting.html
[6]:https://en.wikipedia.org/wiki/Stencil_buffer