#version 130

in vec3 Position;
uniform mat4 projection, view, model;
uniform float time;
out vec4 Color;

void main()
{
    vec3 adjustedPosition = Position;
    adjustedPosition.y += sin(time) * 5.0;
    gl_Position = projection * view * model * vec4(adjustedPosition, 1);
    Color = vec4(clamp(Position, 0.0, 1.0), 1);
}
