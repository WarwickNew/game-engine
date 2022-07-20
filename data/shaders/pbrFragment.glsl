#version 330 core
out vec4 FragColor;

in vec2 ourTexCoord;
in vec3 ourNormCoord;
in vec3 WorldPos;

// TODO: make temporary hard coded world/camera pos dynamic
//uniform vec3 WorldPos ;
uniform vec3 CameraPos;
uniform int tick;
//vec3 WorldPos = vec3(0.0f, 0.0f, 0.0f);
//vec3 CameraPos = vec3(0.0f, 0.0f, -1.0f);
//TODO: make these values rely on associated textures.
vec3 albedo = vec3(0.8f, 0.8f, 0.8f);

//float metallic = sin(tick / 60 * 0.3f);
//float roughness = sin(tick / 60 * 0.3f);
//float ao = sin(tick / 60 * 0.8f);

//float metallic = 0.3f;
float roughness = 0.3f;
float ao = 0.8f;

// Handle multiple textures from the Mesh Object (Might not even be used)
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_metalness1;
uniform sampler2D texture_metalness2;

// PBR functions from learnOpenGL.com
const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main()
{
   //albedo = vec3(texture(texture_diffuse1, ourTexCoord));
   float metallic = texture(texture_metalness1, ourTexCoord).r;
   // Establish ambient lighting
   float ambientStrength = 0.1;

   // Establish a temporary hard coded light position
   vec3 lightPosition = vec3(1.0, 1.0, 1.0);
   vec3 lightColor = vec3(1.0, 0.9, 1.0);

   // Normal light maths
   vec3 N = normalize(ourNormCoord);
   vec3 V = normalize(CameraPos - WorldPos);

   vec3 Lo = vec3(0.0f);
   //TODO: Loop through the code up to ambient definition for each light
   vec3 L = normalize(lightPosition - WorldPos);
   vec3 H = normalize(V - L);
   float distance = length(lightPosition - WorldPos);
   float attenuation = 1.0 / (distance * distance);
   vec3 radiance = lightColor * attenuation;

   //Cook-Torrence BRDF
   vec3 F0 = vec3(0.04);
   F0 = mix(F0, albedo, metallic);
   vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

   float NDF = DistributionGGX(N, H, roughness);
   float G   = GeometrySmith(N, V, L, roughness);

   vec3 numerator = NDF * G * F;
   float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0)  + 0.0001;
   vec3 specular = numerator / denominator;

   //Next bit
   vec3 kS = F;
   vec3 kD = vec3(1.0) - kS;

   kD *= 1.0 - metallic;

   float NdotL = max(dot(N, L), 0.0);
   Lo += (kD * albedo / PI + specular) * radiance * NdotL;

   vec3 ambient = vec3(0.03) * albedo * ao;
   vec3 color   = ambient + Lo;

   color = color / (color + vec3(1.0));
   color = pow(color, vec3(1.0/2.2));

   //FragColor = texture(texture_diffuse1, ourTexCoord);
   FragColor = texture(texture_metalness1, ourTexCoord);
   //FragColor = texture(texture_diffuse1, ourTexCoord) * vec4(color, 0.0);
   //FragColor = vec4(CameraPos,1.0);
}
