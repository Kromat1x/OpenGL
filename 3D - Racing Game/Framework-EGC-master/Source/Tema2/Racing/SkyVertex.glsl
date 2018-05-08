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
		frag_color = vec3(0, 0.8f, 0);
	} else if (Time >= 35 && Time < 45) {
		frag_color = vec3(0, 0.75f, 0);
	} else if(Time >= 45 && Time < 55) {
		frag_color = vec3(0, 0.7f, 0);
	} else if(Time >= 55 && Time < 65) {
		frag_color = vec3(0, 0.65f, 0);
	} else if(Time >= 65 && Time < 75) {
		frag_color = vec3(0, 0.6f, 0);
	} else if(Time >= 75 && Time < 85) {
		frag_color = vec3(0, 0.55f, 0);
	} else if(Time >= 85 && Time < 95) {
		frag_color = vec3(0, 0.5f, 0);
	} else if(Time >= 95 && Time < 105) {
		frag_color = vec3(0, 0.45f, 0);
	} else if(Time >= 105 && Time < 115) {
		frag_color = vec3(0, 0.4f, 0);
	} else if(Time >= 115 && Time < 125) {
		frag_color = vec3(0, 0.45f, 0);
	} else if(Time >= 125 && Time < 135) {
		frag_color = vec3(0, 0.5f, 0);
	} else if(Time >= 135 && Time < 145) {
		frag_color = vec3(0, 0.55f, 0);
	} else if(Time >= 145 && Time < 155) {
		frag_color = vec3(0, 0.6f, 0);
	} else if(Time >= 155 && Time < 165) {
		frag_color = vec3(0, 0.65f, 0);
	} else if(Time >= 165 && Time < 175) {
		frag_color = vec3(0, 0.7f, 0);
	} else if(Time >= 175 && Time < 185) {
		frag_color = vec3(0, 0.75f, 0);
	} else if(Time >= 185 && Time < 195) {
		frag_color = vec3(0, 0.8f, 0);
	} else if(Time >= 195 && Time < 205) {
		frag_color = vec3(0, 0.85f, 0);
	} else if(Time >= 205) {
		frag_color = vec3(0, 0.9f, 0);
	}
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}