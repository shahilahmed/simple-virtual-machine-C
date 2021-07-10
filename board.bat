set src_file=board.c
set exe_file=board.exe

cls
gcc core/data.c core/vm.c %src_file% -o %exe_file%

%exe_file%

rm %exe_file%

