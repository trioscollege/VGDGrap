#version 330 core

in vec2 fragmentUV;

out vec4 color;

uniform sampler2D tSampler;
//uniform float time;

void main()
{
    //vec4 textureColor = texture(tSampler, 1.0, 1.0);
    vec4 texColor = texture(tSampler, fragmentUV);
    color = texColor;
    //color = texColor + vec4(1.0 * (cos(time) + 1.0) * 0.5,
    //                                  1.0 * (cos(time + 2.0) + 1.0) * 0.5,
    //                                   1.0 * (cos(time + 1.0) + 1.0) * 0.5,
    //                                   1);

}