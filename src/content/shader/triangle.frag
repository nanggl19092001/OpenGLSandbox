#version 330

in vec4 vCol;
in vec2 vTexCoord;
uniform sampler2D texUni;
out vec4 colour;

void main(){
    // colour = vec4(vTexCoord.r, vTexCoord.g, 0.0, 0.0)
    colour = texture(texUni, vTexCoord);
    // colour = vCol;
}