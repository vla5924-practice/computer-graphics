#version 430
const float EPSILON = 0.001;
const float BIG = 1000000.0;
const int DIFFUSE = 1;
const int REFLECTION = 2;
const int REFRACTION = 3;

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
	vec3 center;
	float radius;
	vec3 color;
	int materialIdx;
};

struct Triangle
{
	vec3 v1;
	vec3 v2;
	vec3 v3;
	int materialIdx;
};

struct Material
{
	float ambient;
	float diffuse;
	float specular;
	float specularPower;
};

layout(std430, binding = 0) buffer SphereBuffer
{
	Sphere sphereData[];
};

struct Intersection
{
	float time;
	vec3 point;
	vec3 normal;
	vec3 color;
	vec4 lightCoeffs;
	int materialIdx;
};

struct Light
{
	vec3 position;
};

in vec3 interpolatedVertex;
out vec4 fragmentColor;
uniform Camera camera;
uniform vec2 scale;

Material material = { 0.4, 0.9, 0.0, 512.0 };
Light light = { vec3(1, 0, -8) };

//Sphere sphere = { vec3(-1.0, -1.0, -2.0), 2, 1 };

Ray generateRay(Camera camera)
{
	vec2 coords = interpolatedVertex.xy * normalize(scale);
	vec3 direction = camera.view + camera.side * coords.x + camera.up * coords.y;
	return Ray(camera.position, normalize(direction));
}

vec3 phong(Intersection ints, Light currLight, float shadowing)
{
	vec3 light = normalize ( currLight.position - ints.point );
	float diffuse = max(dot(light, ints.normal), 0.0);
	vec3 view = normalize(camera.position - ints.point);
	vec3 reflected = reflect(-view, ints.normal );
	float specular = pow(max(dot(reflected, light), 0.0), ints.lightCoeffs.w);
	return ints.lightCoeffs.x * ints.color + ints.lightCoeffs.y * diffuse * ints.color + ints.lightCoeffs.z * specular * 1;
}

vec4 raytrace(Ray primaryRay);
float shadow(Light currLight, Intersection ints)
{
	// Point is lighted
	float shadowing = 1.0;
	// Vector to the light source
	vec3 direction = normalize(currLight.position - ints.point);
	// Distance to the light source
	float distanceLight = distance(currLight.position, ints.point);
	// Generation shadow ray for this light source
	Ray shadowRay = Ray(ints.point + direction * EPSILON, direction);
	// ...test intersection this ray with each scene object
	Intersection shadowIntersect;
	shadowIntersect.time = BIG;
	// trace ray from shadow ray begining to light source position
	if(raytrace(shadowRay))
	{
		// this light source is invisible in the intercection point
		shadowing = 0.0;
	}
	return shadowing;
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
		//time = min ( max ( 0.0, ( -B - D ) / A ), ( -B + D ) / A );
		float t1 = (-B - D) / A;
		float t2 = (-B + D) / A;
		if(t1 < 0 && t2 < 0)
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

bool intersect(Ray ray, float start, float final, inout Intersection intersect)
{
	bool result = false;
	float time = start;
	intersect.time = final;
	for(int i = 0; i < sphereData.length(); i++)
	{
		if (intersectSphere(sphereData[i], ray, start, final, time) && (time < intersect.time))
		{
			intersect.time = time;
			intersect.point = ray.origin + ray.direction * time;
			intersect.normal = normalize(intersect.point - sphereData[i].center);
			intersect.color = sphereData[i].color;
			intersect.materialIdx = sphereData[i].materialIdx;
			result = true;
		}
	}
	return result;
}

vec4 raytrace(Ray primaryRay)
{
	vec4 resultColor = vec4(0, 0, 0, 0);
	Ray ray = primaryRay;
	Intersection intersection;
	intersection.time = BIG;
	float start = 0;
	float final = BIG;
	if (intersect(ray, start, final, intersection))
	{
		float shadowing = shadow(light, intersection);
		resultColor += vec4(phong(intersection, light, shadowing), 0);
		resultColor += vec4(0.1, 0.1, 0.1, 0.1);
	}
	return resultColor;
}

void main()
{
	Ray ray = generateRay(camera);
	//fragmentColor = raytrace(ray);
	fragmentColor = vec4 (abs(ray.direction.xy), 0, 1.0);
}
