//Generated with Symbolize (c) 2019 Alexander Kraus <nr4@z10.info>.
#ifndef SYMBOLIZE_H
#define SYMBOLIZE_H

int rand_handle, lfnoise_handle, mfnoise_handle, dbox_handle, dbox3_handle, dvoronoi_handle, normal_handle, stroke_handle, add_handle, smoothmin_handle, zextrude_handle, line_handle;
const int nsymbols = 12;
const char *rand_source = "#version 130\nvoid rand(in vec2 x,out float n){x+=400.;n=fract(sin(dot(sign(x)*abs(x),vec2 (12.9898,78.233)))*43758.5453);}\0";
const char *lfnoise_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rand(in vec2 x,out float d);void lfnoise(in vec2 t,out float n){vec2 i=floor(t);t=fract(t);t=smoothstep(c.yy,c.xx,t);vec2 v1,v2;rand(i,v1.x);rand(i+c.xy,v1.y);rand(i+c.yx,v2.x);rand(i+c.xx,v2.y);v1=c.zz+2.*mix(v1,v2,t.y);n=mix(v1.x,v1.y,t.x);}\0";
const char *mfnoise_source = "#version 130\nvoid lfnoise(in vec2 x,out float d);void mfnoise(in vec2 x,in float d,in float b,in float e,out float n){n=0.;float a=1.,nf=0.,buf;for(float f=d;f<b;f*=2.){lfnoise(f*x,buf);n+=a*buf;a*=e;nf+=1.;}n*=(1.-e)/(1.-pow(e,nf));}\0";
const char *dbox_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dbox(in vec2 x,in vec2 b,out float d){vec2 da=abs(x)-b;d=length(max(da,c.yy))+min(max(da.x,da.y),0.0);}\0";
const char *dbox3_source = "#version 130\nvoid dbox3(in vec3 x,in vec3 b,out float d){vec3 da=abs(x)-b;d=length(max(da,0.0))+min(max(da.x,max(da.y,da.z)),0.0);}\0";
const char *dvoronoi_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rand(in vec2 x,out float d);void dvoronoi(in vec2 x,out float d,out vec2 z){vec2 y=floor(x);float ret=1.;vec2 pf=c.yy,p;float df=10.;for(int i=-1;i<=1;i+=1)for(int j=-1;j<=1;j+=1){p=y+vec2 (float (i),float (j));float pa;rand(p,pa);p+=pa;d=length(x-p);if(d<df){df=d;pf=p;}}for(int i=-1;i<=1;i+=1)for(int j=-1;j<=1;j+=1){p=y+vec2 (float (i),float (j));float pa;rand(p,pa);p+=pa;vec2 o=p-pf;d=length(.5*o-dot(x-pf,o)/dot(o,o)*o);ret=min(ret,d);}d=ret;z=pf;}\0";
const char *normal_source = "const vec3 c=vec3 (1.0,0.0,-1.0);void scene(in vec3 x,out vec2 s);void normal(in vec3 x,out vec3 n){const float dx=5.e-4;vec2 s,na;scene(x,s);scene(x+dx*c.xyy,na);n.x=na.x;scene(x+dx*c.yxy,na);n.y=na.x;scene(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}\0";
const char *stroke_source = "void stroke(in float d0,in float s,out float d){d=abs(d0)-s;}\0";
const char *add_source = "void add(in vec2 sda,in vec2 sdb,out vec2 sdf){sdf=mix(sda,sdb,step(sdb.x,sda.x));}\0";
const char *smoothmin_source = "void smoothmin(in float a,in float b,in float k,out float dst){float h=max(k-abs(a-b),0.0)/k;dst=min(a,b)-h*h*h*k*(1.0/6.0);}\0";
const char *zextrude_source = "void zextrude(in float z,in float d2d,in float h,out float d){vec2 w=vec2 (-d2d,abs(z)-0.5*h);d=length(max(w,0.0));}\0";
const char *line_source = "void line(in vec3 x,in vec3 p1,in vec3 p2,out float dst){vec3 d=p2-p1;dst=length(x-mix(p1,p2,clamp(dot(x-p1,d)/dot(d,d),0.,1.)));}\0";
const char *decayingfactory_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;const float pi=acos(-1.);const vec3 c=vec3 (1.0,0.0,-1.0);float a=1.0;void rand(in vec2 x,out float num);void lfnoise(in vec2 t,out float num);void mfnoise(in vec2 x,in float fmin,in float fmax,in float alpha,out float num);void dbox(in vec2 x,in vec2 b,out float d);void dbox3(in vec3 x,in vec3 b,out float d);void dvoronoi(in vec2 x,out float d,out vec2 ind);void normal(in vec3 x,out vec3 n);void stroke(in float d0,in float s,out float d);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void colorize_wall_concrete(in vec2 x,out vec3 col){float w=.4,d;float n,n2,n3,n4;mfnoise(x,8.,8.e2,.68,n);lfnoise(2.*x,n2);col=mix(vec3 (0.85,0.84,0.82),vec3 (0.07,0.05,0.04),.5+.5*n);col=mix(col,mix(vec3 (0.85,0.84,0.82),vec3 (0.86,0.83,0.79),.8+.2*n),smoothstep(.0,.3,n*n2));mfnoise(x,.4,2.e2,.48,n3);col=mix(col,c.yyy,smoothstep(-.2,.4,.3+n3-n));float na;lfnoise(iTime*c.xx,na);col=mix(col,c.yyy,(.5+.5*na)*smoothstep(.1,-.1,abs(.3+n3-n)-.1));col=mix(col,mix(vec3 (0.45,0.06,0.01),vec3 (0.69,0.14,0.04),(.1+.9*n)*smoothstep(-.1,.4,.3+1.4*n3+.7*n)),smoothstep(.3,.7,.3+1.4*n3-.5*n));}void colorize_tiles(in vec2 x,out vec3 col){float w=.4,d;vec2 y=mod(x,w)-.5*w;float n;mfnoise(x,4.,4.e2,.48,n);dbox(y,.47*w*c.xx,d);d+=.005*n;col=mix(vec3 (0.90,0.84,0.80),1.2*vec3 (1.00,0.95,0.86),.5+.5*n);float nr;mfnoise(x*vec2 (12.,1.),1.,1.e1,.85,nr);col=mix(col,1.4*vec3 (0.80,0.58,0.22),clamp(.1+.9*nr,0.,1.));float v;vec2 vi;dvoronoi((x.xy-.1*n)/w,v,vi);col=mix(col,vec3 (0.54,0.48,0.45),smoothstep(1.5/iResolution.y,-1.5/iResolution.y,abs(v)-.01));col=mix(vec3 (0.22,0.22,0.22),col,smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d));float na;mfnoise(x,4.,4.e2,.98,na);col=mix(col,mix(vec3 (0.54,0.48,0.45),.0*c.xxx,.5+.5*na),smoothstep(1.5/iResolution.y,-1.5/iResolution.y,.3+n));}void colorize_wall(in vec2 x,out vec3 col){if(x.y>0.)colorize_wall_concrete(x,col);else colorize_tiles(x,col);}void colorize_pipes(in vec2 x,out vec3 col){float n,nlo;mfnoise(x,4.8e1,4.8e3,.65,n);lfnoise(6.*x,nlo);col=mix(vec3 (0.37,0.07,0.00),vec3 (0.62,0.63,0.66),.5+.5*n);vec3 c1=mix(vec3 (1.00,0.84,0.70),vec3 (0.37,0.07,0.00),.5+.5*n);col=mix(col,c1,smoothstep(n-.1,n+.1,nlo));col=mix(col,vec3 (0.64,0.39,0.32),(.5+.5*n)*smoothstep(n-.1,n+.1,nlo));float nb;stroke(n,.1,nb);col=mix(col,vec3 (0.58,0.33,0.26),smoothstep(1.5/iResolution.y,-1.5/iResolution.y,nb));}void wall_tiles(in vec3 x,out float d){float n;mfnoise(x.xy,4.,4.e2,.45,n);float w=.4;vec2 y=mod(x.xy,w)-.5*w;dbox(y,.47*w*c.xx,d);float v;vec2 vi;dvoronoi((x.xy-.1*n)/w,v,vi);v=mix(v,1.,smoothstep(1.5/iResolution.y,-1.5/iResolution.y,.3+n));d=x.z+.008*n+.2*smoothstep(1.5/iResolution.y,-1.5/iResolution.y,abs(v)-.01)+.3*smoothstep(2.5/iResolution.y,-2.5/iResolution.y,d+.005*n)*smoothstep(-1.5/iResolution.y,1.5/iResolution.y,.3+n)-.2*(.5*n+.5)*smoothstep(1.5/iResolution.y,-1.5/iResolution.y,.3+n);}void wall_concrete(in vec3 x,out float d){float n;mfnoise(x.xy,8.,8.e2,.68,n);d=x.z+.015*(.5+.5*n);}void pipes(in vec3 x,out float d){float n,nlo,na;mfnoise(x.xy,4.8e1,4.8e3,.65,na);mfnoise(x.xy,1.8e1,4.8e3,.55,n);lfnoise(6.*x.xy,nlo);d=x.z+.015*n-.015*smoothstep(na-.1,na+.1,nlo);}void pipes_normal(in vec3 x,out vec3 n){const float dx=5.e-4;float s;pipes(x,s);pipes(x+dx*c.xyy,n.x);pipes(x+dx*c.yxy,n.y);pipes(x+dx*c.yyx,n.z);n=normalize(n-s);}void wall_tiles_normal(in vec3 x,out vec3 n){const float dx=5.e-4;float s;wall_tiles(x,s);wall_tiles(x+dx*c.xyy,n.x);wall_tiles(x+dx*c.yxy,n.y);wall_tiles(x+dx*c.yyx,n.z);n=normalize(n-s);}void wall_concrete_normal(in vec3 x,out vec3 n){const float dx=5.e-4;float s;wall_concrete(x,s);wall_concrete(x+dx*c.xyy,n.x);wall_concrete(x+dx*c.yxy,n.y);wall_concrete(x+dx*c.yyx,n.z);n=normalize(n-s);}void scene(in vec3 x,out vec2 sdf){float d;dbox3(x,112.*c.xxx,sdf.x);float w=mix(.4,.38,smoothstep(1.5/iResolution.y,-1.5/iResolution.y,x.y));dbox3(x,vec3 (w,1.2*w,56.),d);sdf.x=max(sdf.x,-d);dbox3(vec3 (x.xy,abs(mod(x.z,2.)))-.8*c.yyx,vec3 (2.,1.2*w,w),d);sdf.x=max(sdf.x,-d);sdf.y=1.;if(abs(x.x)<.4){float wa=.1;vec2 sda=vec2 (length(vec2 (mod(x.x,wa)-.5*wa,x.y-1.2*w))-.4*wa,2.);add(sdf,sda,sdf);}float n,n2;lfnoise(12.*x.xz-iTime*c.yx+.1*iTime*c.xy,n);lfnoise(34.5*x.xz-3.141*iTime*c.yx-.1*iTime*c.xy,n2);vec2 sdb=vec2 (x.y+.38-.002*(.7*n+.3*n2),3.);add(sdf,sdb,sdf);}void colorize(in vec3 x,in vec2 s,inout vec3 n,out vec3 col){if(s.y==1.){if(abs(dot(n,c.xyy))+abs(dot(n,c.yxy))<1.e-4){colorize_wall(6.*x.xy,col);if(x.y<0.)wall_tiles_normal(6.*x*c.xxy,n);else wall_concrete_normal(6.*x*c.xxy,n);}else if(abs(dot(n,c.yxy))+abs(dot(n,c.yyx))<1.e-4){colorize_wall(6.*x.zy,col);if(x.y<0.)wall_tiles_normal(6.*x.zyx,n);else wall_concrete_normal(6.*x.zyx,n);}else {if(x.y<0.){colorize_wall(6.*x.zx-23.,col);wall_tiles_normal(6.*x.zxy-23.*c.xxy,n);}else {colorize_wall(6.*x.zx+23.,col);wall_concrete_normal(6.*x.zxy+23.*c.xxy,n);}}}else if(s.y==2.){colorize_pipes(6.*x.zx-23.,col);pipes_normal(6.*x.zxy-23.*c.xxy,n);}}void mainImage(out vec4 fragColor,in vec2 fragCoord){a=iResolution.x/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);vec3 col=c.yyy;vec3 t=vec3 (uv,0.)-mix(.3,.7,0.*smoothstep(0.,1.,sin(pi*iTime)))*iTime*c.yyx+.01*abs(cos(2.*pi*iTime))*c.yxy+.005*sin(2.*pi*iTime)*c.xyy,o=c.yyx-.3*iTime*c.yyx+.01*abs(sin(2.*pi*iTime))*c.yxy+.005*sin(2.*pi*iTime)*c.xyy,dir=normalize(t-o),x,n;float d=0.;vec2 s;int N=300,i;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=s.x;}{normal(x,n);float d0=d;if(s.y==3.){o=x;d=.002;dir=reflect(dir,n);for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=s.x;}normal(x,n);d=abs(d)+abs(d0);}colorize(x,s,n,col);vec3 l=-abs(normalize(o)/max(d*d,1.));col=.1*col/min(d,4.)+.6*col*abs(dot(l,n))+.3*col*abs(pow(dot(reflect(-l,n),dir),4.));}col=clamp(col,0.,1.);float na;lfnoise(iTime*c.xx,na);vec3 gs=length(col)*c.xxx;col=mix(col,gs,.5+.5*na);fragColor=vec4 (col,1.0);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
const char *fogforest_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;const float pi=acos(-1.);const vec3 c=vec3 (1.0,0.0,-1.0);float a=1.0;void rand(in vec2 x,out float num);void lfnoise(in vec2 t,out float n);void mfnoise(in vec2 x,in float d,in float b,in float e,out float n);void dvoronoi(in vec2 x,out float d,out vec2 z);void smoothmin(in float a,in float b,in float k,out float dst);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void zextrude(in float z,in float d2d,in float h,out float d);void dbox(in vec2 p,in vec2 b,out float dst);void line(in vec3 x,in vec3 p1,in vec3 p2,out float dst);void stroke(in float d,in float s,out float dst);void rand3(in vec3 x,out float num){num=fract(sin(dot(sign(x)*abs(x),vec3 (12.9898,78.233,45.1232)))*43758.5453);}void lfnoise3(in vec3 t,out float num){vec3 i=floor(t);t=fract(t);t=smoothstep(c.yyy,c.xxx,t);vec2 v1,v2,v3,v4;rand3(i,v1.x);rand3(i+c.xyy,v1.y);rand3(i+c.yxy,v2.x);rand3(i+c.xxy,v2.y);rand3(i+c.yyx,v3.x);rand3(i+c.xyx,v3.y);rand3(i+c.yxx,v4.x);rand3(i+c.xxx,v4.y);v1=c.zz+2.*mix(v1,v2,t.y);v3=c.zz+2.*mix(v3,v4,t.y);v2.x=-1.+2.*mix(v1.x,v1.y,t.x);v2.y=-1.+2.*mix(v3.x,v3.y,t.x);num=mix(v2.x,v2.y,t.z);}void mfnoise3(in vec3 x,in float fmin,in float fmax,in float alpha,out float dst){dst=0.;float a=1.,nf=0.;for(float f=fmin;f<fmax;f=f*2.){float buf;lfnoise3(f*x,buf);dst+=a*buf;a*=alpha;nf+=1.;}dst*=(1.-alpha)/(1.-pow(alpha,nf));}void scene(in vec3 x,out vec2 d){x.y+=.1*iTime;float n;mfnoise(x.xy,4.,4.e2,.35,n);d=vec2 (x.z-.05*n,1.);float v,da;vec2 vi;dvoronoi(x.xy,v,vi);vec2 r;rand(vi,r.x);rand(vi+1301.,r.y);vec2 y=x.xy-vi,n2;lfnoise(3.*x.z*c.xx-r,n2.x);lfnoise(4.*x.z*c.xx+33.1*r,n2.y);da=length(y-.01*n2)-.07*mix(1.,.7,smoothstep(0.,1.,clamp(x.z*3.,0.,1.)));smoothmin(d.x,da,.2,d.x);d.y=mix(1.,2.,step(.1*n,x.z));float z=mod(x.z,.05)-.025,zi=(x.z-z)/.05;vec2 rp;rand(zi*c.xx+r,rp.x);rand(zi*c.xx+r+1332.,rp.y);rp*=vec2 (1.,2.*pi);float nz;lfnoise(5.*length(y-.01*n2)*c.xx-33.*zi,nz);line(vec3 (y-.01*n2,z+.01*nz),c.yyy,vec3 (rp.x*vec2 (cos(rp.y),sin(rp.y)),.05*rp.x),da);stroke(da,mix(1.,.1,smoothstep(0.,1.,clamp(length(vec3 (y-.01*n2,z))/.7,0.,1.)))*.01*(.3+rp.x+n2.x),da);smoothmin(d.x,da,.05,d.x);}const float dx=5.e-4;void normal(in vec3 x,out vec3 n);void colorize(in vec2 x,out vec3 col){x.y+=.1*iTime;float n;mfnoise(x.xy,4.e0,4.e2,.65,n);col=mix(vec3 (0.55,0.69,0.37),vec3 (0.00,0.02,0.04),.9+.1*n);}void mainImage(out vec4 fragColor,in vec2 fragCoord){a=iResolution.x/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);vec3 col=c.yyy;float pp=.3*iTime;vec3 o=c.yzy+.2*c.yyx,t=c.yyy+.3*c.yyx,dir=normalize(t-o),r=normalize(c.xyy),u=normalize(cross(r,dir)),n,x;t+=uv.x*r+uv.y*u;dir=normalize(t-o);vec2 s;float d=0.;int N=350,i;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4*max(d*d,1.))break;if(d>10.)break;d+=min(.01*max(d,1.),s.x);}vec3 l=normalize(x+c.yxx);if(i<N){normal(x,n);}if(s.y==2.){col=.2*vec3 (0.05,0.12,0.12)+.2*vec3 (0.05,0.12,0.12)*abs(dot(l,n))+.6*vec3 (0.04,0.13,0.12)*abs(pow(dot(reflect(-l,n),dir),3.));}if(s.y==1.){colorize(x.xy,col);.5*col+.2*col*abs(dot(l,n))+.6*col*abs(pow(dot(reflect(-l,n),dir),3.));}vec3 c1=mix(vec3 (0.91,0.87,0.68),vec3 (0.07,0.21,0.21),clamp(length(uv),0.,1.));float noiz;mfnoise3(x,1.,100.,.65,noiz);noiz=.5+.5*noiz;c1=mix(c1,vec3 (0.29,0.60,0.47),noiz);col=mix(col,c1,clamp(d/10.,0.,1.));fragColor=clamp(vec4 (col,1.0),0.,1.);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
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
void Loaddbox3()
{
    int dbox3_size = strlen(dbox3_source);
    dbox3_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dbox3_handle, 1, (GLchar **)&dbox3_source, &dbox3_size);
    glCompileShader(dbox3_handle);
