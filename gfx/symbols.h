//Generated with Symbolize (c) 2019 Alexander Kraus <nr4@z10.info>.
#ifndef SYMBOLIZE_H
#define SYMBOLIZE_H

int rand_handle, lfnoise_handle, mfnoise_handle, dbox_handle, dcirclesegment_handle, dcircle_handle, dlinesegment_handle, dlogo210_handle, dspline2_handle, stroke_handle, mirror_handle, smoothmin_handle;
const int nsymbols = 12;
const char *rand_source = "#version 130\nvoid rand(in vec2 x,out float n){x+=400.;n=fract(sin(dot(sign(x)*abs(x),vec2 (12.9898,78.233)))*43758.5453);}\0";
const char *lfnoise_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rand(in vec2 x,out float d);void lfnoise(in vec2 t,out float n){vec2 i=floor(t);t=fract(t);t=smoothstep(c.yy,c.xx,t);vec2 v1,v2;rand(i,v1.x);rand(i+c.xy,v1.y);rand(i+c.yx,v2.x);rand(i+c.xx,v2.y);v1=c.zz+2.*mix(v1,v2,t.y);n=mix(v1.x,v1.y,t.x);}\0";
const char *mfnoise_source = "#version 130\nvoid lfnoise(in vec2 x,out float d);void mfnoise(in vec2 x,in float d,in float b,in float e,out float n){n=0.;float a=1.,nf=0.,buf;for(float f=d;f<b;f*=2.){lfnoise(f*x,buf);n+=a*buf;a*=e;nf+=1.;}n*=(1.-e)/(1.-pow(e,nf));}\0";
const char *dbox_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dbox(in vec2 x,in vec2 b,out float d){vec2 da=abs(x)-b;d=length(max(da,c.yy))+min(max(da.x,da.y),0.0);}\0";
const char *dcirclesegment_source = "#version 130\nconst float pi=acos(-1.);void dcirclesegment(in vec2 x,in float R,in float p0,in float p1,out float d){float p=atan(x.y,x.x);vec2 philo=vec2 (max(p0,p1),min(p0,p1));if((p<philo.x&&p>philo.y)||(p+2.0*pi<philo.x&&p+2.0*pi>philo.y)||(p-2.0*pi<philo.x&&p-2.0*pi>philo.y))d=abs(length(x)-R);else d=min(length(x-vec2 (cos(p0),sin(p0))),length(x-vec2 (cos(p1),sin(p1))));}\0";
const char *dcircle_source = "#version 130\nvoid dcircle(in vec2 x,in float R,out float d){d=abs(length(x)-R);}\0";
const char *dlinesegment_source = "#version 130\nvoid dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d){vec2 da=p2-p1;d=length(x-mix(p1,p2,clamp(dot(x-p1,da)/dot(da,da),0.,1.)));}\0";
const char *dlogo210_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);const float pi=acos(-1.);void dcirclesegment(in vec2 x,in float R,in float p0,in float p1,out float d);void dcircle(in vec2 x,in float R,out float d);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void dlogo210(in vec2 x,in float R,out float d){float d2;dcircle(x+R*c.zy,R,d);dlinesegment(x,R*c.yz,R*c.yx,d2);d=min(d,d2);dcirclesegment(x+R*c.xy,R,-.5*pi,.5*pi,d2);d=min(d,d2);}\0";
const char *dspline2_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);const float pi=acos(-1.);float dist2(vec2 p0,vec2 p1,vec2 p2,vec2 x,float t){t=clamp(t,0.,1.);return length(x-pow(1.-t,2.)*p0-2.*(1.-t)*t*p1-t*t*p2);}void dspline2(in vec2 x,in vec2 p0,in vec2 p1,in vec2 p2,out float ds){vec2 E=x-p0,F=p2-2.*p1+p0,G=p1-p0;vec3 ai=vec3 (3.*dot(G,F),2.*dot(G,G)-dot(E,F),-dot(E,G))/dot(F,F);float tau=ai.x/3.,p=ai.y-tau*ai.x,q=-tau*(tau*tau+p)+ai.z,dis=q*q/4.+p*p*p/27.;if(dis>0.){vec2 ki=-.5*q*c.xx+sqrt(dis)*c.xz,ui=sign(ki)*pow(abs(ki),c.xx/3.);ds=dist2(p0,p1,p2,x,ui.x+ui.y-tau);return ;}float fac=sqrt(-4./3.*p),arg=acos(-.5*q*sqrt(-27./p/p/p))/3.;vec3 t=c.zxz*fac*cos(arg*c.xxx+c*pi/3.)-tau;ds=min(dist2(p0,p1,p2,x,t.x),min(dist2(p0,p1,p2,x,t.y),dist2(p0,p1,p2,x,t.z)));}\0";
const char *stroke_source = "void stroke(in float d0,in float s,out float d){d=abs(d0)-s;}\0";
const char *mirror_source = "void mirror(in vec2 x,in vec2 w,out vec2 y){y=abs(x)-w;}\0";
const char *smoothmin_source = "void smoothmin(in float a,in float b,in float k,out float dst){float h=max(k-abs(a-b),0.0)/k;dst=min(a,b)-h*h*h*k*(1.0/6.0);}\0";
const char *z10out_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;const float pi=acos(-1.);const vec3 c=vec3 (1.0,0.0,-1.0);float a=1.0,ry=1.0;void rand(in vec2 x,out float n);void lfnoise(in vec2 t,out float n);void mfnoise(in vec2 x,in float d,in float b,in float e,out float n);void dbox(in vec2 x,in vec2 b,out float d);void dcirclesegment(in vec2 x,in float R,in float p0,in float p1,out float d);void dcircle(in vec2 x,in float R,out float d);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void dlogo210(in vec2 x,in float R,out float d);float dist2(vec2 p0,vec2 p1,vec2 p2,vec2 x,float t);void dspline2(in vec2 x,in vec2 p0,in vec2 p1,in vec2 p2,out float ds);void stroke(in float d0,in float s,out float d);void mirror(in vec2 x,in vec2 w,out vec2 y);void smoothmin(in float a,in float b,in float k,out float dst);float sm(in float d){return smoothstep(ry,-ry,d);}void colorize(in vec2 x,out vec3 col){col=vec3 (0.12,0.13,0.16);float d;dbox(x-.1*c.yx,vec2 (.5*a,.3),d);col=mix(col,vec3 (0.48,0.37,0.33),sm(d));dbox(x+.25*c.yx,vec2 (.5*a,.075),d);col=mix(col,vec3 (0.62,0.62,0.63),sm(d));dbox(x+.33*c.yx,vec2 (.5*a,.01),d);col=mix(col,c.xxx,sm(d));dbox(x+.36*c.yx,vec2 (.5*a,.02),d);col=mix(col,vec3 (0.55,0.52,0.48),sm(d));if(abs(x.x+.3)>.4){vec2 a=vec2 (mod(x.x-.1,.4)-.2,x.y);dbox(a+.29*c.yx,vec2 (.1,.03),d);col=mix(col,mix(vec3 (0.29,0.26,0.25),vec3 (0.49,0.46,0.43),step(fract(35.*(x.x-.4/35.))-.2,0.)),sm(d));dbox(a-.1*c.yx,vec2 (.12,.15),d);col=mix(col,vec3 (0.65,0.65,0.66),sm(d));stroke(d+.001,.001,d);col=mix(col,c.yyy,sm(d));vec2 b=a;mirror(a-.1*c.yx,vec2 (.04,.04),b);stroke(b.y,.04,b.y);dbox(b,vec2 (.038),d);vec3 n;lfnoise(12.*x-floor(iTime),n.x);lfnoise(12.*x-floor(iTime)+1337.,n.y);lfnoise(12.*x-floor(iTime)+2337.,n.z);n=clamp((1.3+.2*sin(2.*pi*iTime))*(.5+.5*n),0.,1.);col=mix(col,n,sm(d));b=a;stroke(a.x,.12,b.x);dbox(b-.1*c.yx,vec2 (.05,.12),d);col=mix(col,mix(vec3 (0.65,0.68,0.75),vec3 (0.30,0.27,0.24),step(d+.02,0.)*step((fract(80.*x.y)-.5)/80.,0.)),sm(d));stroke(d+.001,.001,d);col=mix(col,c.yyy,sm(d));}vec2 y=x-vec2 (-.2,-.15);stroke(y.x,.101,y.x);dbox(y,vec2 (.1,.2),d);col=mix(col,vec3 (0.09,0.20,0.18),sm(d));vec2 z;mirror(y,vec2 (.045,.08),z);dbox(z,vec2 (.035,.06),d);col=mix(col,vec3 (0.07,0.11,0.12),sm(d));stroke(d,.003,d);col=mix(col,c.yyy,sm(d));float da=length((x-vec2 (-.2,.15))*vec2 (1.,3.))-.2;dbox(x-vec2 (-.2,.1),vec2 (.2,.05),d);d=min(d,da);col=mix(col,vec3 (0.20,0.32,0.26)*step(fract(35.*(x.x-.5/35.))-.8,0.),sm(d));da=length((x-vec2 (-.2,.125))*vec2 (1.,2.))-.14;col=mix(col,vec3 (0.14,0.12,0.13),sm(da));stroke(da+.005,.002,da);col=mix(col,c.yyy,sm(da));dlogo210(x-vec2 (-.2,.125),.04,da);stroke(da,.0125,da);col=mix(col,mix(c.xyy,c.xxy,clamp((x.y)/.3,0.,1.)),sm(da));stroke(da-.005,.002,da);col=mix(col,c.yyy,sm(da));vec2 w=x+.2*c.xy;stroke(w.x,.23,w.x);dlinesegment(w,-.33*c.yx,.18*c.yx,da);float db;dspline2(x,vec2 (-.44,.18),vec2 (-.24,.3),vec2 (.04,.18),db);da=min(da,db);stroke(da,.01,db);stroke(da,.03,da);col=mix(col,vec3 (0.48,0.52,0.59),sm(da));col=mix(col,.8*vec3 (0.48,0.52,0.59),sm(db));float dsmoke;vec3 cs=col;dlinesegment(vec2 (.125,1.)*x,.35*c.yx,.35*c.yx,dsmoke);dlinesegment(x,vec2 (.2,.3),vec2 (-.2,-.2),da);stroke(da,.01,da);stroke(dsmoke,.095,dsmoke);smoothmin(dsmoke,da,.5,dsmoke);float n;mfnoise(x-.1*iTime,8.,800.,.35,n);dsmoke+=.03*mix(-1.,1.,n);cs=mix(cs,.1*c.xxx,sm(dsmoke));dsmoke+=.01*x.y;cs=mix(cs,.2*c.xxx,sm(dsmoke));dsmoke+=.05*x.y;cs=mix(cs,.3*c.xxx,sm(dsmoke));dsmoke+=.1*x.y;cs=mix(cs,.4*c.xxx,sm(dsmoke));col=mix(col,cs,smoothstep(5.,6.,iTime));}void mainImage(out vec4 fragColor,in vec2 fragCoord){a=iResolution.x/iResolution.y;ry=1.5/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);vec3 col=c.yyy;colorize(uv,col);fragColor=vec4 (col,1.);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
void Loadrand()
{
    int rand_size = strlen(rand_source);
    rand_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rand_handle, 1, (GLchar **)&rand_source, &rand_size);
    glCompileShader(rand_handle);
