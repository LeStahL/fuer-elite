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

out vec4 gl_FragColor;

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

void dstar(in vec2 x, in float N, in vec2 R, out float dst)
{
    float d = pi/N,
        p0 = acos(x.x/length(x)),
        p = mod(p0, d),
        i = mod(round((p-p0)/d),2.);
    x = length(x)*vec2(cos(p),sin(p));
    vec2 a = mix(R,R.yx,i),
    	p1 = a.x*c.xy,
        ff = a.y*vec2(cos(d),sin(d))-p1;
   	ff = ff.yx*c.zx;
    dst = dot(x-p1,ff)/length(ff);
}

void colorize(in vec2 x, out vec3 col)
{
    if(iTime < 48.)
    {
        col = vec3(0.12,0.13,0.16);
        float d;
        
        x += .02+.02*fract(iTime/.375/4.)*fract(iTime/.375/4.)*x;
        
        // Wall concrete
        dbox(x-.1*c.yx, vec2(.5*a, .3), d);
        col = mix(col, vec3(0.48,0.37,0.33), sm(d));
        dbox(x+.25*c.yx, vec2(.5*a, .075), d);
        col = mix(col, vec3(0.62,0.62,0.63), sm(d));
        dbox(x+.33*c.yx, vec2(.5*a, .01), d);
        col = mix(col, c.xxx, sm(d));
        dbox(x+.36*c.yx, vec2(.5*a, .02), d);
        col = mix(col, vec3(0.55,0.52,0.48), sm(d));
        
        // Windows
        if(abs(x.x+.3) > .4)
        {
            // Basement windows
            vec2 a = vec2(mod(x.x-.1, .4)-.2, x.y);
            dbox(a+.29*c.yx, vec2(.1,.03), d);
            col = mix(col, mix(vec3(0.29,0.26,0.25),vec3(0.49,0.46,0.43),step(fract(35.*(x.x-.4/35.))-.2,0.)), sm(d));
            
            // Main windows
            dbox(a-.1*c.yx, vec2(.12, .15), d);
            col = mix(col, vec3(0.65,0.65,0.66), sm(d));
            stroke(d+.001, .001, d);
            col = mix(col, c.yyy, sm(d));

            // Glass
            vec2 b = a;
            mirror(a - .1*c.yx, vec2(.04, .04), b);
            stroke(b.y, .04, b.y);
            dbox(b, vec2(.038), d);
            vec3 n;
            lfnoise(12.*x-floor(iTime/.375), n.x);
            lfnoise(12.*x-floor(iTime/.375)+1337., n.y);
            lfnoise(12.*x-floor(iTime/.375)+2337., n.z);
            n = clamp((1.3+.2*sin(2.*pi*iTime))*(.5+.5*n), 0., 1.);
            col = mix(col, n, sm(d));
            
            // Sides
            b = a;
            stroke(a.x, .12, b.x);
            dbox(b-.1*c.yx, vec2(.05, .12), d);
            col = mix(col, mix(vec3(0.65,0.68,0.75), vec3(0.30,0.27,0.24), step(d+.02,0.)*step((fract(80.*x.y)-.5)/80.,0.)), sm(d));
            stroke(d+.001, .001, d);
            col = mix(col, c.yyy, sm(d));
        }
        // Door back
        vec2 y = x-vec2(-.2,-.15);
        stroke(y.x,.101, y.x);
        dbox(y, vec2(.1,.2), d);
        col = mix(col, vec3(0.09,0.20,0.18), sm(d));
        
        // Door inner part
        vec2 z;
        mirror(y,vec2(.045,.08), z);
        dbox(z, vec2(.035,.06), d);
        col = mix(col, vec3(0.07,0.11,0.12), sm(d));
        stroke(d, .003, d);
        col = mix(col, c.yyy, sm(d));
        
        // Door upper part
        float da = length((x-vec2(-.2,.15))*vec2(1.,3.))-.2;
        dbox(x-vec2(-.2,.1),vec2(.2,.05), d);
        d = min(d,da);
        col = mix(col, vec3(0.20,0.32,0.26)*step(fract(35.*(x.x-.5/35.))-.8,0.), sm(d)); 
        
        // Door 210 logo
        da = length((x-vec2(-.2,.125))*vec2(1.,2.))-.14;
        col = mix(col, vec3(0.14,0.12,0.13), sm(da));
        stroke(da+.005, .002, da);
        col = mix(col, c.yyy, sm(da));
        dlogo210(x-vec2(-.2,.125), .04,da);
        stroke(da,.0125,da);
        col = mix(col, mix(c.xyy,c.xxy,clamp((x.y)/.3,0.,1.)), sm(da));
        stroke(da-.005, .002, da);
        col = mix(col,c.yyy, sm(da));
        
        // Door side bricks
        vec2 w = x+.2*c.xy;
        stroke(w.x, .23, w.x);
        dlinesegment(w,-.33*c.yx, .18*c.yx, da);
        float db;
        dspline2(x,vec2(-.44,.18),vec2(-.24,.3),vec2(.04,.18),db);
        da = min(da, db);
        stroke(da, .01, db);
        stroke(da, .03, da);
        col = mix(col, vec3(0.48,0.52,0.59), sm(da));
        col = mix(col, .8*vec3(0.48,0.52,0.59), sm(db));
        
        // Smoke
        float dsmoke;
        vec3 cs = col;
        dlinesegment(vec2(.125,1.)*x, .35*c.yx, .35*c.yx, dsmoke);
        dlinesegment(x, vec2(.2,.3), vec2(-.2,-.2), da);
        stroke(da, .01, da);
        stroke(dsmoke, .095, dsmoke);
        smoothmin(dsmoke, da, .5, dsmoke);
        float n;
        mfnoise(x-.1*iTime,8.,800.,.35,n);
        dsmoke += .03*mix(-1.,1.,n);
        cs = mix(cs, .1*c.xxx, sm(dsmoke));
        dsmoke += .01*x.y;
        cs = mix(cs, .2*c.xxx, sm(dsmoke));
        dsmoke += .05*x.y;
        cs = mix(cs, .3*c.xxx, sm(dsmoke));
        dsmoke += .1*x.y;
        cs = mix(cs, .4*c.xxx, sm(dsmoke));
        col = mix(col, cs, smoothstep(30.,31., iTime));
    }
    else
    {
        col = c.yyy;
        for(float r = 0.; r < mix(.1,1.,clamp(iTime,0.,1.)); r += .2)
        {
            float ri = fract(r + iTime);
            float d;
            dstar(x,12.,vec2(.5*ri, ri),d);
            stroke(d, .05, d);
            col = mix(col, c.xxy, sm(d));
            stroke(d-.02,.01,d);
            col = mix(col, c.xyy, sm(d));
        }
        col = mix(col, c.yyy, clamp(iTime-53.,0.,1.));
    }
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    a = iResolution.x/iResolution.y;
  	ry = 1.5/iResolution.y;
  	vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);
  	vec3 col = c.yyy;
  
  	colorize(uv,col);
  
    col = mix(c.yyy, col, smoothstep(9.,10.,iTime)*(1.-smoothstep(20.,21.,iTime))
                         +smoothstep(48.,48.1,iTime)*(1.-smoothstep(50.9,51.,iTime))
                         +smoothstep(30.,31.,iTime)*(1.-smoothstep(40.,41.,iTime)));

  	fragColor = vec4(col, 1.);
}

void main()
{
    mainImage(gl_FragColor, gl_FragCoord.xy);
}
