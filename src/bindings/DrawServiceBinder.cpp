/******************************************************************************
 *
 *    This file is part of openDarkEngine project
 *    Copyright (C) 2009 openDarkEngine team
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *	   $Id$
 *
 *****************************************************************************/

#include "bindings.h"
#include "DrawServiceBinder.h"
#include "DrawSheet.h"
#include "DrawSheetBinder.h"
#include "DrawSourceBinder.h"
#include "RenderedImageBinder.h"

namespace Opde {

	namespace Python {

		// -------------------- Draw Service --------------------
		const char* DrawServiceBinder::msName = "DrawService";

		// ------------------------------------------
		PyTypeObject DrawServiceBinder::msType = {
			PyObject_HEAD_INIT(&PyType_Type)
			0,
			"opde.services.DrawService",                   // char *tp_name; */
			sizeof(DrawServiceBinder::Object),  // int tp_basicsize; */
			0,                        // int tp_itemsize;       /* not used much */
			DrawServiceBinder::dealloc,   // destructor tp_dealloc; */
			0,			              // printfunc  tp_print;   */
			DrawServiceBinder::getattr,  // getattrfunc  tp_getattr; /* __getattr__ */
			0,   					  // setattrfunc  tp_setattr;  /* __setattr__ */
			0,				          // cmpfunc  tp_compare;  /* __cmp__ */
			repr,			              // reprfunc  tp_repr;    /* __repr__ */
			0,				          // PyNumberMethods *tp_as_number; */
			0,                        // PySequenceMethods *tp_as_sequence; */
			0,                        // PyMappingMethods *tp_as_mapping; */
			0,			              // hashfunc tp_hash;     /* __hash__ */
			0,                        // ternaryfunc tp_call;  /* __call__ */
			0,			              // reprfunc tp_str;      /* __str__ */
			0,			              // getattrofunc tp_getattro; */
			0,			              // setattrofunc tp_setattro; */
			0,			              // PyBufferProcs *tp_as_buffer; */
			0,			              // long tp_flags; */
			0,			              // char *tp_doc;  */
			0,			              // traverseproc tp_traverse; */
			0,			              // inquiry tp_clear; */
			0,			              // richcmpfunc tp_richcompare; */
			0,			              // long tp_weaklistoffset; */
			0,			              // getiterfunc tp_iter; */
			0,			              // iternextfunc tp_iternext; */
			msMethods,	              // struct PyMethodDef *tp_methods; */
			0,			              // struct memberlist *tp_members; */
			0,			              // struct getsetlist *tp_getset; */
		};

		// ------------------------------------------
		PyMethodDef DrawServiceBinder::msMethods[] = {
				{"createSheet", createSheet, METH_VARARGS},
				{"destroySheet", destroySheet, METH_VARARGS},
				{"getSheet", getSheet, METH_VARARGS},
				{"setActiveSheet", setActiveSheet, METH_VARARGS},
				{"createDrawSource", createDrawSource, METH_VARARGS},
				{"createRenderedImage", createRenderedImage, METH_VARARGS},
				{"createRenderedLabel", createRenderedLabel, METH_VARARGS},
				{"destroyDrawOperation", destroyDrawOperation, METH_VARARGS},
				{"createAtlas", createAtlas, METH_VARARGS},
				{"destroyAtlas", destroyAtlas, METH_VARARGS},
				{"loadFont", loadFont, METH_VARARGS},
				{"setFontPalette", setFontPalette, METH_VARARGS},
				{NULL, NULL},
		};

		// ------------------------------------------
		PyObject* DrawServiceBinder::createSheet(PyObject* self, PyObject* args) {
			__PYTHON_EXCEPTION_GUARD_BEGIN_;
			
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;

			
			// argument - the name of the sheet to create, string
			const char* sname;

			if (PyArg_ParseTuple(args, "s", &sname)) {
			    DrawSheet* i = o->createSheet(sname);
			    
			    // TODO: Sheet binding...
			    PyObject *o = DrawSheetBinder::create(i);
			    
				result = o;
				
				return result;
			} else {
				// Invalid parameters
				PyErr_SetString(PyExc_TypeError, "Expected a string argument!");
				return NULL;
			}
		
			__PYTHON_EXCEPTION_GUARD_END_;
		}
		
