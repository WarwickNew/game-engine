#version 330 core
out vec4 FragColor;

in vec2 ourTexCoord;

// Handle multiple textures from the Mesh Object (Might not even be used)
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

uniform sampler2D ourTexture;

void main()
{
   FragColor = texture(texture_diffuse1, ourTexCoord);
   //FragColor = texture(ourTexture, ourTexCoord);
   //FragColor = vec4(ourTexCoord.y,ourTexCoord.x,0,0);
}
