@echo off

cmake -G"Unix Makefiles" . -Bbuild/
make -C build/

pause>nul
