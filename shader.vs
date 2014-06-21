#version 130

in vec3 Position;
uniform mat4 projection, view, model;
out vec4 Color;

void main()
{
    gl_Position = projection * view * model * vec4(Position, 1);
    Color = vec4(clamp(Position, 0.0, 1.0), 1);
}
