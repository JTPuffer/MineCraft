#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

in vec3 lightPosOut;

struct Material { 
    vec3 ambient;
    vec3 diffuse; 
    vec3 specular; 
    float shininess;
};
uniform Material material;

struct Light { 
    vec3 position;
    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
};
uniform Light light;

uniform vec3 objectColour;


void main()
{
    //ambiewnt
    vec3 ambient = material.ambient * light.ambient;


    //diffuse
    vec3 norm = normalize(Normal); 
    vec3 lightDir = normalize(lightPosOut - FragPos);
   
    float scaler = max( dot(norm,lightDir),0.0); // gives a ratio of how clost to perpendicular and adjusts the light based on that
    vec3 diffuse = (scaler * material.diffuse) *light.diffuse ;



    float spec = pow( max( dot( normalize(-FragPos), reflect(-lightDir, norm) ), 0.0), material.shininess); // pow makes it more concentrated you know maths
    vec3 specular = material.specular * spec * light.specular;

    FragColor = vec4((ambient + diffuse + specular) * objectColour, 1.0f);

}