		// ------------------------------------------
		PyObject* DrawServiceBinder::destroySheet(PyObject* self, PyObject* args) {
			__PYTHON_EXCEPTION_GUARD_BEGIN_;
			
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;

			
			PyObject *sheet;
			if (PyArg_ParseTuple(args, "o", &sheet)) {
				// cast to drawsheet and destroy
				DrawSheet* ds;
				
				if (!DrawSheetBinder::extract(sheet, ds))
					__PY_CONVERR_RET;
				
				o->destroySheet(ds);
			}

			result = Py_None;
			Py_INCREF(result);
			return result;
			
			__PYTHON_EXCEPTION_GUARD_END_;
		}
		
		// ------------------------------------------
		PyObject* DrawServiceBinder::getSheet(PyObject* self, PyObject* args) {
			__PYTHON_EXCEPTION_GUARD_BEGIN_;
						
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			// argument - the name of the sheet to create, string
			const char* sname;

			if (PyArg_ParseTuple(args, "s", &sname)) {
				DrawSheet* i = o->getSheet(sname);
				
				PyObject *o = DrawSheetBinder::create(i);
				
				result = o;
				Py_INCREF(result);
				return result;
			} else {
				// Invalid parameters
				PyErr_SetString(PyExc_TypeError, "Expected a string argument!");
				return NULL;
			}
			
			__PYTHON_EXCEPTION_GUARD_END_;
		}
		
		// ------------------------------------------
		PyObject* DrawServiceBinder::setActiveSheet(PyObject* self, PyObject* args) {
			__PYTHON_EXCEPTION_GUARD_BEGIN_;
						
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			PyObject *sheet;
			if (PyArg_ParseTuple(args, "o", &sheet)) {
				DrawSheet* ds;
				
				if (!DrawSheetBinder::extract(sheet, ds))
					__PY_CONVERR_RET;
				
				o->setActiveSheet(ds);
				
				__PY_NONE_RET;
			}else {
				// Invalid parameters
				PyErr_SetString(PyExc_TypeError, "Expected a DrawSheet as an argument!");
				return NULL;
			}
			
			__PYTHON_EXCEPTION_GUARD_END_;
		}
		
		// ------------------------------------------
		PyObject* DrawServiceBinder::createDrawSource(PyObject* self, PyObject* args) {
			__PYTHON_EXCEPTION_GUARD_BEGIN_;
						
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			// argument - the name of the sheet to create, string
			const char *name, *group;

			if (PyArg_ParseTuple(args, "ss", &name, &group)) {
				DrawSourcePtr i = o->createDrawSource(name, group);
				
				PyObject *o = DrawSourceBinder::create(i);
				
				return o;
			} else {
				// Invalid parameters
				PyErr_SetString(PyExc_TypeError, "Expected two string arguments!");
				return NULL;
			}
			
			__PYTHON_EXCEPTION_GUARD_END_;
		}
		
		// ------------------------------------------
		PyObject* DrawServiceBinder::createRenderedImage(PyObject* self, PyObject* args) {
			__PYTHON_EXCEPTION_GUARD_BEGIN_;
						
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			PyObject *ds;
			if (PyArg_ParseTuple(args, "o", &ds)) {
				DrawSourcePtr cds;
				
				if (!DrawSourceBinder::extract(ds, cds))
					__PY_CONVERR_RET;
					
				RenderedImage* ri = o->createRenderedImage(cds);
				
				return RenderedImageBinder::create(ri);
			}
			
			return result;
			
			__PYTHON_EXCEPTION_GUARD_END_;
		}
		
