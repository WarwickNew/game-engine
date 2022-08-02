#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP;
uniform mat4 Model;
uniform vec3 CameraPos;
uniform int tick;

out vec2 gtexCoord;
out vec3 gnormCoord;



//Pbr
out vec3 gWorldPos;

out DATA {
   vec3 normal;
   vec2 texCoord;
   mat4 camProj;
   mat4 modelProj;
   vec3 lightPos;
   vec3 camPos;
} data_out;

void main()
{
   // Saving camera projection until geometry shader.
   gl_Position = Model * vec4(aPos, 1.0);
   gnormCoord = aNormal;
   gtexCoord = aTexCoord;

   data_out.normal = aNormal;
   data_out.texCoord = aTexCoord;
   data_out.camProj = MVP;
   data_out.modelProj = Model;
   data_out.lightPos = vec3( (sin(tick / 1000.0)*2),  1 + sin(tick / 600.0)*2, 2.0);
   data_out.camPos = CameraPos;

   // Calculate position of fragment
   gWorldPos = vec3(Model * vec4(aPos, 1.0));
};
