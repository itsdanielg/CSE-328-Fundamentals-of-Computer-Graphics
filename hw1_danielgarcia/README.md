HOW TO USE THIS PROGRAM:

This program uses a 2D Coordinate System consisting of 4 quadrants where the origin (0,0) is at the center of the window with a window width of 1600 and a window height of 900.

Inputs:
Plotting Mode:
	Left Click -> Place Vertex
	Right Click -> Complete Polygon
Transformation Mode:
	Left Click -> Select Vertex (Also highlights it yellow)
	Right Click -> Move Selected Vertex

Keyboard Inputs:
'd' -> Delete all non-simple polygons
'p' -> Change to Plotting mode
't' -> Change to Transformation mode
'Enter' -> Open command-line to enter transformation input
(Can only be accessed when in transformation mode and there is a selected vertex to select polygon)
	COMMANDS:
	't' = Translation
	's' = Scale
	'r' = Rotate
	'h' = Shear
	'm' = Mirror
	FORMAT: 
	|COMMAND|
	|X FACTOR| |Y FACTOR| OR |ANGLE|

Notes:
-> Red lines indicate non-simple polygons due to intersecting line segments
-> Scaling is respective to the origin (0,0)
-> Rotation is respective to the origin (0,0)

WHAT DO THE FILES DO?
main.c -> The main openGL program. Initializes the window, inputs, and drawings
struct.h -> Contains the main structures used throughout the program (Points, lines, and polygons)
midpoint.c -> Contains the midpoint algorithm function
scan.c -> Contains functions that check for line segment intersections and scan conversion for polygon filling
transformation.c = Contains transformation functions