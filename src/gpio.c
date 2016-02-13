#include <Python.h>
#include "native-gpio.h"

static PyObject *GpioError;

static PyObject * gpio_system(PyObject *self, PyObject *args)
{
	const char *command;
	int sts;

	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;

	sts = system(command);

	if (sts < 0)
	{
		PyErr_SetString(GpioError, "System command failed");
		return NULL;
	}

	return PyLong_FromLong(sts);
}

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

static PyMethodDef GpioMethods[] = {
		{"system", gpio_system, METH_VARARGS, "Execute a shell command."},
		{"direction", (PyCFunction)gpio_direction, METH_VARARGS|METH_KEYWORDS, "Set direction of a gpio"},
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
