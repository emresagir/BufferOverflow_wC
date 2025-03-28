# BufferOverflow_wC

This project is done for the Cybersecurity for Embedded systems course in Polito. 

It basically searches the 

## Security Check
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


## RUN

After disabling the security and making sure of CANARY or PIE is not on, 
compile it with 
    make all

this will generate the vulnerable_program

Then with 
    . exploit.sh

Follow the prompt and enter the buffer size, which is 100 bytes in this case. 
It will increase the payload byte by 1 with every iteration to find the correct memory address. 
(Which is 100 bytes of buffer + 20 bytes + 8 bytes of wanted return adress)


### TODO:   
        0. Need to add pattern recognition to stop when it finds the secret functions print.

        1. Implement basic protection mechanisms and try to bypass them

        2. Investigate how ASLR (Address Space Layout Randomization) affects your exploit