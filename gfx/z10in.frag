/* Fuer Elite by Team210 - 64k intro by Team210 at Underground Conference 2k19
* Copyright (C) 2019  Alexander Kraus <nr4@z10.info>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#version 130

uniform float iTime;
uniform vec2 iResolution;

// Global constants
const float pi = acos(-1.);
const vec3 c = vec3(1.0, 0.0, -1.0);
float a = 1.0, ry = 1.0;

void rand(in vec2 x, out float n);
void lfnoise(in vec2 t, out float n);
void mfnoise(in vec2 x, in float d, in float b, in float e, out float n);
void dbox(in vec2 x, in vec2 b, out float d);
void dcirclesegment(in vec2 x, in float R, in float p0, in float p1, out float d);
void dcircle(in vec2 x, in float R, out float d);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void dlogo210(in vec2 x, in float R, out float d);
float dist2(vec2 p0,vec2 p1,vec2 p2,vec2 x,float t);
void dspline2(in vec2 x, in vec2 p0, in vec2 p1, in vec2 p2, out float ds);
void stroke(in float d0, in float s, out float d);
void mirror(in vec2 x, in vec2 w, out vec2 y);
void smoothmin(in float a, in float b, in float k, out float dst);
float sm(in float d)
{
    return smoothstep(ry,-ry,d);
}

void colorize(in vec2 x, out vec3 col)
{
    col = mix(vec3(0.30,0.14,0.47),vec3(0.02,0.03,0.16),.5-.5*x.y);
    
    float d, ind;
    vec2 y;
    vec3 n;
    
    // People partying in background
    for(float i=8.; i>=0.; i-=1.)
    {
        float da;
        y = vec2(mod(x.x-.1*i, .4)-.2, x.y)-.01*i*c.yx;
        ind = x.x-y.x;
        lfnoise(ind*c.xx-iTime+i, n.x);
        lfnoise(ind*c.xx+1337.-iTime+i, n.y);
        lfnoise(ind*c.xx+2338.-iTime+i, n.z);
        float ra, db;
        rand(ind*c.xx+i, ra);
        db = length(y-.1*n.y*c.yx-.2*c.yx)-.05;
        dlinesegment(y-.1*n.y*c.yx-.2*c.yx, vec2(.08,-.05), vec2(.1+.05*n.x,.05), d);
        dlinesegment(y-.1*n.y*c.yx-.2*c.yx, vec2(-.08,-.05), vec2(-.1+.05*n.z,.05), da);
        d = min(d, da);
        stroke(d, .025, d);    
        smoothmin(d, db, .01, d);
        dlinesegment(y-.1*n.y*c.yx-.2*c.yx, -.1*c.yx, -(.14+.04*ra)*c.yx, da);
        stroke(da, .07-.02*ra, da);
        smoothmin(d, da, .1, d);
        vec2 aa = y;
        stroke(aa.x, -.01, aa.x);
        dlinesegment(aa-.1*n.y*c.yx-.2*c.yx, vec2(.04,-.2),vec2(.05,-.4), da);
        stroke(da, .03, da);
        smoothmin(d, da, .1, d);
        col = mix(col, vec3(0.18,0.08,0.30), sm(d));
        stroke(d, .001, d);
        col = mix(col, mix(vec3(0.36,0.18,0.49),vec3(0.94,0.49,0.60), i/5.), sm(d));
        
        // Party lights
        dlinesegment(x, vec2(a*n.x,1.), vec2(a*n.z,-1.), d);
        stroke(d, -.1*(x.y-1.), d);
        n = .5+.5+n;
        col = mix(col, mix(col, n, .5), sm(d));
    }
    
    // Bar
    dbox(x+.3*c.yx, vec2(.5*a, .1), d);
    col = mix(col, vec3(0.10,0.07,0.32), sm(d));
    dbox(x+.5*c.yx, vec2(.5*a, .15), d);
    col = mix(col, vec3(0.02,0.01,0.17), sm(d));
    
    // Alcohol
    y = vec2(mod(x.x-5.e-4*floor(iTime), .1)-.05, x.y);
    ind = x.x-y.x;
    rand(ind*c.xx, n.x);
    rand(ind*c.xx+1337., n.y);
    rand(ind*c.xx+2338., n.z);
    n = mix(n, .5+.5*n, n);
    n = clamp(n, 0.,1.);
    float r = .03, h=.06;
    dbox(y+.2*c.yx+.1*n.y*c.yx, vec2(r,.5*h), d);
    d = min(d, length(y+.2*c.yx+.1*n.y*c.yx+.5*h*c.yx)-r);
    col = mix(col, n, sm(d));
    d = length(y+.2*c.yx+.1*n.y*c.yx-.5*h*c.yx)-r;
    col = mix(col, .7*n, sm(d));
    
    // 210 Logo on bar
    dlogo210(x+.425*c.yx, .04, d);
    stroke(d, .015, d);
    col = mix(col, mix(c.xyy,c.xxy, clamp((x.y+.465)/.08,0.,1.)), sm(d));
    stroke(d-.005, .002, d);
    col = mix(col, c.xxy, sm(d));
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    a = iResolution.x/iResolution.y;
  	ry = 1.5/iResolution.y;
  	vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);
  	vec3 col = c.yyy;
  
  	colorize(uv,col);
  
  	fragColor = vec4(col, 1.);
}

void main()
{
    mainImage(gl_FragColor, gl_FragCoord.xy);
}
