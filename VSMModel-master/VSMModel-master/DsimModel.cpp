#include "StdAfx.h"
#include "DsimModel.h"

INT DsimModel::isdigital (CHAR *pinname)
{
	return TRUE;							// Indicates this is a digital model
}

VOID DsimModel::setup (IINSTANCE *instance, IDSIMCKT *dsimckt)
{
	inst = instance;
	ckt = dsimckt;
	pin_R = inst->getdsimpin("R", true);	
	pin_S = inst->getdsimpin("S", true);	
	pin_Q = inst->getdsimpin("Q", true);	
}

VOID DsimModel::runctrl (RUNMODES mode)
{
}

VOID DsimModel::actuate (REALTIME time, ACTIVESTATE newstate)
{
}

BOOL DsimModel::indicate (REALTIME time, ACTIVEDATA *data)
{
	return FALSE;
}

VOID DsimModel::simulate(ABSTIME time, DSIMMODES mode) {
	
	if (ishigh(pin_S->istate()) && islow(pin_R->istate())) {
		pin_Q->setstate(time, 1, TSTATE);
	} 
	else if (ishigh(pin_R->istate()) && islow(pin_S->istate())) {
		pin_Q->setstate(time, 0, FSTATE);
	}
	else if (islow(pin_R->istate()) && islow(pin_S->istate())) {
		if (ishigh(pin_Q->istate())) {
			pin_Q->setstate(time, 1, TSTATE);
		}
		else {
			pin_Q->setstate(time, 0, FSTATE);
		}
	}
	else {
		pin_Q->setstate(time, 1, UNDEFINED);
	}
	
	
}

VOID DsimModel::callback (ABSTIME time, EVENTID eventid)
{
}
