#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor; // get the values from the previous stage (attrib pointer)
layout(location = 2) in vec3 aNormal;

out vec4 vColor; // send out vColor to fragment shader, but it doenst have a value yet
out vec3 vNormal;
out vec3 vfragPos;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(aPos, 1.0f); // for testing purposes
    vColor = aColor; // set the variable thats going to the fragment shader to the input from the attrib pointer
    vNormal = mat3(transpose(inverse(u_ModelMatrix))) * aNormal;
    vfragPos = vec3(u_ModelMatrix * vec4(aPos, 1.0f));
}
