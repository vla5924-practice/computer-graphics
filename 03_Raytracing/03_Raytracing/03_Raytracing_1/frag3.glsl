#version 430

/*************************************/
/*             Constants             */
/*************************************/

const float EPSILON = 0.001;
const float BIG = 1000000.0;


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

struct Sphere
{
	vec3  center;
	float radius;
	vec3  color;
	int   materialIdx;
};

//layout(std430, binding = 0) buffer SphereBuffer
//{
//	Sphere sphereData[];
//};

struct Material
{
	vec3 color;
	float ambient;
	float diffuse;
	float specular;
	float specularPower;
};

struct Intersection
{
	float time;
	vec3  point;
	vec3  normal;
	vec3  color;
	int   materialIdx;
};

struct Light
{
	vec3 position;
};


/*************************************/
/*          Global variables         */
/*************************************/

in  vec3 interpolatedVertex;
out vec4 fragmentColor;

uniform Camera camera;
uniform vec2   scale;

Material material = { vec3(0.8, 0, 0), 0.4, 0.9, 0.0, 512.0 };
Light light = { vec3(1, 0, -8) };
Sphere spheres[] = {
	{ vec3(1, 2, 3), 10, vec3(1, 0, 1), 0 }
};
Material materials[] = {
	{ vec3(0.8, 0, 0), 0.4, 0.9, 0.0, 512.0 }
};


/*************************************/
/*             Functions             */
/*************************************/

Ray generateRay(Camera camera)
{
	vec2 coords = interpolatedVertex.xy * normalize(scale);
	vec3 direction = camera.view + camera.side * coords.x + camera.up * coords.y;
	return Ray(camera.position, normalize(direction));
}

bool intersectSphere(Sphere sphere, Ray ray, float start, float final, out float time)
{
	ray.origin -= sphere.center;
	float A = dot(ray.direction, ray.direction);
	float B = dot(ray.direction, ray.origin);
	float C = dot(ray.origin, ray.origin) - sphere.radius * sphere.radius;
	float D = B * B - A * C;
	if (D > 0.0)
	{
		D = sqrt(D);
		float t1 = ( -B - D ) / A;
		float t2 = ( -B + D ) / A;
		if((t1 < 0) && (t2 < 0))
			return false;
		if(min(t1, t2) < 0)
		{
			time = max(t1,t2);
			return true;
		}
		time = min(t1, t2);
		return true;
	}
	return false;
}

bool intersectAll(Ray ray, float start, float final, inout Intersection is)
{
	bool result = false;
	float time = start;
	is.time = final;
	for(int i = 0; i < spheres.length(); i++)
	{
		if (intersectSphere(spheres[i], ray, start, final, time) && (time < is.time))
		{
			is.time = time;
			is.point = ray.origin + ray.direction * time;
			is.normal = normalize(is.point - spheres[i].center);
			is.color = spheres[i].color;
			is.materialIdx = spheres[i].materialIdx;
			result = true;
		}
	}
	return result;
}

float shadow(Intersection is)
{
	// Point is lighted
	float shadowing = 1.0;
	// Vector to the light source
	vec3 direction = normalize(light.position - is.point);
	// Distance to the light source
	float distanceLight = distance(light.position, is.point);
	// Generation shadow ray for this light source
	Ray shadowRay = { is.point + direction * EPSILON, direction };
	// ...test intersection this ray with each scene object
	Intersection shadowIs;
	shadowIs.time = BIG;
	// trace ray from shadow ray begining to light source position
	if(intersectAll(shadowRay, 0, distanceLight, shadowIs))
	{
		// this light source is invisible in the interûection point
		shadowing = 0.0;
	}
	return shadowing;
}


vec3 phong(Intersection is, float shadowing)
{
	vec3 light = normalize ( light.position - is.point );
	float diffuse = max(dot(light, is.normal), 0.0);
	vec3 view = normalize(camera.position - is.point);
	vec3 reflected = reflect( -view, is.normal );
	Material material = materials[is.materialIdx];
	float specular = pow(max(dot(reflected, light), 0.0), material.specularPower);
	return material.ambient * is.color + material.diffuse * diffuse * is.color * shadowing + material.specular * specular * shadowing;
}

vec4 trace(Ray primaryRay)
{
	vec4 resultColor = vec4(0, 0, 0, 0);
	Ray ray = primaryRay;
	Intersection is;
	is.time = BIG;
	float start = 0;
	float final = BIG;
	if (intersectAll(ray, start, final, is))
	{
		float shadowing = shadow(is);
		resultColor += vec4(phong(is, shadowing), 0);
	}
	return resultColor;
}


/*************************************/
/*           Main function           */
/*************************************/

void main()
{
	Ray ray = generateRay(camera);
	fragmentColor = trace(ray);
}
