#version 330

layout(location = 0) in vec3 v_position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

out vec3 frag_color;

void main()
{
	if(Time > 0 && Time < 35){
		frag_color = vec3(0, 0.25f, 1);
	} else if (Time >= 35 && Time < 45) {
		frag_color = vec3(0, 0.22f, 0.9f);
	} else if(Time >= 45 && Time < 55) {
		frag_color = vec3(0, 0.2f, 0.8f);
	} else if(Time >= 55 && Time < 65) {
		frag_color = vec3(0, 0.19f, 0.7f);
	} else if(Time >= 65 && Time < 75) {
		frag_color = vec3(0.25f, 0.07f, 0.3f);
	} else if(Time >= 75 && Time < 85) {
		frag_color = vec3(0.20f, 0, 0.2f);
	} else if(Time >= 85 && Time < 95) {
		frag_color = vec3(0.15f, 0.02f, 0.23f);
	} else if(Time >= 95 && Time < 105) {
		frag_color = vec3(0.1f, 0.04f, 0.27f);
	} else if(Time >= 105 && Time < 115) {
		frag_color = vec3(0.05f, 0.06f, 0.29f);
	} else if(Time >= 115 && Time < 125) {
		frag_color = vec3(0.03f, 0.07f, 0.3f);
	} else if(Time >= 125 && Time < 135) {
		frag_color = vec3(0, 0.07f, 0.3f);
	} else if(Time >= 135 && Time < 145) {
		frag_color = vec3(0, 0.1f, 0.4f);
	} else if(Time >= 145 && Time < 155) {
		frag_color = vec3(0, 0.12f, 0.5f);
	} else if(Time >= 155 && Time < 165) {
		frag_color = vec3(0, 0.14f, 0.6f);
	} else if(Time >= 165 && Time < 175) {
		frag_color = vec3(0, 0.17f, 0.7f);
	} else if(Time >= 175 && Time < 185) {
		frag_color = vec3(0, 0.2f, 0.8f);
	} else if(Time >= 185 && Time < 195) {
		frag_color = vec3(0, 0.2f, 0.9);
	} else if(Time >= 195) {
		frag_color = vec3(0, 0.25f, 1);
	}
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}