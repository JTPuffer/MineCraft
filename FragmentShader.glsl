#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

in vec3 lightPosOut;

uniform vec3 objectColour;
uniform vec3 lightColour;


void main()
{
    //ambiewnt
    float ambient = 0.1;


    //diffuse
    vec3 norm = normalize(Normal); 
    vec3 lightDir = normalize(lightPosOut - FragPos);
   
    float scaler = max( dot(norm,lightDir),0.0); // gives a ratio of how clost to perpendicular and adjusts the light based on that
    vec3 diffuse = scaler * lightColour;



    float specularStrength =0.5;

    float spec = pow( max( dot( normalize(-FragPos), reflect(-lightDir, norm) ), 0.0), 256); // pow makes it more concentrated you know maths
    vec3 specular = specularStrength * spec * lightColour;

    FragColor = vec4((ambient + diffuse + specular) * objectColour, 1.0f);

}
