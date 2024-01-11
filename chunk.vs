#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location =2) in vec3 aNormal;

layout (location = 3) in vec4 aOffset;

out vec2 BasicTexCoords;
out vec3 Normal;
out vec3 FragPos;

flat out int MaterialIndex;
uniform mat4 model; 
uniform mat4 view;
uniform mat4 projection;


void main() {

    vec3 position = vec3( aPos.x +aOffset.x, aPos.y +aOffset.y, aPos.z +aOffset.z) ;
    vec4 worldPos = vec4(position, 1.0);
    MaterialIndex=int(aOffset.w);
    FragPos = vec3(worldPos);
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    BasicTexCoords = aTexCoords;
    gl_Position = projection * view * worldPos;

}