#version 410

in vec4 vCol;

out vec4 colour;

void main(){
    colour = vec4(vCol);
}