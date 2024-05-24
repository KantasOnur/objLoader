#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor; // get the values from the previous stage (attrib pointer)

out vec4 vColor; // send out vColor to fragment shader, but it doenst have a value yet
uniform mat4 u_MVP;
void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0f); // for testing purposes
    vColor = aColor; // set the variable thats going to the fragment shader to the input from the attrib pointer
}
