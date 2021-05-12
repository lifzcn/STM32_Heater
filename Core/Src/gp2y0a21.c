#include "gp2y0a21.h"

float GP2Y0A21_GetDistance(float value)
{
	float distance;
	if(value>=0.755&&value<=0.885)
	{
		distance=-20*value+70;
	}
	else if(value>=0.885&&value<=2.555)
	{
		distance=-10*value+40;
	}
//	if(value>=82&&value<=115)
//	{
//		distance=(-5*value+905)/33.0;
//	}
//	else if(value>=65&&value<82)
//	{
//		distance=(-5*value+665)/17.0;
//	}
//	else if(value>=46&&value<65)
//	{
//		distance=(-10*value+1030)/19.0;
//	}
//	else if(value>=36&&value<46)
//	{
//		distance=76.0-value;	
//	}
//	else if(value>=30&&value<36)
//	{
//		distance=(-5/3.0)*value+100.0;
//	}
//	else if(value>=26&&value<30)
//	{
//		distance=(-5/2.0)*value+125.0;
//	}
//	else if(value>=23&&value<26)
//	{
//		distance=(-10*value+440)/3;
//	}
//	else if(value>=21&&value<23)
//	{
//		distance=-5.0*value+185.0;
//	}
	return distance;
}
