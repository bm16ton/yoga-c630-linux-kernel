/*
 * This file is Copyright (c) 2010 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 *
 * Python binding for selected libgps library functions
 */
#include <Python.h>

#include <stdio.h>
#include "gps.h"
#include "gpsdclient.h"
#include "compiler.h"	/* for UNUSED */
#include "python_compatibility.h"

/*
 * Client utility functions
 */

static PyObject *
gpsclient_deg_to_str(PyObject *self UNUSED, PyObject *args)
{
    int fmt;
    double degrees;

    if (!PyArg_ParseTuple(args, "id", &fmt, &degrees))
	return NULL;
    return Py_BuildValue("s", deg_to_str((enum deg_str_type)fmt, degrees));
}

static PyObject *
gpsclient_gpsd_units(PyObject *self UNUSED, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
	return NULL;
    return Py_BuildValue("i", (int)gpsd_units());
}

/*
 * Miscellanea
 */

static PyObject *
gpsclient_wgs84_separation(PyObject *self UNUSED, PyObject *args)
{
    double lat = 0.0, lon = 0.0;
    double sep;

    if (!PyArg_ParseTuple(args, "dd", &lat, &lon))
	return NULL;
    sep = wgs84_separation(lat, lon);
    return Py_BuildValue("d", sep);
}

static PyObject *
gpsclient_maidenhead(PyObject *self UNUSED, PyObject *args)
{
    double lat = 0.0, lon = 0.0;
    char *gs;

    if (!PyArg_ParseTuple(args, "dd", &lat, &lon))
	return NULL;
    gs = maidenhead(lat, lon);
    return Py_BuildValue("s", gs);
}

/* List of functions defined in the module */

static PyMethodDef gpsclient_methods[] = {
    {"wgs84_separation",	gpsclient_wgs84_separation,	METH_VARARGS,
     PyDoc_STR("Return WGS84 geodetic separation in meters.")},
    {"deg_to_str",      	gpsclient_deg_to_str,      	METH_VARARGS,
     PyDoc_STR("String-format a latitude/longitude.")},
    {"gpsd_units",      	gpsclient_gpsd_units,      	METH_VARARGS,
     PyDoc_STR("Deduce a set of units from locale and environment.")},
    {"maidenhead",      	gpsclient_maidenhead,  	METH_VARARGS,
     PyDoc_STR("Maidenhead grid-square locator from lat/lon.")},
    {NULL,		NULL}		/* sentinel */
};

PyDoc_STRVAR(module_doc,
"Python wrapper for selected libgps library routines.\n\
");

/* banishes a pointless compiler warning */
extern PyMODINIT_FUNC initclienthelpers(void);

// cppcheck-suppress unusedFunction
GPSD_PY_MODULE_INIT(clienthelpers)
{
    PyObject *m;

    /* Create the module and add the functions */
    GPSD_PY_MODULE_DEF(m, "clienthelpers", module_doc, gpsclient_methods)

    if (m == NULL)
	return GPSD_PY_MODULE_ERROR_VAL;

    PyModule_AddIntConstant(m, "deg_dd", deg_dd);
    PyModule_AddIntConstant(m, "deg_ddmm", deg_ddmm);
    PyModule_AddIntConstant(m, "deg_ddmmss", deg_ddmmss);

    PyModule_AddIntConstant(m, "unspecified", unspecified);
    PyModule_AddIntConstant(m, "imperial", imperial);
    PyModule_AddIntConstant(m, "nautical", nautical);
    PyModule_AddIntConstant(m, "metric", metric);

    return GPSD_PY_MODULE_SUCCESS_VAL(m);
}
