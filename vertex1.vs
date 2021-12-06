#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec4 coloring;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(){
gl_Position = projection * view * model * vec4(position, 1.0f);
coloring = vec4(color, 1.f);
}
