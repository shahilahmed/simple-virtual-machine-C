set src_file=temp.c
set exe_file=temp.exe

cls
gcc core/data.c core/vm.c %src_file% -o %exe_file%

%exe_file%

rm %exe_file%

