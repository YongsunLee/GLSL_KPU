#version 330

in vec2 v_TexPos;

Layout(location=0) out vec4 FragColor;

uniform Sampler2D u_Textrue

void main()
{
     FragColor = texture(u_Textrue, v_TexPos);
}
