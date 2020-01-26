#version 330 core

in vec2 vertexPosition;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec2 fragmentUV;

uniform mat4 proj;

void main()
{
    gl_Position.xy = (proj * vec4(vertexPosition, 0.0, 1.0)).xy;

    gl_Position.z = 0.0;

    gl_Position.w = 1.0;

    fragmentPosition = vertexPosition;
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}