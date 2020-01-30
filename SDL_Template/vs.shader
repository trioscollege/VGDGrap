#version 330 core

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 proj;

void main()
{
    //gl_Position.xy = vertexPosition

    //gl_Position.z = 0.0;

    //gl_Position.w = 1.0;

    //fragmentPosition = vertexPosition;

    //fragmentColor = vertexColor;
    //fragmentUV = vertexUV;
}