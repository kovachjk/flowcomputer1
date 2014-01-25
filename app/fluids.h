/* 
 * File:   fluid_data.h
 * Author: JKovach
 * Description: Lookup table of standard fluids used by flow calculations.
 *
 * Created on September 22, 2012, 10:31 AM
 */

#ifndef FLUID_DATA_H
#define	FLUID_DATA_H

enum gasLookup
{
    air,
    ammonia,
    agon,
    co2,
    methane,
    natGas,
    nitrogen,
    oxygen,
    propane,
    nx19,
    gasoline,
    kerosene,
    num2Fuel,
    water,
    hygrogen,
    ethylene,
    helium
};
struct lp //liquid parameters
{
    float rDnsty;
    float rTemp;
    float coeffExpan;
    float heatComb;
    float heatSpec;
    float visCoeffA;
    float visCoeffB;


}liquidParams;

struct gp //gp gas parameters
{
    float rDnsty;
    float rTemp;
    int   zFactRef;
    float zFact100;
    float isntrphExpnt;
    float coeffExpan;
    float heatComb;//
    float heatSpec;//
    float visCoeffA;
    float visCoeffB;
}gasParams;


#endif	/* FLUID_DATA_H */

