## BufferOverflow_wC

This project is done for the Cybersecurity for Embedded systems course in Polito.

# Security Check
This is a basic implementation so it needs to be compiled without security features.

Check ASLR status:

cat /proc/sys/kernel/randomize_va_space

    2 (enabled) → Disable with: echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
    0 (disabled) → No ASLR issues

This disables ASLR, making the memory layout predictable. Remember to re-enable it after testing with:
echo 2 | sudo tee /proc/sys/kernel/randomize_va_space



Check for other protections
checksec --file=./your_binary

If Canary or PIE (Position Independent Executable) is enabled, 
you'll need to bypass those protections.




TODO:   1. Implement basic protection mechanisms and try to bypass them
        2. Investigate how ASLR (Address Space Layout Randomization) affects your exploit