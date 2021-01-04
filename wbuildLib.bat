echo "compiling ..."

cl /c /EHsc src\*.c /I lib\ /Foobj\

echo "building static lib ..."

lib /OUT:lib\cxx.lib obj\*.obj

rem echo "building dynamic lib ..."
rem LINK /DLL /OUT:lib\cxx.dll obj\*.obj


