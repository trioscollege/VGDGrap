#version 330 core

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D tSampler;

void main()
{

    vec4 texColor = texture(tSampler, fragmentUV);
    //if (texColor.a < 0.1)
    //    discard;
    color = texColor;

    //color = vec4(1,0,0,0);
}