		// ------------------------------------------
		PyObject* DrawServiceBinder::createRenderedLabel(PyObject* self, PyObject* args) {
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			return result;	//Temporary return to fix the VC build
		}
		// ------------------------------------------
		PyObject* DrawServiceBinder::destroyDrawOperation(PyObject* self, PyObject* args) {
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			return result;	//Temporary return to fix the VC build
		}
		// ------------------------------------------		
		PyObject* DrawServiceBinder::createAtlas(PyObject* self, PyObject* args) {
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			return result;	//Temporary return to fix the VC build
		}
		// ------------------------------------------
		PyObject* DrawServiceBinder::destroyAtlas(PyObject* self, PyObject* args) {
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			return result;	//Temporary return to fix the VC build
		}
		// ------------------------------------------		
		PyObject* DrawServiceBinder::loadFont(PyObject* self, PyObject* args) {
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			return result;	//Temporary return to fix the VC build
		}
		// ------------------------------------------
		PyObject* DrawServiceBinder::setFontPalette(PyObject* self, PyObject* args) {
			PyObject *result = NULL;
			DrawServicePtr o;
			
			if (!python_cast<DrawServicePtr>(self, &msType, &o))
				__PY_CONVERR_RET;
			
			return result;	//Temporary return to fix the VC build
		}
		
		// ------------------------------------------
		PyObject* DrawServiceBinder::getattr(PyObject *self, char *name) {
			return Py_FindMethod(msMethods, self, name);
		}
				
		// ------------------------------------------
		PyObject* DrawServiceBinder::repr(PyObject *self) {
			return PyString_FromFormat("<DrawService at %p>", self);
		}
		
		// ------------------------------------------
		PyObject* DrawServiceBinder::create() {
			Object* object = construct(&msType);

			if (object != NULL) {
				object->mInstance = static_pointer_cast<DrawService>(ServiceManager::getSingleton().getService(msName));
			}

			return (PyObject *)object;
		}

		// ------------------------------------------
		void DrawServiceBinder::init(PyObject* module) {
			publishType(module, &msType, msName);
		}

		
		// -------------------- Draw Operation --------------------
		const char* DrawOperationBinder::msName = "DrawOperation";

		// ------------------------------------------
		PyTypeObject DrawOperationBinder::msType = {
			PyObject_HEAD_INIT(&PyType_Type)
			0,
			"opde.services.DrawOperation",                   // char *tp_name; */
			sizeof(DrawOperationBinder::Object),  // int tp_basicsize; */
			0,                        // int tp_itemsize;       /* not used much */
			DrawOperationBinder::dealloc,   // destructor tp_dealloc; */
			0,			              // printfunc  tp_print;   */
			DrawOperationBinder::getattr,  // getattrfunc  tp_getattr; /* __getattr__ */
			0,   					  // setattrfunc  tp_setattr;  /* __setattr__ */
			0,				          // cmpfunc  tp_compare;  /* __cmp__ */
			repr,			              // reprfunc  tp_repr;    /* __repr__ */
			0,				          // PyNumberMethods *tp_as_number; */
			0,                        // PySequenceMethods *tp_as_sequence; */
			0,                        // PyMappingMethods *tp_as_mapping; */
			0,			              // hashfunc tp_hash;     /* __hash__ */
			0,                        // ternaryfunc tp_call;  /* __call__ */
			0,			              // reprfunc tp_str;      /* __str__ */
			0,			              // getattrofunc tp_getattro; */
			0,			              // setattrofunc tp_setattro; */
			0,			              // PyBufferProcs *tp_as_buffer; */
			// for inheritance searches to work we need this
			Py_TPFLAGS_HAVE_CLASS,	              // long tp_flags; */
			0,			              // char *tp_doc;  */
			0,			              // traverseproc tp_traverse; */
			0,			              // inquiry tp_clear; */
			0,			              // richcmpfunc tp_richcompare; */
			0,			              // long tp_weaklistoffset; */
			0,			              // getiterfunc tp_iter; */
			0,			              // iternextfunc tp_iternext; */
			msMethods,	                      // struct PyMethodDef *tp_methods; */
			0,                                    // struct memberlist /*  *tp_members; */
			0                                    // struct getsetlist /* *tp_getset; */
		};

