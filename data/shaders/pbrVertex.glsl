#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP;
uniform mat4 Model;

out vec2 ourTexCoord;
out vec3 ourNormCoord;
out vec3 FragPos;

void main()
{
   gl_Position = MVP * Model * vec4(aPos, 1.0);
   ourNormCoord = aNormal;
   ourTexCoord = aTexCoord;

   // Calculate position of fragment
   FragPos = vec3(Model * vec4(aPos, 1.0));
};