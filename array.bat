set src_file=array.c
set exe_file=array.exe

cls
gcc core/data.c core/vm.c %src_file% -o %exe_file%

%exe_file%

rm %exe_file%

