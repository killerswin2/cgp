
{
    vec2 pa = p - a;
    vec2 ba = b - a;

    float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0);

    return length( pa - ba*h );
}


vec2 rotatePoint(vec2 center,float angle,vec2 p)
{
  float s = sin(angle);
  float c = cos(angle);

  // translate point back to origin:
  p.x -= center.x;
  p.y -= center.y;

  // rotate point
  float xnew = p.x * c - p.y * s;
  float ynew = p.x * s + p.y * c;

  // translate point back:
  p.x = xnew + center.x;
  p.y = ynew + center.y;
  return p;
}


void getBlips(float radius, out vec2[1] blipsOut)
{	
	vec2 cen = iResolution.xy/2.0;
	float sec = iDate[3];
	float mdl = mod(sec,10.0);
	
	//From 1 to 6 
	float cstepRot = ((sec-mdl)/10.0)+1.0;
	float factorRot = cstepRot/6.0;
	
	float factorLen = sin(factorRot)/2.0;
	float len = radius*factorLen;//0.5;);
	vec2 targetP = vec2(cen.x,cen.y+len);	
	float ang  =  PI*factorRot*2.0;
	targetP = rotatePoint(cen,ang,targetP);
	
	blipsOut[0] = targetP;		
}

float angleVec(vec2 a_, vec2 b_) 
{
    vec3 a = vec3(a_, 0);
    vec3 b = vec3(b_, 0);
     float dotProd = dot(a,b); 
     vec3 crossprod = cross(a,b);
     float crossprod_l = length(crossprod);
     float lenProd = length(a)*length(b);
     float cosa = dotProd/lenProd;
     float sina = crossprod_l/lenProd;
     float angle = atan(sina, cosa);
    
     if(dot(vec3(0,0,1), crossprod) < 0.0) 
        angle=90.0;
     return (angle * (180.0 / PI));
}

void main( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 center =iResolution.xy/2.0;
	float minRes = min(center.x,center.y);
	float radius =minRes-minRes*0.1;
	float circleWitdh = radius*0.02;
	float lineWitdh = circleWitdh*0.8;
	float angleStela = 180.0;	
	vec2 lineEnd =  vec2(center.x,center.y+radius);

	float blue =0.0;
	float green =0.0;
	
	float distanceToCenter = distance(center,fragCoord.xy);	
	float disPointToCircle=abs(distanceToCenter-radius);
							
	//Draw Circle
	if (disPointToCircle<circleWitdh)
	{
		green= 1.0-(disPointToCircle/circleWitdh);
	}
	
	//Rotate Line
	float angle = (-iTime*1.2);
	lineEnd = rotatePoint(center,angle,lineEnd);
	
	//Draw Line	
	float distPointToLine = LineToPointDistance2D(center,lineEnd,fragCoord.xy);
	if (distPointToLine<lineWitdh)
	{ 
		float val = 1.0-distPointToLine/lineWitdh;
		if (val>green)
			green=val;
	}
	
	
	//Draw Stela
	float angleStelaToApply = angleVec(normalize(lineEnd-center),normalize(fragCoord.xy-center));
	if (angleStelaToApply<angleStela && distanceToCenter<radius-circleWitdh/2.0+1.0)
	{
		float factorAngle = 1.0-angleStelaToApply/angleStela;
		
		float finalFactorAngle = (factorAngle*0.5)-0.15;
		
		
		if (finalFactorAngle>green)
			green=finalFactorAngle;
		

			
		//DrawBlips
		vec2 blips[1];
		float angles[1];
		getBlips(radius,blips);

		
		float distToBlip = distance(fragCoord.xy,blips[0]);//blips[0]);
			
		if (distToBlip<15.0)
		{
			float blipFactor = 1.0-distToBlip/15.0;
			float toSubtract = 1.0-factorAngle;
			float final = blipFactor-toSubtract;
			if (final>green)
			green = final;
		}			
	}

	fragColor = vec4(0.0,green,blue,1.0);
}


