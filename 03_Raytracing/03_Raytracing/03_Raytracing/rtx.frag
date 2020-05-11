#version 430

in vec3 interpolatedVertex;
out vec4 fragmentColor;

void main()
{
    fragmentColor = vec4(abs(interpolatedVertex.xy), 0, 1.0);
}