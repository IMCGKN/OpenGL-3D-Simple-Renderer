#version 410 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec2 iTexCoords;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec3 iFragPos;

uniform sampler2D tex0;

uniform vec3 lightPos;
uniform vec3 viewPos;

vec3 lightColor;

void main()
{
    lightColor = vec3(1.0, 1.0, 1.0);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor * texture(tex0, iTexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(iNormal);
    vec3 lightDir = normalize(lightPos - iFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * texture(tex0, iTexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - iFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * lightColor * texture(tex0, iTexCoords).rgb;  
    
    // attenuation
    float distance    = length(lightPos - iFragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));    

    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}