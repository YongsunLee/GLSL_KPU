#version 330

in vec3 a_Position;

uniform float u_Time;
uniform vec2 u_startPoint;
uniform vec2 u_endPoint;

void main()
{
	float pi = 3.141592;
	vec2 newPos = vec2(-10, -10);

	vec2 k = u_endPoint - u_startPoint;

	mat2 rot = mat2(cos(pi/2), sin(pi/2), -sin(pi/2), cos(pi/2));

	vec2 rotVec = normalize(rot*k);
	
	if (u_Time > a_Position.x)
	{
		float newTime = u_Time - a_Position.x; 
		newTime = fract(newTime/2);				
		
		float temp = (sin(newTime * pi * a_Position.y) * a_Position.z * 0.3f);

		newPos = u_startPoint + k * newTime;
		newPos += rotVec * temp;
	}

	gl_Position = vec4(
		newPos.x,
		newPos.y,
		0.f,
		1.0f
	);

	//gl_PointSize = abs(sin(u_Time));	// point의 크기가 u_Time의 값을 따라 변경 sin을 통해서 작아젔다 커졌다 할 수 있다.
	gl_PointSize = u_Time * 5;	// point의 크기가 u_Time의 값을 따라 변경 sin을 통해서 작아젔다 커졌다 할 수 있다.

	//gl_PointSize = 10.f;
}