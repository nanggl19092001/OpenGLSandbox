#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
out vec4 vCol;
out vec2 vTexCoord;

uniform float iMove;              
uniform mat4 modelViewMatrix;   
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(){
    gl_Position = projectionMatrix * viewMatrix * modelViewMatrix * vec4(pos, 1.0);
    vCol = vec4(clamp(pos, 0.0, 1.0), 1.0);
    vTexCoord = tex;
}