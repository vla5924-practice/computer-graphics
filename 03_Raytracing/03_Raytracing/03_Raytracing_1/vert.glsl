#version 430

in vec3 vertex;
out vec3 interpolatedVertex;

void main()
{
    gl_Position = vec4(vertex, 1.0);
    interpolatedVertex = vertex;
}
