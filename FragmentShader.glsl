#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

in vec3 lightPosOut;
in vec2 TexCoords;

struct Material { 
    sampler2D diffuse;
    sampler2D specular; 
    float shininess;
};
uniform Material material;

struct Light { 
    //vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
};
uniform Light light;

uniform vec3 objectColour;


void main()
{
    //ambiewnt
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    //diffuse
    vec3 norm = normalize(Normal); 
    vec3 lightDir = normalize(-light.direction);
   
    float scaler = max( dot(norm,lightDir),0.0); // gives a ratio of how clost to perpendicular and adjusts the light based on that
    vec3 diffuse = light.diffuse * scaler * vec3(texture(material.diffuse,TexCoords));



    float spec = pow( max( dot( normalize(-FragPos), reflect(-lightDir, norm) ), 0.0), material.shininess); // pow makes it more concentrated you know maths
    vec3 specular =  spec * light.specular* vec3(texture(material.specular,TexCoords));

    FragColor = vec4((ambient + diffuse + specular), 1.0f);

}
