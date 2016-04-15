# MFC
A multithreading referential compress of DNA information

This is the 0.1 version

Usage:

   mfc task inputpath outputpath
	or mfc task inputpath referencepath outputpath
    where:
    - task is either COMPRESS, DECOMPRESS
    - input is \n";
    - a path to the to-be-compressed file (in case of COMPRESS)
    - a path to the referentially compressed files (in case of DECOMPRESS)
	- referencepath is \n";
	- a path to a  appointed reference sequence path (in case of COMPRESS and DECOMPRESS)
    - output is\n";
    - a path to the referentially compressed output files (in case of COMPRESS)
    - a path to the uncompressed outputfile (in case of DECOMPRESS)
      
    Examples:
    ./mfc COMRESS /database/chr1/ /database/reference.fa /database/compressed/ 
    ./mfc DECOMRESS /database/compressed/ /database/reference.fa /database/decompressed/ 
   
    For further information please see README.txt
