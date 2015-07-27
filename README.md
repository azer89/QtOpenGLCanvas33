A custom Qt canvas with OpenGL 3.3. This program does not use glBegin() and gelEnd(), instead, it uses VertexBufferObjects and VertexArrayObjects to perform rendering. 

The main purpose of this project is to create a 2D rendering canvas which uses modern OpenGL. The canvas is a combination of a derived QAbstractScrollArea class and a derived QGLWidget class so it has scrollbars and can be zoomed in/out. 

![alt tag](https://raw.githubusercontent.com/azer89/QtOpenGLCanvas33/master/screenshot.png)

The program is really simple since it only draws an n-gon. Press right button to add the number of the sides, and press left to do the opposite.
