printf  "============================INIT=====================================\n"

################ Environment specific commands ############


################ Default commands ############
catch throw
set print elements 0
set print repeats 0
set breakpoint pending on

define bsave
    save breakpoints /vinoth/etc/gdbBreakpoints.txt
end

define bload
    source /vinoth/etc/gdbBreakpoints.txt
end

bload




printf  "=====================================================================\n"
