#version 330

in vec2 v_TexPos;

uniform sampler2D u_TextureOriginal;
uniform sampler2D u_TextureBlur;

layout(location=0) out vec4 FragColor;

void main()
{
    FragColor = texture(u_TextureBlur, v_TexPos) + texture(u_TextureOriginal, v_TexPos);
}