		// ------------------------------------------
		PyMethodDef DrawOperationBinder::msMethods[] = {
			{"setPosition", setPosition, METH_VARARGS},
			{"setZOrder", setZOrder, METH_VARARGS},
			{"setClipRect", setClipRect, METH_VARARGS},			
			{NULL, NULL}
		};
		
		CastInfo<DrawOperation*> DrawOperationBinder::msCastInfo[] = {
				{&RenderedImageBinder::msType, &defaultPythonUpcaster<DrawOperation*, RenderedImage*>}
		};
		
		// ------------------------------------------
		PyObject* DrawOperationBinder::setPosition(PyObject* self, PyObject* args)  {
			__PYTHON_EXCEPTION_GUARD_BEGIN_;
                
			DrawOperation* o = NULL;
			
			if (!python_cast<DrawOperation*>(self, &msType, &o, msCastInfo))
				__PY_CONVERR_RET;
	  
			int x, y;
			
			if (PyArg_ParseTuple(args, "ii", &x, &y)) {
				o->setPosition(x, y);
                        
				__PY_NONE_RET;
			} else {
				// Invalid parameters
				PyErr_SetString(PyExc_TypeError, "Expected two integer arguments!");
				return NULL;
			}
					
			__PYTHON_EXCEPTION_GUARD_END_;
		}

		// ------------------------------------------
		PyObject* DrawOperationBinder::setZOrder(PyObject* self, PyObject* args)  {
			__PYTHON_EXCEPTION_GUARD_BEGIN_;
                
			DrawOperation* o = NULL;
			
			if (!python_cast<DrawOperation*>(self, &msType, &o, msCastInfo))
				__PY_CONVERR_RET;
	  
			int z;
			
			if (PyArg_ParseTuple(args, "i", &z)) {
				o->setZOrder(z);
			
				__PY_NONE_RET;
			} else {
				// Invalid parameters
				PyErr_SetString(PyExc_TypeError, "Expected an integer argument!");
				return NULL;
			}
					
			__PYTHON_EXCEPTION_GUARD_END_;
		}

		// ------------------------------------------
		PyObject* DrawOperationBinder::setClipRect(PyObject* self, PyObject* args)  {
			__PYTHON_EXCEPTION_GUARD_BEGIN_;
                
			DrawOperation* o = NULL;
			
			if (!python_cast<DrawOperation*>(self, &msType, &o, msCastInfo))
				__PY_CONVERR_RET;
                  
			PyObject *cr;
                        
			if (PyArg_ParseTuple(args, "o", &cr)) {
				// if it's a tuple, it should contain four floats
				ClipRect rect;
				if (!msRectTypeInfo.fromPyObject(cr, rect)) {
					PyErr_SetString(PyExc_TypeError, "Expected 4 float tuple!");
	                                return NULL;
				};
				
				o->setClipRect(rect);
                        
				__PY_NONE_RET;
			} else {
				// Invalid parameters
				PyErr_SetString(PyExc_TypeError, "Expected an integer argument!");
				return NULL;
			}
					
			__PYTHON_EXCEPTION_GUARD_END_;
		}

		// ------------------------------------------
		PyObject* DrawOperationBinder::getattr(PyObject *self, char *name) {
			// TODO: Image/Group name getters?
			return Py_FindMethod(msMethods, self, name);
		}
				
		// ------------------------------------------
		PyObject* DrawOperationBinder::repr(PyObject *self) {
			return PyString_FromFormat("<DrawOperation at %p>", self);
		}
		
		// ------------------------------------------
		bool DrawOperationBinder::extract(PyObject *object, DrawOperation*& op) {
			return python_cast<DrawOperation*>(object, &msType, &op);
		}
		
		// ------------------------------------------
		PyObject* DrawOperationBinder::create(DrawOperation *sh) {
			Object* object = construct(&msType);

			if (object != NULL) {
				object->mInstance = sh;
			}

			return (PyObject *)object;
		}

		// ------------------------------------------
		void DrawOperationBinder::init(PyObject* module) {
			publishType(module, &msType, msName);
		}

  	} // namespace Python
} // namespace Opde

