#version 330 core

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D tSampler;
uniform float rotate;

void main()
{

    //mat4 RotationMatrix = mat4(
    //    cos(rotate), -sin(rotate), 0.0, 0.0,
    //    sin(rotate), cos(rotate), 0.0, 0.0,
    //    0.0, 0.0, 1.0, 0.0,
    //    0.0, 0.0, 0.0, 1.0
    //);


    //float mid = 0.25;
    //vec2 rotated = vec2(cos(rotate) * (fragmentUV.x - mid) + sin(rotate) * (fragmentUV.y - mid) + mid,
    //    cos(rotate) * (fragmentUV.y - mid) - sin(rotate) * (fragmentUV.x - mid) + mid);

    vec4 rotatedTexture = texture(tSampler, fragmentUV);
    color = rotatedTexture;
    



    //vec4 texColor = texture(tSampler, fragmentUV);
    //if (texColor.a < 0.1)
    //    discard;
    //color = texColor;
}

