#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

// View
layout (location = 2) uniform mat4 mvp;

out vec2 ourTexCoord;

void main()
{
   gl_Position = mvp * vec4(aPos, 1.0);
   ourTexCoord = aTexCoord;
};
