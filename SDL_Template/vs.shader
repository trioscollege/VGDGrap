#version 330 core

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 proj;
//uniform float flip;
uniform mat4 trans;
void main()
{
    gl_Position = proj * vec4(vertexPosition,0,1);

    gl_Position.z = 0.0;

    gl_Position.w = 1.0;

    fragmentPosition = gl_Position.xy;

    fragmentColor = vertexColor;

    fragmentUV = vertexUV;
    //if (flip == 1)
        //fragmentUV = vec2(vertexUV.x, flip - vertexUV.y);
}