#include <Python.h>
#include "native-gpio.h"

static PyObject *GpioError;

static PyObject * gpio_direction(PyObject *self, PyObject *args, PyObject *keywds)
{
	const int gpio;
	const int direction;

	static char *kwlist[] = {"gpio", "direction", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &gpio, &direction))
		return NULL;

	gpioDirection(gpio, direction);

	return Py_None;
}

static PyObject * gpio_set(PyObject *self, PyObject *args, PyObject *keywds)
{
	const int gpio;
	const int value;

	static char *kwlist[] = {"gpio", "value", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &gpio, &value))
		return NULL;

	gpioSet(gpio, value);

	return Py_None;
}

static PyMethodDef GpioMethods[] = {
		{"direction", (PyCFunction)gpio_direction, METH_VARARGS|METH_KEYWORDS, "Set direction of a gpio"},
		{"set", (PyCFunction)gpio_set, METH_VARARGS|METH_KEYWORDS, "Set the value of a gpio"},
		{NULL, NULL, 0, NULL}
};


PyMODINIT_FUNC initgpio(void)
{
	PyObject *m;

	m = Py_InitModule("gpio", GpioMethods);
	if (m == NULL)
		return;

	GpioError = PyErr_NewException("gpio.error", NULL, NULL);
	Py_INCREF(GpioError);
	PyModule_AddObject(m, "error", GpioError);

	int setup = gpioSetup();

	if (setup == -1) // Opening /dev/mem failed
	{
		PyErr_SetString(GpioError, "Opening /dev/mem failed");
		return;
	}
	else if (setup == -2) // Memory mapping failed
	{
		PyErr_SetString(GpioError, "Mapping memory failed");
		return;
	}
}
