/*
 * Python binding for the packet.c module.
 *
 * This file is Copyright (c) 2010-2018 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 *
 */

#include "gpsd_config.h"  /* must be before all includes */

/* Python.h insists on setting GNU_SOURCE, _POSIX_C_SOURCE and
 * _XOPEN_SOURCE.  Without guards. */
#undef _GNU_SOURCE
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <Python.h>

#include <stdio.h>
#include "gpsd.h"
#include "python_compatibility.h"

static PyObject *ErrorObject = NULL;

static PyObject *report_callback = NULL;

static void basic_report(const char *buf)
{
    (void)fputs(buf, stderr);
}

void errout_reset(struct gpsd_errout_t *errout)
{
    errout->debug = LOG_SHOUT;
    errout->report = basic_report;
}

void gpsd_log(int errlevel,
              const struct gpsd_errout_t *errout UNUSED,
              const char *fmt, ... )
{
    char buf[BUFSIZ];
    PyObject *args;
    va_list ap;

    if (!report_callback)   /* no callback defined, exit early */
	return;

    if (!PyCallable_Check(report_callback)) {
	PyErr_SetString(ErrorObject, "Cannot call Python callback function");
	return;
    }

    va_start(ap, fmt);
    (void)vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    args = Py_BuildValue("(is)", errlevel, buf);
    if (!args)
	return;

    PyObject *result = PyObject_Call(report_callback, args, NULL);
    Py_XDECREF(result);
    Py_DECREF(args);
}


static PyTypeObject Lexer_Type;

typedef struct {
	PyObject_HEAD
	struct gps_lexer_t lexer;
} LexerObject;

static LexerObject *
newLexerObject(PyObject *arg UNUSED)
{
    LexerObject *self;
    self = PyObject_New(LexerObject, &Lexer_Type);
    if (self == NULL)
	return NULL;
    memset(&self->lexer, 0, sizeof(struct gps_lexer_t));
    packet_reset(&self->lexer);
    return self;
}

/* Lexer methods */

static int
Lexer_init(LexerObject *self)
{
    packet_reset(&self->lexer);
    return 0;
}

static PyObject *
Lexer_get(LexerObject *self, PyObject *args)
{
    ssize_t len;
    int fd;

    if (!PyArg_ParseTuple(args, "i;missing or invalid file descriptor argument to gps.packet.get", &fd))
        return NULL;

    len = packet_get(fd, &self->lexer);
    if (PyErr_Occurred())
	return NULL;

    return Py_BuildValue("(i, i, " GPSD_PY_BYTE_FORMAT ", i)",
			 len,
			 self->lexer.type,
			 self->lexer.outbuffer,
			 self->lexer.outbuflen,
			 self->lexer.char_counter);
}

static PyObject *
Lexer_reset(LexerObject *self)
{
    packet_reset(&self->lexer);
    if (PyErr_Occurred())
	return NULL;
    return 0;
}

static void
Lexer_dealloc(LexerObject *self)
{
    PyObject_Del(self);
}

static PyMethodDef Lexer_methods[] = {
    {"get",	(PyCFunction)Lexer_get,	METH_VARARGS,
    		PyDoc_STR("Get a packet from a file descriptor.")},
    {"reset",	(PyCFunction)Lexer_reset,	METH_NOARGS,
    		PyDoc_STR("Reset the packet lexer to ground state.")},
    {NULL,		NULL}		/* sentinel */
};

PyDoc_STRVAR(Lexer__doc__,
"GPS packet lexer object\n\
\n\
Fetch a single packet from file descriptor");

static PyTypeObject Lexer_Type = {
	/* The ob_type field must be initialized in the module init function
	 * to be portable to Windows without using C++. */
	PyVarObject_HEAD_INIT(NULL, 0)
	"gps.packet.lexer",	/*tp_name*/
	sizeof(LexerObject),	/*tp_basicsize*/
	0,			/*tp_itemsize*/
	/* methods */
	(destructor)Lexer_dealloc, /*tp_dealloc*/
	0,			/*tp_print*/
	0,			/*tp_getattr*/
	0,			/*tp_setattr*/
	0,			/*tp_compare*/
	0,			/*tp_repr*/
	0,			/*tp_as_number*/
	0,			/*tp_as_sequence*/
	0,			/*tp_as_mapping*/
	0,			/*tp_hash*/
        0,                      /*tp_call*/
        0,                      /*tp_str*/
        PyObject_GenericGetAttr,  /*tp_getattro*/
        0,                      /*tp_setattro*/
        0,                      /*tp_as_buffer*/
        Py_TPFLAGS_DEFAULT,     /*tp_flags*/
        Lexer__doc__,           /*tp_doc*/
        0,                      /*tp_traverse*/
        0,                      /*tp_clear*/
        0,                      /*tp_richcompare*/
        0,                      /*tp_weaklistoffset*/
        0,                      /*tp_iter*/
        0,                      /*tp_iternext*/
        Lexer_methods,		/*tp_methods*/
        0,                      /*tp_members*/
        0,                      /*tp_getset*/
        0,                      /*tp_base*/
        0,                      /*tp_dict*/
        0,                      /*tp_descr_get*/
        0,                      /*tp_descr_set*/
        0,                      /*tp_dictoffset*/
        (initproc)Lexer_init,	/*tp_init*/
        0,                      /*tp_alloc*/
        0,                      /*tp_new*/
        0,                      /*tp_free*/
        0,                      /*tp_is_gc*/
};

