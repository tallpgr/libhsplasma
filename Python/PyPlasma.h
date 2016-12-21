/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PYPLASMA_H
#define _PYPLASMA_H

#include <Python.h>
#include <Util/plString.h>

PyObject* PlasmaString_To_PyString(const plString& str);
PyObject* PlasmaString_To_PyUnicode(const plString& str);
plString PyString_To_PlasmaString(PyObject* str);

// The Python API insists that character constants are "char *" without the
// const. Sane compilers complain about this (with good reason). Therefore:
template <size_t size>
inline char* _pycs(const char (&str)[size]) { return const_cast<char*>(str); }

// Python 3.x does things differently...  This should help to keep things
// under control with both 2.x and 3.0 somewhat seamlessly.
#if (PY_MAJOR_VERSION >= 3)
    // Int -> Long
    #define PyInt_Check(ob) PyLong_Check(ob)
    #define PyInt_FromLong PyLong_FromLong
    #define PyInt_AsLong PyLong_AsLong

    // String -> Unicode
    #define PyAnyStr_Check(ob) (PyUnicode_Check(ob) || PyBytes_Check(ob))
    #define PyString_FromString(str) PyUnicode_DecodeUTF8((str), strlen((str)), NULL)
    #define PlStr_To_PyStr PlasmaString_To_PyUnicode

    // Py_TPFLAGS_CHECKTYPES is no longer used in Py3k
    #define Py_TPFLAGS_CHECKTYPES 0
#elif (PY_MAJOR_VERSION == 2) && (PY_MINOR_VERSION >= 6)
    #undef PyBytes_Check
    #undef PyBytes_FromStringAndSize
    #undef PyBytes_AsStringAndSize
    #undef PyBytes_AsString

    #define PlStr_To_PyStr PlasmaString_To_PyString
    #define PyBytes_Check(ob) PyString_Check(ob)
    #define PyBytes_FromStringAndSize(v, len) PyString_FromStringAndSize(v, len)
    #define PyBytes_AsStringAndSize(obj, buf, len) PyString_AsStringAndSize(obj, buf, len)
    #define PyBytes_AsString PyString_AsString
    #define PyAnyStr_Check(ob) (PyUnicode_Check(ob) || PyBytes_Check(ob))
#else
    #error Your Python version is too old.  Only 2.6 and later are supported
#endif

#if (PY_MAJOR_VERSION >= 3) || ((PY_MAJOR_VERSION == 2) && (PY_MINOR_VERSION >= 6))
    #define TP_VERSION_TAG_INIT 0,
#else
    #define TP_VERSION_TAG_INIT
#endif

#if (PY_MAJOR_VERSION >= 4) || ((PY_MAJOR_VERSION == 3) && (PY_MINOR_VERSION >= 4))
    #define TP_FINALIZE_INIT NULL,
#else
    #define TP_FINALIZE_INIT
#endif

// This should work the same for all versions
#define PyStr_To_PlStr PyString_To_PlasmaString

/* Use this macro to ensure the layouts of subclass types are consistent */
#define PY_WRAP_PLASMA(pyType, plType)                          \
    extern "C" {                                                \
    struct py##pyType {                                         \
        PyObject_HEAD                                           \
        plType* fThis;                                          \
        bool fPyOwned;                                          \
    };                                                          \
    extern PyTypeObject py##pyType##_Type;                      \
    PyObject* Init_py##pyType##_Type();                         \
    int py##pyType##_Check(PyObject* obj);                      \
    PyObject* py##pyType##_From##pyType(plType*);               \
    }

#define PY_WRAP_PLASMA_VALUE(pyType, plType)                    \
    extern "C" {                                                \
    struct py##pyType {                                         \
        PyObject_HEAD                                           \
        plType* fThis;                                          \
    };                                                          \
    extern PyTypeObject py##pyType##_Type;                      \
    PyObject* Init_py##pyType##_Type();                         \
    int py##pyType##_Check(PyObject* obj);                      \
    PyObject* py##pyType##_From##pyType(const plType&);         \
    }

#define PY_PLASMA_CHECK_TYPE(pyType)                                    \
    int py##pyType##_Check(PyObject* obj) {                             \
        if (obj->ob_type == &py##pyType##_Type                          \
            || PyType_IsSubtype(obj->ob_type, &py##pyType##_Type))      \
            return 1;                                                   \
        return 0;                                                       \
    }

#define PY_PLASMA_IFC_METHODS(pyType, plType)                           \
    PY_PLASMA_CHECK_TYPE(pyType)                                        \
    PyObject* py##pyType##_From##pyType(plType* obj) {                  \
        if (!obj) {                                                     \
            Py_INCREF(Py_None);                                         \
            return Py_None;                                             \
        }                                                               \
        py##pyType* pyobj = PyObject_New(py##pyType, &py##pyType##_Type); \
        pyobj->fThis = obj;                                             \
        pyobj->fPyOwned = false;                                        \
        return (PyObject*)pyobj;                                        \
    }

#define PY_PLASMA_VALUE_IFC_METHODS(pyType, plType)                     \
    PY_PLASMA_CHECK_TYPE(pyType)                                        \
    PyObject* py##pyType##_From##pyType(const plType& obj) {            \
        py##pyType* pyobj = PyObject_New(py##pyType, &py##pyType##_Type); \
        pyobj->fThis = new plType(obj);                                 \
        return (PyObject*)pyobj;                                        \
    }

#endif
