/* Generated with shader-compressor by NR4/Team210. */
#ifndef LOAD_H
#define LOAD_H
const char * load_frag =
"/* Fuer Elite - 64k Intro by Team210 at Underground Conference 9\n"
" * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>\n"
" * \n"
" * This program is free software: you can redistribute it and/or modify\n"
" * it under the terms of the GNU General Public License as published by\n"
" * the Free Software Foundation, either version 3 of the License, or\n"
" * (at your option) any later version.\n"
" * \n"
" * This program is distributed in the hope that it will be useful,\n"
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" * GNU General Public License for more details.\n"
" * \n"
" * You should have received a copy of the GNU General Public License\n"
" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
" */\n"
"\n"
"#version 130\n"
"\n"
"uniform float iTime, iProgress;\n"
"uniform vec2 iResolution;\n"
"\n"
"// Global constants\n"
"const float pi = acos(-1.);\n"
"const vec3 c = vec3(1.0, 0.0, -1.0);\n"
"float a = 1.0, ry = 1.0;\n"
"\n"
"void rand(in vec2 x, out float n)\n"
"{\n"
"    x += 400.;\n"
"    n = fract(sin(dot(sign(x)*abs(x) ,vec2(12.9898,78.233)))*43758.5453);\n"
"}\n"
"\n"
"void lfnoise(in vec2 t, out float n)\n"
"{\n"
"    vec2 i = floor(t);\n"
"    t = fract(t);\n"
"    t = smoothstep(c.yy, c.xx, t);\n"
"    vec2 v1, v2;\n"
"    rand(i, v1.x);\n"
"    rand(i+c.xy, v1.y);\n"
"    rand(i+c.yx, v2.x);\n"
"    rand(i+c.xx, v2.y);\n"
"    v1 = c.zz+2.*mix(v1, v2, t.y);\n"
"    n = mix(v1.x, v1.y, t.x);\n"
"}\n"
"\n"
"void mfnoise(in vec2 x, in float d, in float b, in float e, out float n)\n"
"{\n"
"    n = 0.;\n"
"    float a = 1., nf = 0., buf;\n"
"    for(float f = d; f<b; f *= 2.)\n"
"    {\n"
"        lfnoise(f*x, buf);\n"
"        n += a*buf;\n"
"        a *= e;\n"
"        nf += 1.;\n"
"    }\n"
"    n *= (1.-e)/(1.-pow(e, nf));\n"
"}\n"
"\n"
"//distance to spline with parameter t\n"
"float dist2(vec2 p0,vec2 p1,vec2 p2,vec2 x,float t)\n"
"{\n"
"    t = clamp(t, 0., 1.);\n"
"    return length(x-pow(1.-t,2.)*p0-2.*(1.-t)*t*p1-t*t*p2);\n"
"}\n"
"\n"
"//minimum dist3ance to spline\n"
"void dspline2(in vec2 x, in vec2 p0, in vec2 p1, in vec2 p2, out float ds)\n"
"{\n"
"    //coefficients for 0 = t^3 + a * t^2 + b * t + c\n"
"    vec2 E = x-p0, F = p2-2.*p1+p0, G = p1-p0;\n"
"    vec3 ai = vec3(3.*dot(G,F), 2.*dot(G,G)-dot(E,F), -dot(E,G))/dot(F,F);\n"
"\n"
"	//discriminant and helpers\n"
"    float tau = ai.x/3., p = ai.y-tau*ai.x, q = - tau*(tau*tau+p)+ai.z, dis = q*q/4.+p*p*p/27.;\n"
"    \n"
"    //triple real root\n"
"    if(dis > 0.) \n"
"    {\n"
"        vec2 ki = -.5*q*c.xx+sqrt(dis)*c.xz, ui = sign(ki)*pow(abs(ki), c.xx/3.);\n"
"        ds = dist2(p0,p1,p2,x,ui.x+ui.y-tau);\n"
"        return;\n"
"    }\n"
"    \n"
"    //three dist3inct real roots\n"
"    float fac = sqrt(-4./3.*p), arg = acos(-.5*q*sqrt(-27./p/p/p))/3.;\n"
"    vec3 t = c.zxz*fac*cos(arg*c.xxx+c*pi/3.)-tau;\n"
"    ds = min(\n"
"        dist2(p0,p1,p2,x, t.x),\n"
"        min(\n"
"            dist2(p0,p1,p2,x,t.y),\n"
"            dist2(p0,p1,p2,x,t.z)\n"
"        )\n"
"    );\n"
"}\n"
"\n"
"void dlinesegment2(in vec2 x, in vec2 p1, in vec2 p2, out float d)\n"
"{\n"
"    vec2 da = p2-p1;\n"
"    d = length(x-mix(p1, p2, clamp(dot(x-p1, da)/dot(da,da),0.,1.)));\n"
"}\n"
"\n"
"void dcircle(in vec2 x, in float R, out float d)\n"
"{\n"
"    d = length(x)-R;\n"
"}\n"
"\n"
"// Stroke\n"
"void stroke(in float d0, in float s, out float d)\n"
"{\n"
"    d = abs(d0)-s;\n"
"}\n"
"\n"
"void smoothmin(in float a, in float b, in float k, out float dst)\n"
"{\n"
"    float h = max( k-abs(a-b), 0.0 )/k;\n"
"    dst = min( a, b ) - h*h*h*k*(1.0/6.0);\n"
"}\n"
"\n"
"void colorize(in vec2 x, out vec3 col)\n"
"{\n"
"    vec2 dsx = vec2(x.x, x.y);\n"
"    vec3 bcol = vec3(0.99,0.63,0.11),\n"
"        gray = vec3(0.62,0.59,0.48),\n"
"        lightgray = vec3(0.83,0.82,0.77),\n"
"        beer = mix(vec3(0.99,0.80,0.00), vec3(0.97,0.65,0.09), (.5+.5*x.y)/.8),\n"
"        lightbeer = mix(vec3(1.00,0.87,0.07), vec3(1.00,0.98,0.76), (.5+.5*x.y)/.8);\n"
"    \n"
"    // bubbles\n"
"    float dc = 1.;\n"
"    for(int i=0; i<200; ++i)\n"
"    {\n"
"        float index = float(i);\n"
"        vec2 dx;\n"
"        rand(index*c.xx, dx.x);\n"
"        rand(index*c.xx-1338., dx.y);\n"
"        float dd;\n"
"        dcircle(mod(.5+x-vec2(.2,.5)*mix(-c.xx,c.xx,dx)-1.*iProgress*c.yx,1.)-.5, .03*dx.x, dd);\n"
"        \n"
"        smoothmin(dc, dd, .02, dc);\n"
"    }\n"
"    float ddc;\n"
"    stroke(dc, .002, ddc);\n"
"    beer = mix(beer, vec3(0.73,0.47,0.00), smoothstep(ry, -ry, ddc));\n"
"    beer = mix(beer, vec3(0.98,0.78,0.07), smoothstep(ry, -ry, dc+.005));\n"
"    \n"
"    float d, da, db, dhandle, dbeer;\n"
"    dlinesegment2(vec2(.5,1.)*x, .25*c.yz, .25*c.yx, d);\n"
"    stroke(d, .1, d);\n"
"    dspline2(x, vec2(.2,-.15), vec2(.35,-.1)+.1*c.yz, vec2(.35,.05), da);\n"
"    dspline2(x, vec2(.35,.05), vec2(.35, .15), vec2(.2,.15), db);\n"
"    da = min(da, db);\n"
"    dhandle = da;\n"
"    stroke(da, .04, da);\n"
"  	smoothmin(d, da, .05, d);\n"
"    col = mix(col, bcol, smoothstep(ry, -ry, d));\n"
"    stroke(dhandle, .03, da);\n"
"    col = mix(col, gray, smoothstep(ry, -ry, d+.01));\n"
"    stroke(dhandle, .025, da);\n"
"    col = mix(col, lightgray, smoothstep(ry, -ry, da));\n"
"    stroke(dhandle, .005, da);\n"
"    col = mix(col, c.xxx, smoothstep(ry, -ry, da));\n"
"    \n"
"    dspline2(x, vec2(-.15,-.27), vec2(0.,-.36), vec2(.15,-.27), da);\n"
"    \n"
"    dlinesegment2(vec2(.5,1.)*x, .25*c.yz, .25*c.yx, dbeer);\n"
"    stroke(dbeer, .095, dbeer);\n"
"    col = mix(col, beer, smoothstep(ry,-ry,dbeer));\n"
"    \n"
"    // stripes\n"
"    dlinesegment2(vec2(.5,1.)*vec2(abs(x.x-.03)-.1,x.y)-.4*abs(x.x)*c.yx, -.3*c.yx, .25*c.yx, dbeer);\n"
"    stroke(dbeer, .015, dbeer);\n"
"    col = mix(col, lightbeer, smoothstep(ry,-ry,dbeer));\n"
"    \n"
"    stroke(da, .02, db);\n"
"    col = mix(col, lightgray, smoothstep(ry, -ry, db));\n"
"    \n"
"    dlinesegment2(vec2(.5,1.)*x, .2*c.yx-.4*iProgress*c.yx, .25*c.yx, dbeer);\n"
"    stroke(dbeer, .095, dbeer);\n"
"    col = mix(col, vec3(0.78,0.44,0.05), smoothstep(ry,-ry,dbeer));\n"
"    \n"
"    dlinesegment2(vec2(.5,1.)*x, .2*c.yx-.4*iProgress*c.yx, .25*c.yx, dbeer);\n"
"    stroke(dbeer, .092, dbeer);\n"
"    col = mix(col, vec3(0.95,0.94,0.87), smoothstep(ry,-ry,dbeer));\n"
"    \n"
"    // stripes\n"
"    dlinesegment2(vec2(.5,1.)*vec2(abs(x.x-.03)-.1,x.y)-.4*abs(x.x)*c.yx, .12*c.yx-.4*iProgress*c.yx, .25*c.yx, dbeer);\n"
"    stroke(dbeer, .015, dbeer);\n"
"    col = mix(col, vec3(1.00,1.00,1.00), smoothstep(ry,-ry,dbeer));\n"
"    \n"
"    // Foam\n"
"    dlinesegment2(vec2(.5,1.)*x, .3*c.yx, .3*c.yx, dbeer);\n"
"    dlinesegment2(x, vec2(-.2,.3), vec2(-.2,.1), da);\n"
"    stroke(da, .06, da);\n"
"    stroke(dbeer, .095, dbeer);\n"
"    smoothmin(dbeer, da, .05, dbeer);\n"
"    float n;\n"
"    mfnoise(x-.1*iTime,8.,800.,.35,n);\n"
"    dbeer += .03*mix(-1.,1.,n);\n"
"    col = mix(col, vec3(0.78,0.76,0.69), smoothstep(ry,-ry,dbeer));\n"
"    dbeer += .01*x.y;\n"
"    col = mix(col, vec3(0.88,0.88,0.81), smoothstep(ry,-ry,dbeer));\n"
"    dbeer += .05*x.y;\n"
"    col = mix(col, vec3(0.95,0.95,0.89), smoothstep(ry,-ry,dbeer));\n"
"    dbeer += .1*x.y;\n"
"    col = mix(col, vec3(1.00,1.00,0.95), smoothstep(ry,-ry,dbeer));\n"
"}\n"
"\n"
"void mainImage(out vec4 fragColor, in vec2 fragCoord)\n"
"{\n"
"  	a = iResolution.x/iResolution.y;\n"
"  	ry = 1.5/iResolution.y;\n"
"  	vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);\n"
"  	vec3 col = c.yyy;\n"
"  \n"
"  	colorize(uv,col);\n"
"  \n"
"  	fragColor = vec4(col, 1.);\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    mainImage(gl_FragColor, gl_FragCoord.xy);\n"
"}\n"
"\n"
;
#endif
