#version 330 core
uniform mat4 MVP;
out vec4 FragColor;

in vec2 texCoord;

in GS_OUT {
   vec3 tangentLightPos;
   vec3 tangentViewPos;
   vec3 tangentFragPos;
} from_gs;


// TODO: make temporary hard coded world/camera pos dynamic
uniform vec3 CameraPos;

// Handle multiple textures from the Mesh Object (Might not even be used)
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_rma1;
uniform sampler2D texture_normal1;

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

vec3 PBR(vec3 albedo, float roughness, float metallic, float ao)
{
   vec3 lightPosition = from_gs.tangentLightPos;
   vec3 lightColor  = vec3(13.47, 11.31, 10.79);

   vec3 camPos = from_gs.tangentViewPos;
   vec3 fragPos = from_gs.tangentFragPos;

   // Thanks to us calculating the tangent space to the triangle and using
   // these values instead of normal space we can just use the plain corrected
   // UV values here.
   vec3 N = normalize((texture(texture_normal1, texCoord).xyz * 2.0 - 1.0)/2);
   vec3 V = normalize(camPos - fragPos);

   vec3 F0 = vec3(0.04);
   F0 = mix(F0, albedo, metallic);

   // reflectance equation
   vec3 Lo = vec3(0.0);
   // calculate per-light radiance
   vec3 L = normalize(lightPosition - fragPos);
   vec3 H = normalize(V + L);
   float distance    = length(lightPosition - fragPos);
   float attenuation = 1.0 / (distance * distance);
   vec3 radiance     = lightColor * attenuation;

   // cook-torrance brdf
   float NDF = DistributionGGX(N, H, roughness);
   float G   = GeometrySmith(N, V, L, roughness);
   vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);

   vec3 kS = F;
   vec3 kD = vec3(1.0) - kS;
   kD *= 1.0 - metallic;

   vec3 numerator    = NDF * G * F;
   float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
   vec3 specular     = numerator / denominator;

   // add to outgoing radiance Lo
   float NdotL = max(dot(N, L), 0.0);
   Lo += (kD * albedo / PI + specular) * radiance * NdotL;

   vec3 ambient = vec3(0.03) * albedo * ao;
   vec3 color = ambient + Lo;

   color = color / (color + vec3(1.0));
   return pow(color, vec3(1.0/2.2));
}

void main()
{
   vec3 albedo;
   albedo.r = pow(texture(texture_diffuse1, texCoord).r, 2.2);
   albedo.g = pow(texture(texture_diffuse1, texCoord).g, 2.2);
   albedo.b = pow(texture(texture_diffuse1, texCoord).b, 2.2);
   float roughness = texture(texture_rma1, texCoord).r;
   float metallic = texture(texture_rma1, texCoord).g;
   float ao = texture(texture_rma1, texCoord).b;

   FragColor = vec4(PBR(albedo, roughness, metallic, ao), 1.0);
}
