#!/bin/sh

PY_BIN=$(which python | grep -v "not found")


if [ -z "${PY_BIN}" ]; then
	echo "python not installed or not in PATH, leaving."
	exit 1
fi

PY_VER=$(./check.py)

if [ ${PY_VER} -le 260 ]; then
	echo "python is too old, leaving."
	exit 1
fi

exit 0
