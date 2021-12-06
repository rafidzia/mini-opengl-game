#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec4 coloring;
void main(){
gl_Position = vec4(position, 1.0f);
coloring = vec4(color, 1.f);
}
