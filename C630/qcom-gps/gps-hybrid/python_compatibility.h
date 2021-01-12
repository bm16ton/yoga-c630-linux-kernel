/*
 * python_compatibility.h -- macros for Python 2/3 compatibility
 *
 * This file is Copyright (c) 2016 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 *
 * Definitions based on examples in "Supporting Python 3 - The Book Site"
 *     http://python3porting.com/cextensions.html
 */

#ifndef _PYTHON_COMPATIBILITY_H_
#define _PYTHON_COMPATIBILITY_H_

#include <Python.h>

#if PY_MAJOR_VERSION >= 3

#define GPSD_PY_MODULE_INIT(name) PyMODINIT_FUNC PyInit_##name(void)

#define GPSD_PY_MODULE_DEF(mod, name, doc, methods) \
    static struct PyModuleDef moduledef = { \
        PyModuleDef_HEAD_INIT, name, doc, -1, methods, }; \
    mod = PyModule_Create(&moduledef);

#define GPSD_PY_MODULE_ERROR_VAL NULL
#define GPSD_PY_MODULE_SUCCESS_VAL(val) val

#define GPSD_PY_BYTE_FORMAT "y#"

#else /* !Python 3 */

#define GPSD_PY_MODULE_INIT(name) PyMODINIT_FUNC init##name(void)

#define GPSD_PY_MODULE_DEF(mod, name, doc, methods) \
    mod = Py_InitModule3(name, methods, doc);

#define GPSD_PY_MODULE_ERROR_VAL
#define GPSD_PY_MODULE_SUCCESS_VAL(val)

#define GPSD_PY_BYTE_FORMAT "s#"

#endif /* !Python 3 */

#endif /* _PYTHON_COMPATIBILITY_H_ */
