#version 420 core

const float PI = 3.1415926535897932384626433832795;

in vec4 vertexColor;
in vec3 vertexPosition;
in vec3 uv;
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 spotlightColor;
uniform vec3 lightPosition;
uniform vec3 lightDirection;

uniform float ambientStrength; //default = 0.1;
uniform float diffuseStrength; //default = 0.6;
uniform float specularStrength; //default = 0.3;

uniform float light_cutoff_outer;
uniform float light_cutoff_inner;
uniform float time;
uniform bool shouldScroll;

uniform vec3 view_position;
uniform sampler2D shadow_map;
uniform sampler2D actualTexture;

uniform bool shouldRenderShadows;
uniform bool shouldRenderColors;
uniform bool shouldSpotlightChange;

in vec3 fragmentPosition;
in vec4 fragmentPositionLightSpace;
in vec3 fragmentNormal;

in vec4 gl_FragCoord;

vec3 ambient_color(vec3 light_color_arg) {
    return ambientStrength * light_color_arg;
}

vec3 diffuse_color(vec3 light_color_arg, vec3 light_position_arg) {
    vec3 light_direction = normalize(light_position_arg - fragmentPosition);
    return diffuseStrength * light_color_arg * max(dot(normalize(fragmentNormal), light_direction), 0.0f);
}

vec3 specular_color(vec3 light_color_arg, vec3 light_position_arg) {
    vec3 light_direction = normalize(light_position_arg - fragmentPosition);
    vec3 view_direction = normalize(view_position - fragmentPosition);
    vec3 reflect_light_direction = reflect(-light_direction, normalize(fragmentNormal));
    return specularStrength * light_color_arg * pow(max(dot(reflect_light_direction, view_direction), 0.0f),64);
}

float shadow_scalar() {
    // this function returns 1.0 when the surface receives light, and 0.0 when it is in a shadow
    // perform perspective divide
    vec3 normalized_device_coordinates = fragmentPositionLightSpace.xyz / fragmentPositionLightSpace.w;
    // transform to [0,1] range
    normalized_device_coordinates = normalized_device_coordinates * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragment_position_light_space as coords)
    float closest_depth = texture(shadow_map, normalized_device_coordinates.xy).r;
    // get depth of current fragment from light's perspective
    float current_depth = normalized_device_coordinates.z;
    // check whether current frag pos is in shadow
    float bias = 0.0005;
    return ((current_depth - bias) < closest_depth) ? 1.0 : 0.0;
}

float spotlight_scalar() {
	float maximumAngle = light_cutoff_outer;
	float lightToFrag = length(fragmentPosition - lightPosition);
	float lightPoint = length(lightDirection);
	
	float angle = acos(dot(fragmentPosition - lightPosition, lightDirection)/(lightToFrag * lightPoint));
	
	if(abs(angle) < maximumAngle )
		return (maximumAngle  - abs(angle))/maximumAngle ;
	else return 0.0f;
}

void main()
{

		vec3 ambient = vec3(0.0f);
		vec3 diffuse = vec3(0.0f);
		vec3 specular = vec3(0.0f);
	
		float scalar = spotlight_scalar() * shadow_scalar();
		
		ambient = ambient_color(lightColor);
		diffuse = scalar * diffuse_color(lightColor, lightPosition);
		specular = scalar * specular_color(lightColor, lightPosition);
		
		vec3 color, chosenColor;
		vec2 actualUV;
	
		if(shouldScroll)
			actualUV = vec2(uv.x + time*0.1, uv.y);
		else
			actualUV = vec2(uv.x, uv.y);
			
		vec4 textureColor = texture(actualTexture, actualUV);

		chosenColor = vec3(textureColor.x, textureColor.y, textureColor.z);

		
		color = chosenColor; //(specular + diffuse + ambient) * chosenColor;

		FragColor = vec4(color, uv.z);
}
	