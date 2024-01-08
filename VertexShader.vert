#version 330 core
layout (location = 0) in vec3 aPos;
layout (location =1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model; 
uniform mat4 view;
uniform mat4 projection;


void main() {

	vec4 FragPos_T = model * vec4(aPos, 1.0);

	FragPos = vec3(view * FragPos_T);

	gl_Position = projection * view *FragPos_T ;


	Normal = mat3(transpose(inverse(model* view))) * aNormal;
	TexCoords = aTexCoords;

}