#ifdef DEBUG
    printf("---> dbox3 Shader:\n");
    debug(dbox3_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddvoronoi()
{
    int dvoronoi_size = strlen(dvoronoi_source);
    dvoronoi_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dvoronoi_handle, 1, (GLchar **)&dvoronoi_source, &dvoronoi_size);
    glCompileShader(dvoronoi_handle);
#ifdef DEBUG
    printf("---> dvoronoi Shader:\n");
    debug(dvoronoi_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadnormal()
{
    int normal_size = strlen(normal_source);
    normal_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(normal_handle, 1, (GLchar **)&normal_source, &normal_size);
    glCompileShader(normal_handle);
#ifdef DEBUG
    printf("---> normal Shader:\n");
    debug(normal_handle);
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
void Loadadd()
{
    int add_size = strlen(add_source);
    add_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(add_handle, 1, (GLchar **)&add_source, &add_size);
    glCompileShader(add_handle);
#ifdef DEBUG
    printf("---> add Shader:\n");
    debug(add_handle);
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
void Loadzextrude()
{
    int zextrude_size = strlen(zextrude_source);
    zextrude_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(zextrude_handle, 1, (GLchar **)&zextrude_source, &zextrude_size);
    glCompileShader(zextrude_handle);
#ifdef DEBUG
    printf("---> zextrude Shader:\n");
    debug(zextrude_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadline()
{
    int line_size = strlen(line_source);
    line_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(line_handle, 1, (GLchar **)&line_source, &line_size);
    glCompileShader(line_handle);
#ifdef DEBUG
    printf("---> line Shader:\n");
    debug(line_handle);
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
    Loaddbox3();
    updateBar();
    Loaddvoronoi();
    updateBar();
    Loadnormal();
    updateBar();
    Loadstroke();
    updateBar();
    Loadadd();
    updateBar();
    Loadsmoothmin();
    updateBar();
    Loadzextrude();
    updateBar();
    Loadline();
    updateBar();
}
int decayingfactory_program, decayingfactory_handle, fogforest_program, fogforest_handle;
int decayingfactory_iTime_location;
decayingfactory_iResolution_location;
int fogforest_iTime_location;
fogforest_iResolution_location;
const int nprograms = 2;

void Loaddecayingfactory()
{
    int decayingfactory_size = strlen(decayingfactory_source);
    decayingfactory_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(decayingfactory_handle, 1, (GLchar **)&decayingfactory_source, &decayingfactory_size);
    glCompileShader(decayingfactory_handle);
#ifdef DEBUG
    printf("---> decayingfactory Shader:\n");
    debug(decayingfactory_handle);
    printf(">>>>\n");
#endif
    decayingfactory_program = glCreateProgram();
    glAttachShader(decayingfactory_program,decayingfactory_handle);
    glAttachShader(decayingfactory_program,rand_handle);
    glAttachShader(decayingfactory_program,lfnoise_handle);
    glAttachShader(decayingfactory_program,mfnoise_handle);
    glAttachShader(decayingfactory_program,dbox_handle);
    glAttachShader(decayingfactory_program,dbox3_handle);
    glAttachShader(decayingfactory_program,dvoronoi_handle);
    glAttachShader(decayingfactory_program,normal_handle);
    glAttachShader(decayingfactory_program,stroke_handle);
    glAttachShader(decayingfactory_program,add_handle);
    glLinkProgram(decayingfactory_program);
#ifdef DEBUG
    printf("---> decayingfactory Program:\n");
    debugp(decayingfactory_program);
    printf(">>>>\n");
#endif
    glUseProgram(decayingfactory_program);
    decayingfactory_iTime_location = glGetUniformLocation(decayingfactory_program, "iTime");
    decayingfactory_iResolution_location = glGetUniformLocation(decayingfactory_program, "iResolution");
    progress += .2/(float)nprograms;
}

void Loadfogforest()
{
    int fogforest_size = strlen(fogforest_source);
    fogforest_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fogforest_handle, 1, (GLchar **)&fogforest_source, &fogforest_size);
    glCompileShader(fogforest_handle);
#ifdef DEBUG
    printf("---> fogforest Shader:\n");
    debug(fogforest_handle);
    printf(">>>>\n");
#endif
    fogforest_program = glCreateProgram();
    glAttachShader(fogforest_program,fogforest_handle);
    glAttachShader(fogforest_program,rand_handle);
    glAttachShader(fogforest_program,lfnoise_handle);
    glAttachShader(fogforest_program,mfnoise_handle);
    glAttachShader(fogforest_program,dvoronoi_handle);
    glAttachShader(fogforest_program,smoothmin_handle);
    glAttachShader(fogforest_program,add_handle);
    glAttachShader(fogforest_program,zextrude_handle);
    glAttachShader(fogforest_program,dbox_handle);
    glAttachShader(fogforest_program,line_handle);
    glAttachShader(fogforest_program,stroke_handle);
    glAttachShader(fogforest_program,normal_handle);
    glLinkProgram(fogforest_program);
#ifdef DEBUG
    printf("---> fogforest Program:\n");
    debugp(fogforest_program);
    printf(">>>>\n");
#endif
    glUseProgram(fogforest_program);
    fogforest_iTime_location = glGetUniformLocation(fogforest_program, "iTime");
    fogforest_iResolution_location = glGetUniformLocation(fogforest_program, "iResolution");
    progress += .2/(float)nprograms;
}

void LoadPrograms()
{
    Loaddecayingfactory();
    updateBar();
    Loadfogforest();
    updateBar();
}
#endif
