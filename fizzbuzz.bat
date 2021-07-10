set src_file=fizzbuzz.c
set exe_file=fizzbuzz.exe

cls
gcc core/data.c core/vm.c %src_file% -o %exe_file%

%exe_file%

rm %exe_file%