/* Function of no arguments returning new Lexer object */

static PyObject *
gpspacket_new(PyObject *self UNUSED, PyObject *args UNUSED)
{
    LexerObject *rv;

    if (!PyArg_ParseTuple(args, ":new"))
	return NULL;
    rv = newLexerObject(args);
    if (rv == NULL)
	return NULL;
    return (PyObject *)rv;
}

PyDoc_STRVAR(register_report__doc__,
"register_report(callback)\n\
\n\
callback must be a callable object expecting a string as parameter.");

static PyObject *
register_report(LexerObject *self UNUSED, PyObject *args)
{
    PyObject *callback = NULL;

    if (!PyArg_ParseTuple(args, "O:register_report", &callback))
	return NULL;

    if (!PyCallable_Check(callback)) {
	PyErr_SetString(PyExc_TypeError, "First argument must be callable");
	return NULL;
    }

    if (report_callback) {
	Py_DECREF(report_callback);
	report_callback = NULL;
    }

    report_callback = callback;
    Py_INCREF(report_callback);

    Py_INCREF(Py_None);
    return Py_None;
}


/* List of functions defined in the module */

static PyMethodDef packet_methods[] = {
    {"new",		gpspacket_new,		METH_VARARGS,
     PyDoc_STR("new() -> new packet-lexer object")},
    {"register_report", (PyCFunction)register_report, METH_VARARGS,
			register_report__doc__},
    {NULL,		NULL}		/* sentinel */
};

PyDoc_STRVAR(module_doc,
"Python binding of the libgpsd module for recognizing GPS packets.\n\
The new() function returns a new packet-lexer instance.  Lexer instances\n\
have two methods:\n\
    get() takes a file descriptor argument and returns a tuple consisting of\n\
the integer packet type and string packet value.  On end of file it returns\n\
(-1, '').\n\
    reset() resets the packet-lexer to its initial state.\n\
    The module also has a register_report() function that accepts a callback\n\
for debug message reporting.  The callback will get two arguments, the error\n\
level of the message and the message itself.\n\
");

/* banishes a pointless compiler warning */
extern PyMODINIT_FUNC initpacket(void);

// cppcheck-suppress unusedFunction
GPSD_PY_MODULE_INIT(packet)
{
    PyObject *m;

    /* Create the module and add the functions */
    GPSD_PY_MODULE_DEF(m, "packet", module_doc, packet_methods)

    if (m == NULL || PyType_Ready(&Lexer_Type) < 0)
	return GPSD_PY_MODULE_ERROR_VAL;

    PyModule_AddIntConstant(m, "BAD_PACKET", BAD_PACKET);
    PyModule_AddIntConstant(m, "COMMENT_PACKET", COMMENT_PACKET);
    PyModule_AddIntConstant(m, "NMEA_PACKET", NMEA_PACKET);
    PyModule_AddIntConstant(m, "AIVDM_PACKET", AIVDM_PACKET);
    PyModule_AddIntConstant(m, "GARMINTXT_PACKET", GARMINTXT_PACKET);
    PyModule_AddIntConstant(m, "SIRF_PACKET", SIRF_PACKET);
    PyModule_AddIntConstant(m, "ZODIAC_PACKET", ZODIAC_PACKET);
    PyModule_AddIntConstant(m, "TSIP_PACKET", TSIP_PACKET);
    PyModule_AddIntConstant(m, "EVERMORE_PACKET", EVERMORE_PACKET);
    PyModule_AddIntConstant(m, "ITALK_PACKET", ITALK_PACKET);
    PyModule_AddIntConstant(m, "GARMIN_PACKET", GARMIN_PACKET);
    PyModule_AddIntConstant(m, "NAVCOM_PACKET", NAVCOM_PACKET);
    PyModule_AddIntConstant(m, "UBX_PACKET", UBX_PACKET);
    PyModule_AddIntConstant(m, "SUPERSTAR2_PACKET", SUPERSTAR2_PACKET);
    PyModule_AddIntConstant(m, "ONCORE_PACKET", ONCORE_PACKET);
    PyModule_AddIntConstant(m, "GEOSTAR_PACKET", GEOSTAR_PACKET);
    PyModule_AddIntConstant(m, "RTCM2_PACKET", RTCM2_PACKET);
    PyModule_AddIntConstant(m, "RTCM3_PACKET", RTCM3_PACKET);
    PyModule_AddIntConstant(m, "JSON_PACKET", JSON_PACKET);
    PyModule_AddIntConstant(m, "PACKET_TYPES", PACKET_TYPES);

    PyModule_AddIntConstant(m, "LOG_ERROR", LOG_ERROR);
    PyModule_AddIntConstant(m, "LOG_SHOUT", LOG_SHOUT);
    PyModule_AddIntConstant(m, "LOG_WARN", LOG_WARN);
    PyModule_AddIntConstant(m, "LOG_CLIENT", LOG_CLIENT);
    PyModule_AddIntConstant(m, "LOG_INF", LOG_INF);
    PyModule_AddIntConstant(m, "LOG_PROG", LOG_PROG);
    PyModule_AddIntConstant(m, "LOG_IO", LOG_IO);
    PyModule_AddIntConstant(m, "LOG_DATA", LOG_DATA);
    PyModule_AddIntConstant(m, "LOG_SPIN", LOG_SPIN);
    PyModule_AddIntConstant(m, "LOG_RAW", LOG_RAW);

    return GPSD_PY_MODULE_SUCCESS_VAL(m);
}
