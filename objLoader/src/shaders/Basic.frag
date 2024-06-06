#version 330 core

in vec4 vColor; // get the color from vertex shader
in vec3 vNormal;
in vec3 vfragPos;

out vec4 color; // this is the color thats going to be outputed to the screen

uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_EyePos;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * u_LightColor;
    
    
    vec3 normal = normalize(vNormal);
    vec3 lightDir = normalize(u_LightPos - vfragPos);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = diff * u_LightColor;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_EyePos - vfragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), 32) * u_LightColor;
    
    color = vec4((specular + ambient + diffuse), 1.0f) * vColor; // color the pixel the color recieved from the previous stage
}
