#version 430 core
out vec4 FragColor;

in vec2 ourTexCoord;

uniform sampler2D ourTexture;

void main()
{
   FragColor = texture(ourTexture, ourTexCoord);
   //FragColor = vec4(ourTexCoord.y,ourTexCoord.x,0,0);
}
