#version 330

uniform sampler2D diffuseMap; //Zmienna reprezentujaca jednostke teksturujaca
uniform float wallT;
out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 i_l; //wektor do swiatla(przestrzen oka)
in vec4 i_v; //wektor do obserwatora(przestrzen oka)
in vec4 i_n; //wektor normalny (przestrzen oka)

in vec4 i_l2; //wektor do swiatla(przestrzen oka)


in vec2 iTexCoord0; //wspolrzedne teksturowania


void main(void) {
	vec4 v=normalize(i_v);
    vec4 n=normalize(i_n);
    vec4 l=normalize(i_l);
    vec4 l2=normalize(i_l2);

    vec4 r=reflect(-l,n);
    vec4 r2=reflect(-l2,n);

    vec4 ka=vec4(vec3(texture(diffuseMap,iTexCoord0)),wallT); //Kolor obiektu w swietle otoczenia
    vec4 kd=vec4(vec3(texture(diffuseMap,iTexCoord0)),wallT); //Kolor obiektu w swietle rozproszonym

    vec4 ks=vec4(vec3(texture(diffuseMap,iTexCoord0)),wallT); //Kolor obiektu w swietle odbitym

    vec4 la=vec4(0.2,0.2,0.2,1); //Kolor swiatla otoczenia
    vec4 ld=vec4(0.7,0.7,0.7,1); //Kolor swiatla rozpraszanego
    vec4 ls=vec4(0.1,0.1,0.1,1); //Kolor swiatla odbijanego

    float nl=max(dot(n,l),0); //Kosinus kata pomiedzy wektorami do swiatla i normalnym
    float nl2=max(dot(n,l2),0); //Kosinus kata pomiedzy wektorami do swiatla i normalnym
    float rv=pow(max(dot(r,v),0),3); //Kosinus kata pomiedzy wektorami do obserwatora i odbitym, podniesiony do wykladnika Phonga
    float rv2=pow(max(dot(r2,v),0),3); //Kosinus kata pomiedzy wektorami do obserwatora i odbitym, podniesiony do wykladnika Phonga
	pixelColor=ka*la+kd*ld*vec4(nl,nl,nl,1)+ks*ls*vec4(rv,rv,rv,0)+(ka*la+kd*ld*vec4(nl2,nl2,nl2,1)+ks*ls*vec4(rv2,rv2,rv2,0));
}
