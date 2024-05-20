#version 330 core

in vec4 vColor; // get the color from vertex shader
out vec4 color; // this is the color thats going to be outputed to the screen
void main()
{
    color = vColor; // color the pixel the color recieved from the previous stage
}
