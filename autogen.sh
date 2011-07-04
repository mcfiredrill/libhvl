#!/bin/bash

aclocal
automake --add-missing --copy
autoreconf --force --install
