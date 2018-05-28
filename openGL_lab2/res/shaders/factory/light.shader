#vertex
#version 330 core

uniform mat4 camera;
uniform mat4 myTransformation;

in vec3 position;
in vec2 textureCoords;
in vec3 normal;
in vec4 color;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec4 fragColor;

void main() {
    // Pass some variables to the fragment shader
    fragTexCoord = textureCoords;
    fragNormal = normal;
    fragVert = position;
	fragColor = color;
    
    // Apply all matrix transformations to vert
    gl_Position = camera * transpose(myTransformation) * vec4(position, 1);
}

#fragment
#version 330 core

uniform mat4 myTransformation;
uniform vec4 myColor;
uniform sampler2D tex;

uniform struct Light {
   vec3 position;
   vec3 intensities; //a.k.a the color of the light
} myLightStruct;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;
in vec4 fragColor;

out vec4 finalColor;

void main() {
    //calculate normal in world coordinates
    mat3 normalMatrix = transpose(inverse(mat3(myTransformation)));
    vec3 normal = normalize(normalMatrix * fragNormal);
    
    //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = vec3(myTransformation * vec4(fragVert, 1));
    
    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = myLightStruct.position - fragPosition;

    //calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
	vec4 surfaceColor = texture(tex, fragTexCoord);
	//vec4 surfaceColor = fragColor;
    
	finalColor = vec4(brightness * myLightStruct.intensities * surfaceColor.rgb, surfaceColor.a);
}