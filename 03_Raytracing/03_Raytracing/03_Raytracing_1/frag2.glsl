#version 430

/*************************************/
/*          Data structures          */
/*************************************/

struct Camera
{
	vec3 position;
	vec3 view;
	vec3 up;
	vec3 side;
};

struct Ray
{
	vec3 origin;
	vec3 direction;
};


/*************************************/
/*          Global variables         */
/*************************************/

in vec3 interpolatedVertex;
out vec4 fragmentColor;
uniform Camera camera;
uniform vec2 scale;


/*************************************/
/*             Functions             */
/*************************************/

Ray generateRay(Camera camera)
{
	vec2 coords = interpolatedVertex.xy * normalize(scale);
	vec3 direction = camera.view + camera.side * coords.x + camera.up * coords.y;
	return Ray(camera.position, normalize(direction));
}


/*************************************/
/*           Main function           */
/*************************************/

void main()
{
	Ray ray = generateRay(camera);
	fragmentColor = vec4(abs(ray.direction.xy), 0, 1.0);
}
