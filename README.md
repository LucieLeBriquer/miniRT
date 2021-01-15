# My miniRT 
This 42's project is an introduction to the beautiful world of Raytracing.
## Examples

<p align="center">
  <img src="/bitmap/42.png">
</p>

Here are some lowpoly :
<p align="center">
  <img  width=49% src="/bitmap/cat.png">
  <img  width=49% src="/bitmap/fox.png">
</p>
I use <a href="https://github.com/LucieLeBriquer/convertRT">convertRT</a> to obtain .rt format from .obj objects.

## Usage
```
# Compile
make

# Execute
./miniRT scene.rt [options]

# Options
-a to deactivate antialiasing (faster execution)
--save [name] to export the rendering in bitmap format
```

## Bonus
- Filters (press `f` to change filter)
- Antialiasing
- Closed cylinders `cc`
- Cube `cb`
- Pyramid `py`
- Cone `co`
