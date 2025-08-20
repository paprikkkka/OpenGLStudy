#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform float time;

out vec3 color;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    //float offset = 0.3 * sin(time);
    //float scale = 1 / time;
    //vec3 sPos = aPos * scale;
    vec4 position = vec4(aPos, 1.0);
    position =projectionMatrix * viewMatrix * transform * position;

    gl_Position = position;
    color = aColor;
    texCoord = vec2(aTexCoord.x,aTexCoord.y);
    //color = aColor;
}