#ifdef DEBUG
    printf("---> rand Shader:\n");
    debug(rand_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadlfnoise()
{
    int lfnoise_size = strlen(lfnoise_source);
    lfnoise_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(lfnoise_handle, 1, (GLchar **)&lfnoise_source, &lfnoise_size);
    glCompileShader(lfnoise_handle);
#ifdef DEBUG
    printf("---> lfnoise Shader:\n");
    debug(lfnoise_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadmfnoise()
{
    int mfnoise_size = strlen(mfnoise_source);
    mfnoise_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mfnoise_handle, 1, (GLchar **)&mfnoise_source, &mfnoise_size);
    glCompileShader(mfnoise_handle);
#ifdef DEBUG
    printf("---> mfnoise Shader:\n");
    debug(mfnoise_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddbox()
{
    int dbox_size = strlen(dbox_source);
    dbox_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dbox_handle, 1, (GLchar **)&dbox_source, &dbox_size);
    glCompileShader(dbox_handle);
#ifdef DEBUG
    printf("---> dbox Shader:\n");
    debug(dbox_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddcirclesegment()
{
    int dcirclesegment_size = strlen(dcirclesegment_source);
    dcirclesegment_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dcirclesegment_handle, 1, (GLchar **)&dcirclesegment_source, &dcirclesegment_size);
    glCompileShader(dcirclesegment_handle);
#ifdef DEBUG
    printf("---> dcirclesegment Shader:\n");
    debug(dcirclesegment_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddcircle()
{
    int dcircle_size = strlen(dcircle_source);
    dcircle_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dcircle_handle, 1, (GLchar **)&dcircle_source, &dcircle_size);
    glCompileShader(dcircle_handle);
#ifdef DEBUG
    printf("---> dcircle Shader:\n");
    debug(dcircle_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddlinesegment()
{
    int dlinesegment_size = strlen(dlinesegment_source);
    dlinesegment_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dlinesegment_handle, 1, (GLchar **)&dlinesegment_source, &dlinesegment_size);
    glCompileShader(dlinesegment_handle);
#ifdef DEBUG
    printf("---> dlinesegment Shader:\n");
    debug(dlinesegment_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddlogo210()
{
    int dlogo210_size = strlen(dlogo210_source);
    dlogo210_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dlogo210_handle, 1, (GLchar **)&dlogo210_source, &dlogo210_size);
    glCompileShader(dlogo210_handle);
#ifdef DEBUG
    printf("---> dlogo210 Shader:\n");
    debug(dlogo210_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddspline2()
{
    int dspline2_size = strlen(dspline2_source);
    dspline2_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dspline2_handle, 1, (GLchar **)&dspline2_source, &dspline2_size);
    glCompileShader(dspline2_handle);
#ifdef DEBUG
    printf("---> dspline2 Shader:\n");
    debug(dspline2_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadstroke()
{
    int stroke_size = strlen(stroke_source);
    stroke_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(stroke_handle, 1, (GLchar **)&stroke_source, &stroke_size);
    glCompileShader(stroke_handle);
#ifdef DEBUG
    printf("---> stroke Shader:\n");
    debug(stroke_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadmirror()
{
    int mirror_size = strlen(mirror_source);
    mirror_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mirror_handle, 1, (GLchar **)&mirror_source, &mirror_size);
    glCompileShader(mirror_handle);
#ifdef DEBUG
    printf("---> mirror Shader:\n");
    debug(mirror_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadsmoothmin()
{
    int smoothmin_size = strlen(smoothmin_source);
    smoothmin_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(smoothmin_handle, 1, (GLchar **)&smoothmin_source, &smoothmin_size);
    glCompileShader(smoothmin_handle);
#ifdef DEBUG
    printf("---> smoothmin Shader:\n");
    debug(smoothmin_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}

void LoadSymbols()
{
    Loadrand();
    updateBar();
    Loadlfnoise();
    updateBar();
    Loadmfnoise();
    updateBar();
    Loaddbox();
    updateBar();
    Loaddcirclesegment();
    updateBar();
    Loaddcircle();
    updateBar();
    Loaddlinesegment();
    updateBar();
    Loaddlogo210();
    updateBar();
    Loaddspline2();
    updateBar();
    Loadstroke();
    updateBar();
    Loadmirror();
    updateBar();
    Loadsmoothmin();
    updateBar();
}
int z10out_program, z10out_handle;
int z10out_iTime_location;
z10out_iResolution_location;
const int nprograms = 1;

void Loadz10out()
{
    int z10out_size = strlen(z10out_source);
    z10out_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(z10out_handle, 1, (GLchar **)&z10out_source, &z10out_size);
    glCompileShader(z10out_handle);
#ifdef DEBUG
    printf("---> z10out Shader:\n");
    debug(z10out_handle);
    printf(">>>>\n");
#endif
    z10out_program = glCreateProgram();
    glAttachShader(z10out_program,z10out_handle);
    glAttachShader(z10out_program,rand_handle);
    glAttachShader(z10out_program,lfnoise_handle);
    glAttachShader(z10out_program,mfnoise_handle);
    glAttachShader(z10out_program,dbox_handle);
    glAttachShader(z10out_program,dcirclesegment_handle);
    glAttachShader(z10out_program,dcircle_handle);
    glAttachShader(z10out_program,dlinesegment_handle);
    glAttachShader(z10out_program,dlogo210_handle);
    glAttachShader(z10out_program,dspline2_handle);
    glAttachShader(z10out_program,stroke_handle);
    glAttachShader(z10out_program,mirror_handle);
    glAttachShader(z10out_program,smoothmin_handle);
    glLinkProgram(z10out_program);
#ifdef DEBUG
    printf("---> z10out Program:\n");
    debugp(z10out_program);
    printf(">>>>\n");
#endif
    glUseProgram(z10out_program);
    z10out_iTime_location = glGetUniformLocation(z10out_program, "iTime");
    z10out_iResolution_location = glGetUniformLocation(z10out_program, "iResolution");
    progress += .2/(float)nprograms;
}

void LoadPrograms()
{
    Loadz10out();
    updateBar();
}
#endif
