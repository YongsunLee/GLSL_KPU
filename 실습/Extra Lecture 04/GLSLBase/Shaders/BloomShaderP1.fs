#version 330

in vec4 vColor;

layout(location=0) out vec4 FragColor;
layout(location=1) out vec4 BloomColor;

in vec3 v_FragPos;
in vec3 v_Normal;
in vec4 v_Color;

const float c_Ambient = 0.1;
const float c_Diffuse = 0.7;
const float c_Specular = 0.8;
const vec3 c_LightPos = vec3(0, 0.5, 2);

uniform vec3 u_CameraPos;
uniform vec3 u_Emissive;

void main()
{
    vec3 lightDir = normalize(c_LightPos - v_FragPos);
    vec3 viewDir = normalize(u_CameraPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, v_Normal); 

    float diffuse = max(0, dot(lightDir, v_Normal));
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), 128);

	FragColor.rgb = (c_Ambient + c_Diffuse*diffuse + specular*c_Specular)*v_Color.rgb + u_Emissive;
    FragColor.a = v_Color.a;

	BloomColor = max(vec4(0, 0, 0, 0), FragColor - vec4(1, 1, 1, 0));
}
