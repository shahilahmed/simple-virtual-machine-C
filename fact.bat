set src_file=fact.c
set exe_file=fact.exe

cls
gcc core/data.c core/vm.c %src_file% -o %exe_file%

%exe_file%

rm %exe_file%

