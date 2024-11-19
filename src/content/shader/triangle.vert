#version 410

layout (location = 0) in vec3 pos;

out vec4 vCol;

uniform float iMove;              
uniform mat4 modelViewMatrix;   
uniform mat4 projectionMatrix;

void main(){
    gl_Position = projectionMatrix * modelViewMatrix * vec4(pos, 1.0);
    vCol = vec4(clamp(pos, 0.0, 1.0), 1.0);
}