#version 330 core
out vec4 FragColor;

in vec2 ourTexCoord;
in vec3 ourNormCoord;
in vec3 FragPos;

// Handle multiple textures from the Mesh Object (Might not even be used)
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

uniform sampler2D ourTexture;

void main()
{
   // Establish ambient lighting
   float ambientStrength = 0.1;

   // Establish a temporary hard coded light position
   vec3 lightPosition = vec3(1.0, 1.0, 1.0);

   // Normal light maths
   vec3 norm = normalize(ourNormCoord);
   vec3 lightDir = normalize(lightPosition - FragPos);
   // Calculate diffuse
   float diff = max(dot(norm, lightDir), 0.0);

   FragColor = texture(texture_diffuse1, ourTexCoord) * (ambientStrength + diff);
   //FragColor = texture(ourTexture, ourTexCoord);
   //FragColor = vec4(ourTexCoord.y,ourTexCoord.x,0,0);
}
