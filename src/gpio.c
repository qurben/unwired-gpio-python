#include <Python.h>

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

static PyMethodDef GpioMethods[] = {
		{"system", gpio_system, METH_VARARGS, "Execute a shell command."},
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
}
