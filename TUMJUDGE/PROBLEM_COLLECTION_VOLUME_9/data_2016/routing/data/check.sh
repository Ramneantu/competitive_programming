#!/bin/sh
for file in */*.in; do echo $file; ~/git/conpra-stefan/domjudge/validation/checktestdata ../input_format_validators/routing.ctd $file; done
