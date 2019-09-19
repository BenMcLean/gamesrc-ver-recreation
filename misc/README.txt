This directory includes two helper scripts, which may be run with GNU Awk
i.e., gawk. Any other Awk variant might be *incompatible*!

Each of the scripts should get an output LST file from IDA Free v4.1.
The file has to be passed as an argument *twice* (since it's processed twice).

Short explanations of the scripts:  
- print_replaced_var_suffixes_mappings_from_asm_lst.awk: Goes over textual
mentions of global variables and maps them to alternative names, based
on the address in the binary code. The file is scanned *twice* so the
*last* relevant occurrence of the variable name counts.
- replace_var_suffixes_in_asm_lst.awk: This one is similar, but prints
the LST file after renaming the global variables (during the second scan).

Note that these scripts are intended ONLY for 32-bit code built
with Watcom C for DOS (10.0a/b, 10.6 and similar).

FURTHER BE WARNED THAT ANY OF THESE SCRIPTS MAY FAIL FOR ANY ARBITRARY REASON.
